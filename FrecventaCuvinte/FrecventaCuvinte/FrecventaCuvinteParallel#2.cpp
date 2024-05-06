#include <algorithm>
#include <chrono>
#include <execution>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#define INPUT "input.txt"
#define OUTPUT "parallel_output#2.txt"

using namespace std;

ifstream fin(INPUT);
ofstream fout(OUTPUT);

int main()
{
	string input;
	map<string, int> freq;

	const auto start = chrono::high_resolution_clock::now();

	if (!fin.is_open())
	{
		cout << "Could not open the file: " << INPUT << "\n";
		return -1;
	}
	while (fin >> input)
	{
		freq[input]++;
	}

	fin.close();

	if (!fout.is_open())
	{
		cout << "Could not create the file: " << OUTPUT << "\n";
		return -1;
	}

	for_each(execution::par_unseq, freq.begin(), freq.end(), [](const pair<const string, int>& val)
		{
			fout << val.first << ": " << val.second << "\n";
		});

	const auto stop = chrono::high_resolution_clock::now();
	const auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	fout << "\nExecution time: " << duration.count() << " microseconds ";
	fout << "(" << duration.count() / 1000000.0 << " milliseconds)\n";

	fout.close();

	cout << "Output successfully written to: " << OUTPUT << "\n";

	return 0;
}