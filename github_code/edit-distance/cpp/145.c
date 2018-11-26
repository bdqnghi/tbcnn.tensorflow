/*Implementation of Levenshtein distance in CPP (Wagner-Fischer algorithm)*/ 

#include <bits/stdc++.h>
using namespace std;

int levenshtein_distance (string str1,string str2) {
	int m = str1.length();
	int n = str2.length();
	int d[m+1][n+1]; 

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0)
				d[i][j] = j;
		
			else if (j == 0)
				d[i][j] = i;
		
			else if (str1[i-1] == str2[j-1])
				d[i][j] = d[i-1][j-1];	

			else
				d[i][j] = min (min (1 + d[i-1][j], 1 +d[i][j-1]), 1 + d[i-1][j-1]); // deletion -> insertion -> substitution
		}
	}
	return d[m][n];
}

int main (int argc, char **argv) {
	if (argc < 3) {
		cout << endl;
		cout <<"Usage : " << argv[0] << " <string1> <string2> " << endl << endl;
		exit(0);
	}
	else {
		cout << endl;
		cout <<"The Levenshtein distance between " << argv[1] << " and " << argv[2] << " is : " << levenshtein_distance(argv[1],argv[2]) << endl << endl;
	}
	return 0;
}

