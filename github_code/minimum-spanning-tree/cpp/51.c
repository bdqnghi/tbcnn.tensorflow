#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define MAX 1000000

int parent[MAX];

int find_parent(int a)
{
	return parent[a] == a ? a : parent[a] = find_parent(parent[a]);
}

struct Arista
{
	int origen;
	int destino;
	int peso;

	Arista(){}

	Arista(int a, int b, int c)
	{
		origen = a;
		destino = b;
		peso = c;
	}

	void leer()
	{
		cin>>origen>>destino>>peso;
		parent[origen] = origen;
		parent[destino] = destino;
	}

	void print()
	{
		cout<<"De "<<origen<<" a "<<destino<<" con peso "<<peso<<endl;
	}
};

bool orden (Arista a, Arista b)
{
	return a.peso < b.peso;
}

int main()
{
	int nAristas;

	cin>>nAristas;
	
	Arista aristas[nAristas];

	for (int i = 0; i < nAristas; i++)
		aristas[i].leer();

	sort(aristas, aristas + nAristas, orden);

	vector <Arista> minimumSpanningTree;

	for (int i = 0; i < nAristas; i++)
	{
		int parentA, parentB;

		parentA = find_parent(aristas[i].origen);
		parentB = find_parent(aristas[i].destino);

		if (parentA != parentB)
		{
			parent[parentA] = parentB;
			minimumSpanningTree.push_back(aristas[i]);
		}
	}

	int sumTotal = 0;

	for (int i = 0; i < minimumSpanningTree.size(); i++)
	{
		minimumSpanningTree[i].print();
		sumTotal += minimumSpanningTree[i].peso;
	}

	cout<<"Peso Total = "<<sumTotal<<endl;

	return 0;
}