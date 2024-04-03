#include <chrono>
#include <map>
#include <string>
#include <fstream>

#define INPUT "large_input.txt"
#define OUTPUT "large_output.txt"

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
		fout << "The word '" << pair.first << "' appears '" << pair.second << "' times\n";
	}

	const auto stop = chrono::high_resolution_clock::now();
	const auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	fout << "Time taken: " << duration.count() << " microseconds" << endl;

	return 0;
}