/**
* Copyright(c)
* All rights reserved
* Author: hy
* Date: 2018-09-26-18.08
*/
#include<iostream>
using namespace std;
// n ��ʾ���������count��ʾ���뼸������
int n;
int count=0;

/**
* @params i,j �������ʼ�����
* @params s ��¼��(i,j)��С����ʱ�ĶϿ�λ��
*/
void Traceback(int i, int j, int(*s)[100])
{
    if (i==j)
    {
        cout<<"A"<<i;
        return;
    }
    // ���߲����(
    if (i>1 || j<n)
        cout<<"(";
    // �ݹ����
    Traceback(i,s[i][j],s);
    Traceback(s[i][j]+1,j,s);
    // ���߲����)
    if (i>1 || j<n)
        cout<<")";
}

int main()
{
    // p ���������洢n������Ľ���
    int p[100] = {0};
    while(cin>>n)
    {
        // ��ʾ��С���˴��� m[i][j] ��ʾ ��i������͵�j������֮�����С����
        int m[100][100] = {0};
        count++;
        if(n==1)
        {
            // ���ǵ�ֻ��һ������ʱ���������
            cin>>p[0]>>p[1];
            m[1][1] = p[0]*p[1];
        }
        else
        {
            for(int i=0; i<=n; i++)
            {
                cin>>p[i];
            }
        }
        // ��Ӧ����С���˴�����Ӧ�ĶϿ�λ��
        int s[100][100] = {0};
        // �����ھ���ļ��Ϊ2��ʼһ��һ������
        for(int r=2; r<=n; r++)
        {
            // ������
            for(int i=1; i<=n-r+1; i++)
            {
                // ������
                int j = i+r-1;
                // ��[i][j] �Ͽ�Ϊ[i,i+1]��[i+1][j]
                m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
                // ��¼��(i,j)����i���Ͽ�������С����
                s[i][j]=i;
                for(int k=i+1; k<j; k++)
                {
                    // ����k
                    // ��[i][j]�Ͽ�Ϊ[i][k]��[k+1][j]
                    int temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                    // ��k�ı����͵�һ����i+1���Ͽ��Ƚ�
                    if(temp<m[i][j])
                    {
                        m[i][j] = temp;
                        // ��¼��(i,j)����k���Ͽ�������С����
                        s[i][j] = k;
                    }
                }
            }
        }
        cout<<"Case "<<count<<endl;
        cout<<m[1][n]<<" ";
        Traceback(1,n,s);
        cout<<endl;
    }
    return 0;
}
