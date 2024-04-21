#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <mpi.h>
#include <string>

#define INPUT "input.txt"
#define OUTPUT "parallel_output.txt"

using namespace std;
using namespace std::chrono;

const int MAX_WORDS = 8000;
const int MAX_WORD_LENGTH = 50;

ifstream fin(INPUT);
ofstream fout(OUTPUT);

int main(int argc, char** argv)
{
	const auto start_time = high_resolution_clock::now();

	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (!fin.is_open())
	{
		cout << "Could not open the file: " << INPUT << "\n";
		MPI_Finalize();
		return -1;
	}

	char delimiters[162] = {};
	int index = 0;
	for (int ascii_character = 32; ascii_character < 256; ++ascii_character)
	{
		if (!isalnum(ascii_character))
		{
			delimiters[index++] = static_cast<char>(ascii_character);
		}
	}

	char local_words[MAX_WORDS][MAX_WORD_LENGTH] = {};
	int local_word_count[MAX_WORDS] = { 0 };
	string line;
	int line_count = 0;
	while (getline(fin, line))
	{
		if (line_count % size == rank)
		{
			const char* word = strtok(line.data(), delimiters);
			while (word != nullptr)
			{
				int hash = 0;
				for (int i = 0; word[i] != '\0'; ++i)
				{
					hash = (hash * 2 + word[i]) % 997;
				}

				++local_word_count[hash];
				strcpy(local_words[hash], word);

				word = strtok(nullptr, delimiters);
			}
		}
		line_count++;
	}

	fin.close();

	int global_word_count[MAX_WORDS] = { 0 };
	MPI_Allreduce(local_word_count, global_word_count, MAX_WORDS, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	char all_words[MAX_WORDS][MAX_WORD_LENGTH] = {};
	MPI_Allreduce(local_words, all_words, MAX_WORDS * MAX_WORD_LENGTH, MPI_CHAR, MPI_MAX, MPI_COMM_WORLD);

	if (rank == 0)
	{
		if (!fout.is_open())
		{
			cout << "Could not create the file: " << OUTPUT << "\n";
			return -1;
		}

		for (int i = 0; i < MAX_WORDS; ++i)
		{
			if (global_word_count[i] > 0)
			{
				fout << all_words[i] << " : " << global_word_count[i] << "\n";
			}
		}

		const auto end_time = high_resolution_clock::now();
		const auto duration = duration_cast<microseconds>(end_time - start_time);

		fout << "\nExecution time: " << duration.count() << " microseconds ";
		fout << "(" << duration.count() / 1000000.0 << " milliseconds)\n";

		fout.close();

		cout << "Output successfully written to: " << OUTPUT << "\n";
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}