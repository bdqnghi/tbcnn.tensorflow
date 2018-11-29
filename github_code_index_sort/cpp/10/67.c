/*************************************************************************
	> File Name: bucketsort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年01月13日 星期三 20时38分22秒
 ************************************************************************/

#include <iostream>
using namespace std;


#define N  101

int main()
{
    int arr[N] = {0};

    int num = 0;
    cout << "输入学生的个数：";
    cin >> num;
    cout << "输入学生的成绩: ";
    int score;
    for(int i = 0; i < num; ++i){
        cin >> score;
        arr[score]++;
    }

    cout << "从小到大输出学生的成绩: ";
    for (int i = 0; i < N; ++i){
        for (int j = 1; j <= arr[i]; ++j)
            cout << i << " ";
    }
    cout << endl;

    return 0;
}
