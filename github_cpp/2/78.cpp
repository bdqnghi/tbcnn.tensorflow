// Huffman-coding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Huffman.h"

using namespace std;

void help()
{
	auto message =
		"The Program command line execution is ./<program> [<input_file>]\n\
	input_file is optional, if not provided the program will read the user input.\n\n\
	Also, this program assumes the input provided will only contain charactes between a-z and A-Z\n";

	cout << message << endl;
}

void make_string_args(vector<string>& args, int n, char** argv)
{
	for (auto i = 1; i < n; i++)
		args.push_back(string(argv[i]));
}

int main(int argc, char** argv)
{
	// more than 1 argument
	if (argc > 2)
	{
		help();
		return 1;
	}

	// make char** into vector<string>
	vector<string> args;
	make_string_args(args, argc, argv);

	// show help if specified
	if (argc == 2 && args[0] == "help")
	{
		help();
		return 0;
	}

	string message;

	// initialize message
	if (argc == 1)
	{
		getline(cin, message);
	}
	else
	{
		ifstream file;
		file.open(args[0]);

		if (!file.is_open())
		{
			cerr << "Error while opening the file" << endl;
			return 1;
		}

		getline(file, message);

		file.close();
	}

	// code message
	auto result = huffman::code(message);

	// print results
	// pair left has the size of the original ASCII string in bits
	// pair right has the size of the codificated string in bits
	cout << "Size of the original text in ASCII: " << result.first << " bits" << endl;
	cout << "Size of the huffman string: " << result.second << " bits" << endl;
	cout << "Saved size in bits: " << result.first - result.second << endl;

	return 0;
}
