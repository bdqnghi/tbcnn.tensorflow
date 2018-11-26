#include "stdafx.h"
#include "LevenshteinDistanceCpp.h"
#include "LevenshteinDistanceApplication.h"
#include "helpers.h"
#include <windows.h>
#include <chrono>
#include <thread>
#include <fstream>

extern "C" int _stdcall initializeLevMatrix(unsigned int* x, DWORD y, DWORD z);
extern "C" int _stdcall countDiagonally(unsigned int* x, DWORD index, int* s1, int* s2, DWORD len1);
extern "C" int _stdcall countLevenshteinDistance(unsigned int* levTable, int* s1, int* s2, int dir, int index, int len1, int len2);

int main()
{
	string s1 = "";
	string s2 = "";

	Helpers::loadWords(s1, s2);
	ofstream outputFile("outputFile.txt");

	const std::size_t len1 = s1.size(), len2 = s2.size();
	unsigned int howManyTimes = (len1 > len2 ? len2 : len1);
	
	outputFile << "length1: " << len1 << endl;
	outputFile << "length2: " << len2 << endl;

	while (1) {
		int choiceImpl = Helpers::chooseBetweenAsmAndCpp();

		int choiceConc = Helpers::chooseIfConcurrencyOrNot();

		if (1 == choiceImpl) {
			unsigned int* levTableAsm = new unsigned int[(len1 + 1) * (len2 + 1)];
			int* charArrayAsInts1 = new int[len1];
			int* charArrayAsInts2 = new int[len2];
			Helpers::convertStringToArrayOfInts(s1, charArrayAsInts1);
			Helpers::convertStringToArrayOfInts(s2, charArrayAsInts2);
			initializeLevMatrix(levTableAsm, len1, len2);
			if (1 == choiceConc) {
				auto t0 = std::chrono::high_resolution_clock::now();
				for (int i = 1; i <= howManyTimes; i++) {
					countDiagonally(levTableAsm, i, charArrayAsInts1, charArrayAsInts2, len2);
					thread funcTest1(countLevenshteinDistance, levTableAsm, charArrayAsInts1, charArrayAsInts2, 0, i, len2, len1);
					thread funcTest2(countLevenshteinDistance, levTableAsm, charArrayAsInts1, charArrayAsInts2, 1, i, len2, len1);
					funcTest1.join();
					funcTest2.join();
				}

				auto t1 = std::chrono::high_resolution_clock::now();
				//std::chrono::duration<double> elapsed = t1 - t0;

				auto dt = 1.e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();

				//Helpers::showFormattedAsmMatrix(levTableAsm, len2, len1);

				printf("MASM time with concurrency: %lf\n", dt);
				outputFile << "MASM time with concurrency: " << dt << endl;
			}
			else {
				auto t0 = std::chrono::high_resolution_clock::now();

				for (int i = 1; i <= howManyTimes; i++) {
					countDiagonally(levTableAsm, i, charArrayAsInts1, charArrayAsInts2, len2);
					countLevenshteinDistance(levTableAsm, charArrayAsInts1, charArrayAsInts2, 0, i, len2, len1);
					countLevenshteinDistance(levTableAsm, charArrayAsInts1, charArrayAsInts2, 1, i, len2, len1);
				}

				auto t1 = std::chrono::high_resolution_clock::now();
				auto dt = 1.e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();

				//Helpers::showFormattedAsmMatrix(levTableAsm, len2, len1);

				printf("MASM time without concurrency: %lf\n", dt);
				outputFile << "MASM time without concurrency: " << dt << endl;
			}
			outputFile << "Result: " << levTableAsm[(len1 + 1) * (len2 + 1) - 1] << endl;
			delete[] levTableAsm;
			delete[] charArrayAsInts1;
			delete[] charArrayAsInts2;
		}
		else {
			unsigned int** levTable = new unsigned int*[len1 + 1];
			for (int i = 0; i <= (len1 + 1); ++i)
				levTable[i] = new unsigned int[len2 + 1];
			if (1 == choiceConc) {
				auto t0 = std::chrono::high_resolution_clock::now();

				LevenshteinDistanceCpp::Functions::initializeLevMatrix(levTable, len1, len2);
				for (int i = 1; i <= howManyTimes; i++) {
					LevenshteinDistanceCpp::Functions::countDiagonally(levTable, i, s1, s2);
					thread funcTest1(LevenshteinDistanceCpp::Functions::countLevenshteinDistance, levTable, s1, s2, 0, i);
					thread funcTest2(LevenshteinDistanceCpp::Functions::countLevenshteinDistance, levTable, s1, s2, 1, i);
					funcTest1.join();
					funcTest2.join();
				}

				auto t1 = std::chrono::high_resolution_clock::now();
				auto dt = 1.e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();

				//Helpers::showFormattedCppMatrix(levTable, len1, len2);

				printf("C++ time with concurrency: %lf\n", dt);
				outputFile << "C++ time with concurrency: " << dt << endl;
			}
			else {
				auto t0 = std::chrono::high_resolution_clock::now();

				LevenshteinDistanceCpp::Functions::initializeLevMatrix(levTable, len1, len2);
				for (int i = 1; i <= howManyTimes; i++) {
					LevenshteinDistanceCpp::Functions::countDiagonally(levTable, i, s1, s2);
					LevenshteinDistanceCpp::Functions::countLevenshteinDistance(levTable, s1, s2, 0, i);
					LevenshteinDistanceCpp::Functions::countLevenshteinDistance(levTable, s1, s2, 1, i);
				}

				auto t1 = std::chrono::high_resolution_clock::now();
				auto dt = 1.e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();

				//Helpers::showFormattedCppMatrix(levTable, len1, len2);

				printf("C++ time without concurrency: %lf\n", dt);
				outputFile << "C++ time without concurrency: " << dt << endl;
			}
			outputFile << "Result: " << levTable[len1][len2] << endl;
			for (int i = 0; i<= (len1 + 1); i++)
				delete[] levTable[i];

			//delete[] levTable;
		}
	}
	outputFile.close();

	return 0;
}
