/*#define _CRT_SECURE_NO_WARNINGS
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

constexpr int max_words = 8000;
constexpr int max_word_length = 50;

ifstream fin(INPUT);
ofstream fout(OUTPUT);

int main(const int argc, char** argv)
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

	string word;
	int counter = 0;
	int rank_freq_words[max_words] = { 0 };
	char rank_words[max_words][max_word_length] = {};
	while (fin >> word)
	{
		if (counter++ % size == rank)
		{
			int hash = 0;
			for (int i = 0; word[i] != '\0'; ++i)
			{
				hash = (hash * 2 + word[i]) % 997;
			}

			strcpy(rank_words[hash], word.data());
			++rank_freq_words[hash];
		}
	}
	fin.close();

	int freq_words[max_words] = { 0 };
	MPI_Allreduce(rank_freq_words, freq_words, max_words, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	char words[max_words][max_word_length] = {};
	MPI_Allreduce(rank_words, words, max_words * max_word_length, MPI_CHAR, MPI_MAX, MPI_COMM_WORLD);

	if (rank == 0)
	{
		if (!fout.is_open())
		{
			cout << "Could not create the file: " << OUTPUT << "\n";
			return -1;
		}

		for (int i = 0; i < max_words; ++i)
		{
			if (freq_words[i] > 0)
			{
				fout << words[i] << " : " << freq_words[i] << "\n";
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
}*/