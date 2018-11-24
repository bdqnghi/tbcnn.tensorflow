//���ߣ����ٹ�
//ʱ�䣺2016-06-26
//--Ѱ�����·��֮Floyd-Warshall�㷨

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Info
{
	int cost; //��ǰ��㵽��ʼ�ڵ�����·������
	int pre; //��ǰ����ǰ���ڵ�
	Info(){ cost = INT_MAX; pre = -1; }
};
vector<vector<Info>> Path[2]; //�洢ÿ���ڵ�Ե�·����Ϣ���������������ʾ��ʼ�ڵ㣬��������ʾ��ֹ�ڵ�
//����ʹ�õ�����˫�ױ�ʾ����˼��
//���ڸ��㷨�ڵ��������в���ԭ�ز��������Դ˴�ʹ�����������󣬵��������в����л����Ӷ�������
//ÿ�ε���ʱ���о�����

int Floyd()
{
	int n = Path[0].size();
	int flag = 0, flag1;
	for (int k = 0; k < n; k++)
	{
		flag1 = flag;
		flag = (flag + 1) % 2;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Path[flag1][i][k].cost == INT_MAX || Path[flag1][k][j].cost==INT_MAX ||
					Path[flag1][i][j].cost <= Path[flag1][i][k].cost + Path[flag1][k][j].cost)
				{
					Path[flag][i][j] = Path[flag1][i][j];
				}
				else
				{
					Path[flag][i][j].cost = Path[flag1][i][k].cost + Path[flag1][k][j].cost;
					Path[flag][i][j].pre = Path[flag1][k][j].pre;
				}
			}
		}
	}
	return flag;
}
void Print(vector<vector<Info>>& Path)
{
	int n = Path.size();
	cout << "Result:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << "From " << i << " to " << j << ": " << Path[i][j].cost << endl;
	}
	cout << endl;
}
int main()
{
	int n, m, u, v, w;
	ifstream in("data.txt"); //���ļ��ж�ȡͼ����Ϣ
	in >> n >> m; //n��ʾ;�нڵ�ĸ�����m��ʾͼ�бߵ�����
	Path[0].assign(n, vector<Info>(n, Info()));
	while (m--)
	{
		in >> u >> v >> w;
		Path[0][u][v].cost = w;
		Path[0][u][v].pre = u;
	}
	for (int i = 0; i < n; i++)
		Path[0][i][i].cost = 0;
	Path[1] = Path[0];

	int nu=Floyd();
	Print(Path[nu]);

	system("pause");
	return 0;
}