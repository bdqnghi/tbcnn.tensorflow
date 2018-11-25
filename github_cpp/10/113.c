


#include <iostream>
#include <string>

using namespace std;


int min(int a, int b)  
{
	return a < b ? a : b;
}


int edit(string str1, string str2){

	int str1_len = str1.size();
	int str2_len = str2.size();

	
	int **num = new int*[str1_len + 1];

	for(int i = 0; i < str1_len + 1 ;i++){
		num[i] = new int[str2_len + 1];
	}
	for(int i = 0 ;i < str1_len + 1 ;i++){
		num[i][0] = i;
	}
	for(int i = 0 ;i < str2_len + 1;i++){
		num[0][i] = i;
	}

	
	for(int i = 1 ;i < str1_len + 1 ;i++){
		for(int j = 1 ;j< str2_len + 1; j++){
			int distance;
			int temp = min(num[i-1][j] + 1, num[i][j-1] + 1);
			if(str1[i-1] == str2[j-1]){
				distance = 0 ;
			}
			else{
				distance = 1 ;
			}
			num[i][j] = min(temp, num[i-1][j-1] + distance);
		}
	}
	

	int dis = num[str1_len][str2_len];
	
	for(int i = 0; i < str1_len + 1; i++){
		delete[] num[i];
		num[i] = NULL;
	}

	delete[] num;
	num = NULL;
	
	return dis;
}

int main(void){

	string str1 ;
	string str2 ;

	cout<<"input two string:"<<endl;
	cin>>str1;
	cin>>str2;
	int r = edit(str1, str2);
	cout << "the result is : " << r << endl;

	return 0;
}
