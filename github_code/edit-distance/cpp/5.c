#include <iostream>
#include <string>

using namespace std;

int minimum(int a, int b){
	return ((a<b)?a:b);
}

int minDistance(string word1, string word2) {
	int len1 = word1.length(), len2 = word2.length();
	if(len1==0 && len2==0) return 0;
	else if(len1==0) return len2;
	else if(len2==0) return len1;
	int distances[len1+1][len2+1];
	for(int i=0;i<=len1;i++){
		distances[i][0] = i;
	}
	for(int i=0;i<=len2;i++){
		distances[0][i] = i;
	}
	for(int i=1;i<=len1;i++){
		for(int j=1;j<=len2;j++){
			if(word1[i-1]==word2[j-1]){
				distances[i][j] = distances[i-1][j-1];
			} else {
				distances[i][j] = 1 + minimum(distances[i-1][j-1], minimum(distances[i-1][j], distances[i][j-1]));
			}
		}
	}
	/*for(int i=0;i<=len1;i++){
		for(int j=0;j<=len2;j++){
			cout << distances[i][j] << " ";
		}
		cout << endl;
	}*/
	return distances[len1][len2];
}

int main(){
	string word1, word2;
	cin >> word1 >> word2;
	cout << minDistance(word1, word2) << endl;
	return 0;
}