/*
��C����ʵ��һ��revert���������Ĺ����ǽ�������ַ�����ԭ����
����󷵻�
 *
 * author:	dongbeibei
 * time:		2013/7/1
 */


#include <iostream>

using namespace std;

void myswap(char *a, char *b);
void revert(char *str);

int main(void)
{
	char str[] = "asdfg";

	cout<<"origin:\t"<<str<<endl;
	revert(str);
	cout<<"result:\t"<<str<<endl;

	return 0;
}

void myswap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void revert(char *str)
{
	int i, j;

	i = j = 0;

	while(str[j] != '\0')
		j++;
	j--;
	while(i<j)
	{
		myswap(&str[i], &str[j]);
		i++;
		j--;
	}
}
