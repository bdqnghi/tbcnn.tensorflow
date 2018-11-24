//Cho A la cac ky hieu va trong so cua chung.
//tim mot bo ma tien to voi tong do dai ma hoa la nho nhat.

#include <iostream>
#include <string>

using namespace std;

string A[100];
int n;
int S[100];
void Init()
{
	cout<<"Nhap so luong phan tu";
	cin>>n;
	for(int i = 0;i<n;i++)
	{
		cout<<"chu cai thu "<<i+1<<":";
		cin>>A[i];
	}
	for(int i = 0;i<n;i++)
	{
		cout<<"Trong so cua ky tu "<<A[i]<<" la: ";
		cin>>S[i];
	}
}
void Geedy()
{
	
}
void Result()
{
	for(int i = 0;i<n;i++)
	{
		cout<<A[i]<<" ";
	}
	cout<<endl;
	for(int i = 0;i<n;i++)
	{
		cout<<S[i]<<" ";
	}
}
int main()
{
	Init();
	Result();
	
}
