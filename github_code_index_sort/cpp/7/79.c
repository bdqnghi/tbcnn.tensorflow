/*
 * ShellSort.cpp
 *
 *  Created on: 2013-7-10
 *      Author: Administrator
 */

#include "ShellSort.h"

//���ƣ�ͨ��һ������������֤�˸ò���Ǯǰ��������������
void ShellSort::sort(vector<int>& array,vector<int> step)
{
	for(vector<int>::iterator i = step.begin();i != step.end();i++)
	{
		for(int j=*i;j < array.size();j++)
		{
			int key = array[j];
			int k = 0;
			for(k =j-*i;k>=0 && array[k]>key;k-=*i)
			{
				array[k+*i] = array[k];
			}
			array[k+*i] = key;
		}
	}
}

vector<int> ShellSort::sort_result(vector<int> &array)
{
	int step_temp[7] = {1, 9, 34, 182, 836, 4025, 19001};
	vector<int> step(step_temp,step_temp+6);
	sort(array,step);
	return array;
}



