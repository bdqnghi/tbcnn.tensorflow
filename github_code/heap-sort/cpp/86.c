#include<iostream>
using namespace std;

void heapify (int *tab, int heap_size, int i)
{
int largest, temp;
int l=2*i, r=(2*i)+1;
if (l<=heap_size && tab[l]>tab[i])
largest=l;
else largest=i;
if (r<=heap_size && tab[r]>tab[largest])
largest=r;
if (largest!=i)
{
temp=tab[largest];
tab[largest]=tab[i];
tab[i]=temp;
heapify(tab,heap_size,largest);
}
}
void budKopiec(int *tab, int rozmiar)
{
for (int i=rozmiar/2;i>0;i--)
heapify(tab,rozmiar, i);
}

void sort(int *tab, int rozmiar)
{
int temp;
budKopiec(tab, rozmiar);
for (int i=rozmiar;i>1;i--)
{
temp=tab[i];
tab[i]=tab[1];
tab[1]=temp;
rozmiar--;
heapify(tab,rozmiar,1);
}
}

int main()
{
int rozmiar;
cin>>rozmiar;
int *tab=new int[rozmiar+1];

for (int i=1;i<=rozmiar;i++)
cin>>tab[i];

sort (tab,rozmiar);

for (int i=1;i<=rozmiar;i++)
cout<<tab[i] << "dsadfasf aswgy1 ";
cout << endl;

return 0;
}
