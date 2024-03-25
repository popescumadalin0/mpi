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

	while (fin >> input)
	{
		freq[input]++;
	}

	for (const auto& pair : freq)
	{
		fout << "The word '" << pair.first << "' appears '" << pair.second << "' times\n";
	}

	return 0;
}