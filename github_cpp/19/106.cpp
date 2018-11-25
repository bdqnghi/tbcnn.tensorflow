#include "Include.h"

using namespace std;


Quicksort::Quicksort(DrawGraphics* graphics){
	
	this->graphics = graphics;

}

Quicksort::~Quicksort(){

}

void Quicksort::start(vector<int>* list, int start, int end, int mode){
	
	if (mode == 0 || mode == 2)
	{
		if (mode == 0)
		{
			time_t elapsed;
			elapsed = clock();
			quicksort(list, start, end);
			elapsed = clock() - elapsed;
			cout << "Das sortieren dauerte: " << (float)elapsed / CLOCKS_PER_SEC << " Sekunden.";
		}
		else
		{
			quicksort(list, start, end);
		}
	}
	else
	{
		graphicQuicksort(list, start, end);
	}

}

void Quicksort::graphicQuicksort(vector<int>* list, int start, int end){

	if (start < end)
	{
		int index = graphicPartition(list, start, end);
		graphicQuicksort(list, start, index - 1);
		graphicQuicksort(list, index + 1, end);
	}

}

int Quicksort::graphicPartition(vector<int>* list, int start, int end){

	int pivot = list->at(end);
	int index = start;
	for (int i = start; i < end; i++)
	{
		if (list->at(i) <= pivot)
		{
			swap(list->at(i), list->at(index));
			graphics->redraw(index);
			index++;
		}
	}
	swap(list->at(index), list->at(end));
	graphics->redraw(index);
	return index;

}

void Quicksort::quicksort(vector<int>* list, int start, int end){

	if (start < end)
	{
		int index = partition(list, start, end);
		quicksort(list, start, index - 1);
		quicksort(list, index + 1, end);
	}

}

int Quicksort::partition(vector<int>* list, int start, int end){

	int pivot = list->at(end);
	int index = start;
	for (int i = start; i < end; i++)
	{
		if (list->at(i) <= pivot)
		{
			swap(list->at(i), list->at(index));
			index++;
		}
	}
	swap(list->at(index), list->at(end));
	return index;

}