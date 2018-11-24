// Algorithm: Searching for Patterns
// @author: Kushashwa Ravi Shrimali
// KMP Algo - O(n) 
//

#include <bits/stdc++.h>
#include <string.h>

using namespace std;

// computes lps Array  
void lpsArrayCompute(string pat, int index, int* lpsArray);

// return occurences of pattern in the text
void search_kmp(string text, string pattern) {
	// lengths of text and pattern
	int len_text = text.length();
	int len_pattern = pattern.length();
	int M = len_text;
	int N = len_pattern;

	// create lps array and compute
	int* lpsArray = new int[len_text];

	// compute lps array 
	lpsArrayCompute(pattern, len_text, lpsArray);

	// initialize indexes for searching sub-patterns in the text
	int i = 0;
	int j = 0;
	while(i < len_pattern) {
		if(pattern[j] == text[i]) {
			i++; 
			j++;
		}

		if(j == M) {
			printf("Found pattern at: %d", i - j);
			j = lpsArray[j-1];
		} 
		else if(i < N && pattern[j] != text[i]) {
			// mismatch
			if(j != 0)
				j = lpsArray[j -1];
			else
				i += 1;
		}
	}
}

void lpsArrayCompute(string pat, int text_length, int* lpsArray) {
	int len = 0; // length of previous lps
	lpsArray[0] = 0; // initialize

	int i = 1; 
	while(i < text_length) {
		if(pat[i] == pat[len]) {
			len++;
			lpsArray[i] = len;
			i++;
		}
		else {
			if(len != 0) {
				len = lpsArray[len - 1];
			}
			else {
				lpsArray[i] = 0;
				i++;
			}
		}
	}
}

int main() {
	string text = "ABABDABACDABABCABAB";
	string pattern = "ABAB";
	search_kmp(pattern, text);
}