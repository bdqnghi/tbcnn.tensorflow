#include "Include.h"

using namespace std;


Heapsort::Heapsort(DrawGraphics* graphics){

	this->graphics = graphics;

}

Heapsort::~Heapsort(){

}

void Heapsort::start(vector<int>* list, int n){

	time_t elapsed;
	elapsed = clock();
	build_heap(list, n);
	heapsort(list, n);		
	elapsed = clock() - elapsed;
	cout << "Das sortieren dauerte: " << (float)elapsed / CLOCKS_PER_SEC << " Sekunden.";

}

void Heapsort::max_heapify(vector<int>* list, int i, int n){

	int j, temp;
	temp = list->at(i);
	j = 2 * i;
	while (j <= n)
	{
		if (j < n && list->at(j + 1) > list->at(j))
			j = j + 1;
		if (temp > list->at(j))
			break;
		else if (temp <= list->at(j))
		{
			list->at(j / 2) = list->at(j);
			j = 2 * j;
		}
	}
	list->at(j / 2) = temp;
	return;

}

void Heapsort::heapsort(vector<int>* list, int n)
{
	int i, temp;
	for (i = n; i >= 2; i--)
	{
		swap(list->at(i), list->at(1));
		max_heapify(list, 1, i - 1);
	}

}

void Heapsort::build_heap(vector<int>* list, int n){

	int i;
	for (i = n / 2; i >= 1; i--)
	{
		max_heapify(list, i, n);
	}

}

void Heapsort::graphicMax_heapify(vector<int>* list, int i, int n){

	int j, temp;
	temp = list->at(i);
	j = 2 * i;
	while (j <= n)
	{
		if (j < n && list->at(j + 1) > list->at(j))
			j = j + 1;
		if (temp > list->at(j))
			break;
		else if (temp <= list->at(j))
		{
			list->at(j / 2) = list->at(j);
			j = 2 * j;
		}
	}
	list->at(j / 2) = temp;
	graphics->redraw(j);
	return;

}

void Heapsort::graphicHeapsort(vector<int>* list, int n)
{
	int i, temp;
	for (i = n; i >= 2; i--)
	{
		swap(list->at(i), list->at(1));
		graphics->redraw(i);
		graphicMax_heapify(list, 1, i - 1);
	}

}

void Heapsort::graphicBuild_heap(vector<int>* list, int n){

	int i;
	for (i = n / 2; i >= 1; i--)
	{
		graphicMax_heapify(list, i, n);
	}

}