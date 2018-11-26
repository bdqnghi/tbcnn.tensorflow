/// \file 1.cpp
/*
  ------------------------------------
  Create date : 2014-11-04 17:08
  Modified date: 2014-11-07 21:43
  Author : liaoshengxin
  Email : 654504711@qq.com
  ------------------------------------
*/

#include <iostream>
#include <string>

using namespace std;


int min(int a, int b)  //求最小值
{
	return a < b ? a : b;
}

//编辑比较
int edit(string str1, string str2){

	int str1_len = str1.size();
	int str2_len = str2.size();

	//定义编辑距离
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

	//edit
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
	//显示过程
/*	for(int i = 0 ;i < str1_len + 1 ;i++){
		for(int j = 0; j< str2_len + 1; j++){
			cout << num[i][j] << " " ;
		}
		cout << endl;
	}*/
	int dis = num[str1_len][str2_len];
	//释放内存
	for(int i = 0; i < str1_len + 1; i++){
		delete[] num[i];
		num[i] = NULL;
	}

	delete[] num;
	num = NULL;
	//返回结果
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
