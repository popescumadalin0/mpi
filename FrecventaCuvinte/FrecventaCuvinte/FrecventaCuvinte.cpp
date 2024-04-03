#include <chrono>
#include <map>
#include <string>
#include <fstream>

#define INPUT "input.txt"
#define OUTPUT "output.txt"

using namespace std;

ifstream fin(INPUT);
ofstream fout(OUTPUT);

int main()
{
	string input;
	map<string, int> freq;
	const auto start = chrono::high_resolution_clock::now();
	while (fin >> input)
	{
		freq[input]++;
	}

	for (const auto& pair : freq)
	{
		fout << pair.first << ": " << pair.second << "\n";
	}

	const auto stop = chrono::high_resolution_clock::now();
	const auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	fout << "Time taken: " << duration.count() << " microseconds" << endl;

	return 0;
}