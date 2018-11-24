#include <iostream>
#include <set>
#include <vector>
using namespace std;

//����ѵ������
#define M 3
#define N 15

//Ϊ�˼���򵥣���A2={S, M, L},��S=1, M=2, L=3��
//Y={1�� -1}����ΪY={1�� 2}
int A[M][N] = {
	{ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3 },
	{ 1, 2, 2, 1, 1, 1, 2, 2, 3, 3, 3, 2, 2, 3, 3 },
	{ 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2 }
};

struct Px1
{
	int x1;
	int y;
	double p_x1y;
};

struct Px2
{
	int x2;
	int y;
	double p_x2y;
};

double p[2];
Px1 px1[6];
Px2 px2[6];

//����������ʺ���������
void calP()
{
	//��������
	//double p[2];
	int i, j, k;
	multiset<int> m_x1, m_x2, m_y;//���ؼ�����
	multiset<int>::iterator pos1;

	set<int> x1, x2, y;//��������
	set<int>::iterator pos2, pos3;

	//���ö��ؼ������ͼ�������
	for (i = 0; i < N; i++)
	{
		m_x1.insert(A[0][i]);
		m_x2.insert(A[1][i]);
		m_y.insert(A[2][i]);

		x1.insert(A[0][i]);
		x2.insert(A[1][i]);
		y.insert(A[2][i]);
	}

	p[0] = m_y.count(1) / (double)N;	//p(Y = 1)
	p[1] = m_y.count(2) / (double)N;	//p(Y = 2)
	cout << endl << "************����***********" << endl;
	cout << "p(Y = 1) = " << p[0] << endl;
	cout << "p(Y = 2) = " << p[1] << endl;


	//������������
	cout << endl;
	cout << "*********��������********" << endl;
	//	int px1_num = 3 * 2;
	//	int px2_num = 3 * 2;

	j = 0;
	for (pos2 = y.begin(); pos2 != y.end(); pos2++)//y������ȡֵ
	{
		for (pos3 = x1.begin(); pos3 != x1.end(); pos3++)//����x1������ȡֵ
		{
			px1[j].y = *pos2;
			px1[j].x1 = *pos3;

			int count_x1y = 0;
			for (k = 0; k < N; k++)
			{
				if (A[0][k] == px1[j].x1 && A[2][k] == px1[j].y)
					count_x1y++;//��һ��������ÿ������ȡֵ���ֵĴ���������������
			}
			px1[j].p_x1y = count_x1y / (double)m_y.count(px1[j].y);//����p(x1 | y)�ĸ���
			j++;
		}
	}

	cout << "p(x1 | y):" << endl;
	for (j = 0; j < 6; j++)
	{
		cout << px1[j].x1 << " " << px1[j].y << " " << px1[j].p_x1y << endl;
	}


	j = 0;
	for (pos2 = y.begin(); pos2 != y.end(); pos2++)
	{
		for (pos3 = x2.begin(); pos3 != x2.end(); pos3++)
		{
			px2[j].y = *pos2;
			px2[j].x2 = *pos3;

			int count_x2y = 0;
			for (k = 0; k < N; k++)
			{
				if (A[1][k] == px2[j].x2 && A[2][k] == px2[j].y)
					count_x2y++;
			}
			px2[j].p_x2y = count_x2y / (double)m_y.count(px2[j].y);//����p(x2 | y)�ĸ���
			j++;
		}
	}

	cout << "p(x2 | y):" << endl;
	for (j = 0; j < 6; j++)
	{
		cout << px2[j].x2 << " " << px2[j].y << " " << px2[j].p_x2y << endl;
	}

}


/*int main()
{
	int i = 0, j = 0;
	//���ѵ������
	cout << "***********ѵ������************" << endl;
	for (i = 0; i < M; i++)
	{
		if (i == 0) cout << "X1: ";
		else if (i == 1) cout << "X2: ";
		else if (i == 2) cout << " Y: ";
		for (int j = 0; j < N; j++)
		{
			cout << " " << A[i][j];
		}
		cout << endl;
	}

	calP();//�����������������


	int s_x1, s_x2;
	double result[2];
	int class_y = 1;
	cout << "*************Ԥ��***************" << endl;
	cout << endl << endl << "Input:";
	cin >> s_x1 >> s_x2;

	for (i = 0; i < 2; i++)
	{
		double s_px_1, s_px_2;
		for (j = 0; j < 6; j++)
		{
			if (s_x1 == px1[j].x1 && px1[j].y == class_y)
				s_px_1 = px1[j].p_x1y;
			if (s_x2 == px2[j].x2 && px2[j].y == class_y)
				s_px_2 = px2[j].p_x2y;
		}
		result[i] = p[i] * s_px_1 * s_px_2;
		class_y++;
	}

	cout << endl << "all results:";
	cout << result[0] << " " << result[1] << endl;


	for (i = 0; i <2; i++)
	{
		class_y = i;
		if (result[i] < result[i + 1])
		{
			class_y = i + 1;
		}
	}

	cout << "(" << s_x1 << "," << s_x2 << ")��������ǣ�" << class_y + 1 << endl;
	system("pause");
	return 0;
}*/