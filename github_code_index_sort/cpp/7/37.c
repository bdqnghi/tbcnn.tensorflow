//ShellSort.cpp ϣ��������
//����Shellsort::Shellsort�����ڸ�����ʾ�������

#include<iostream>
using namespace std;

//ϣ��������
class ShellSort{
private:
	int *pnum; 							//ָ������ָ��������ָ����������
	int *d;								//ָ������ָ�����������
	int max;
	int row;
public:
	void Size(int n);					//��̬�����ڴ�ռ䣬���ڴ洢����������
	void Delete();						//ɾ����������ڴ�
	void Value(int* value, int n);		//�����ݸ�ֵ
	void Output(int n);					//�Դ�ӡ����
	int DValue(int n);					//����ϣ����������
	void Shellsort(int n, int numOfD);	//ϣ������
};



//��̬�����ڴ�ռ䣬����洢����������
void ShellSort::Size(int n)
{
	pnum = new int[n];
	max=n;
	row=0;
}


//ɾ����������ڴ�
void ShellSort::Delete()
{
	delete [] pnum;
	delete [] d;
}


//�����ݸ�ֵ
void ShellSort::Value(int* value, int n)
{
	int max=sizeof(pnum)/sizeof(int);
	for(int i=0; i<n; i++)
		pnum[i]=value[i];
}


//�Դ�ӡ����
void ShellSort::Output(int n)
{
	for(int i=0; i<n; i++)
	{
		cout<<pnum[i]<<" ";
	}
	cout<<endl;
}

//����n���������ݸ���������d[]��������ĸ�������ֵgap
int ShellSort::DValue(int n) 
{
	int flag=0; //����ֵ�ĸ���
	int max=n; 

	while(n != 1) //��������ֵ�ĸ���
	{
		n=n/2;
		flag++;
	}
	d = new int[flag]; //����ֵ����

	for(int i=0; i<flag; i++) //��������ֵ
	{
		max=max/2;
		d[i]=max; //װ������ֵ
	}
	return flag; //��������ֵ�ĸ���
}

///ϣ����������a[]Ϊ����������������Ԫ�أ�nָ�����������Ԫ�ظ���
//d[]���ϣ������������ֵ��numOfDָ��d[]������Ԫ�ظ���
void ShellSort::Shellsort(int n, int numOfD)
//��ϣ�����򷨶Լ�¼a[0]--a[n-1]����
//�����ڲ���ֱ�Ӳ��뷨����
{
	int i, j, k, m; 
	int gap,row=0;	//gap��ʾ����ֵ��Ҳ����ȡ�����еļ�� rowΪ�ڼ��β�������
	long temp;

	for(m = 0; m < numOfD; m++)
	{
		gap = d[m];              //ȡ�����е�ֵ������gap
		for(k = 0; k < gap; k++) //ѭ���Ƚ�ֵ��������������Ҫ��ѭ��������ѭ��������������ֵ�Ĵ�С�����������еĸ���
		{
			for(i = k; i < n-gap; i = i+gap) //ֱ�Ӳ�������Ĺ���
			{
				temp = pnum[i+gap];			 //ȡtempֵ,
				j = i;						 //���ÿ�ʼ�Ƚϵ�λ��j
				while(j >= 0 && temp <= pnum[j]) //����������˳��
				{
					pnum[j+gap] = pnum[j];	//˳��
					j = j-gap;				//�޸�j
				}
				pnum[j+gap] = temp;			//����temp��ֵ				
			}
		}
		row++;								//�������������1
		if( row ==1) { Output(max);}      //�����һ������Ľ��
	}
}

int main()
{
	int numOfD = 0;				//ϣ����������ֵ
	int aprime;					//����������������ݵĸ����ı���
	int x;						//�����������ݵ������ı���
	ShellSort text;				//ʵ����ShellSort�Ķ���text
	cin>>x;						//�����������ݵ�����
	for(int j=0; j<x; j++)
	{
		int flag=0;
		cin >> aprime;						//�����������ݵĸ���

		int numOfD=text.DValue(aprime);		//����ϣ��������������������͸�������ֵ

		text.Size(aprime);

		int *num = new int[aprime];
		for(int i=0; i<aprime; i++)			//����һ����������
			cin>>num[i];

		text.Value(num,aprime);				//���ݴ���ϣ������
		text.Shellsort(aprime, numOfD);		//ϣ������
		text.Output(aprime);				//���������

		text.Delete();						//�ͷ��ڴ�
		delete [] num;
	}
	return 0;
}