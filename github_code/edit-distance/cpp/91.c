#include <iostream>
#include <string>

using namespace std;

#define MAXLEN 20			//����ַ�������
enum OperEnum
{
	MATCH = 0,
	INSERTNUM1,
	INSERTNUM2,
	DELETENUM1,
	DELETENUM2
};
/*
 * ����:     distance������룬operate�������
 * ������:   TheBeatles1994
 */
typedef struct
{
	int distance;
	int operate;
}StrUnit;
StrUnit strdist[MAXLEN][MAXLEN];
/*
 * ����:     �Ƚ����ַ����Ƿ���ȣ���ȷ���0�����ȷ���1
 * ������:   TheBeatles1994
 */
int CompareChars(char ch1, char ch2)
{
	return (ch1 == ch2 ? 0 : 1);
}

/*
 * ��������: �Ƚ����ַ����ľ���
 * ������:   TheBeatles1994
 */
int CompareStrings(char str1[], char str2[])
{
	int str1len = strlen(str1);
	int str2len = strlen(str2);
	char tempstr1[MAXLEN] = " ";
	char tempstr2[MAXLEN] = " ";

	strcat_s(tempstr1, MAXLEN,str1);
	strcat_s(tempstr2, MAXLEN,str2);
	//��ʼ��strdist
	for (int i = 1; i <= str1len; i++)
	{
		strdist[i][0].distance = i;
		strdist[0][i].distance = i;
	}
	for (int i = 1; i <= str1len; i++)
	{
		for (int j = 1; j <= str2len; j++)
		{
			int ope[5];
			ope[MATCH] = strdist[i - 1][j - 1].distance + CompareChars(tempstr1[i],tempstr2[j]);
			ope[INSERTNUM1] = strdist[i][j - 1].distance + 1;
			ope[INSERTNUM2] = strdist[i - 1][j].distance + 1;
			ope[DELETENUM1] = ope[INSERTNUM2];
			ope[DELETENUM2] = ope[INSERTNUM1];
			strdist[i][j].distance = ope[MATCH];
			strdist[i][j].operate = MATCH;
			for (int k = INSERTNUM1; k <= DELETENUM2; k++)
			{
				if (strdist[i][j].distance > ope[k])
				{
					strdist[i][j].distance = ope[k];
					strdist[i][j].operate = k;
				}
			}
		}
	}

	return strdist[str1len][str2len].distance;
}

int main()
{
	char str1[MAXLEN + 1];
	char str2[MAXLEN + 1];

	gets_s(str1);
	gets_s(str2);

	cout << CompareStrings(str1, str2) << endl;

	system("pause");
	return 0;
}