#include"shellSort.h"

shellSort::shellSort()
{

}
shellSort::shellSort(const shellSort& s)
{

}
shellSort& shellSort::operator=(const shellSort& s)
{

}
shellSort* shellSort::getInstance()
{
	static shellSort instance;
	return &instance;
}

void shellSort::sort(int *p,int sum,int factor)
{
	int d=factor>sum/2?factor:sum/2;
	while(d>0)
	{
		for(int i=d;i<sum;i++)
		{
			int j=i-d;
			while(j>=0&&p[j]>p[j+d])
			{
				int tmp = p[j];
				p[j] = p[j+d];
				p[j+d] = tmp;
				j=j-d;
			}
		}
		
		/*
		for(int i=d;i<sum;i++)
		{
			if(p[i]<p[i-d])
			{
				int j =i-d;
				int x = p[i];
				p[i] = p[i-d];
				while(j>=0&&x<p[j]){
					p[j+d] = p[j];
					j-=d;
				}
				p[j+d] =x;
			}
		}*/

		d= d/2;
	}
}
