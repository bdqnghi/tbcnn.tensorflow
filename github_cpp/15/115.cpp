#include"heap.h"


Heap::Heap (int (* comp)(Event *, Event *))
{
	list = (Event**) calloc(1, sizeof(Event *));;
	list_length = 0;
	this->comp = comp;
}

/*
 Creates a new node with the paramter and adds it to the heap.
 */
void Heap::addNode (Event *element) 
{	
	list_length++;
	if (list_length == 1)
	{
		//list[0] = calloc(1, sizeof(Event));
		list[0] = element;
		return;
	}
	else
	{
		list = (Event**) realloc(list, sizeof(Event*)*list_length);
		list[list_length-1] = element;
	}

	int child_index = list_length;
	int parent_index = child_index/2;
	Event *tmp;
	std::cout << "Child: " << child_index << " Parent: " << parent_index;
	std::cout  << std::endl;
	while (child_index > 1 && 
		comp(list[child_index-1], list[parent_index-1]) > 0)
	{
		std::cout << "Inside" << std::endl;
		tmp = list[child_index-1];
		list[child_index-1] = list[parent_index-1];
		list[parent_index-1] = tmp;
		child_index = parent_index;
		parent_index = child_index/2;
	}
	
}


Event * Heap::removeNode () 
{
	void *output = &list[0];
}


void Heap::printHeap () 
{	
	std::cout << "In Print function\n";
	if (list_length > 0)
	{
		std::cout << list[0]->description;
		std::cout << ": " << list[0]->start_time;
		std::cout << "-" << list[0]->finish_time;
	}

	int i = 1;
	while (i < list_length)
	{
		std::cout << ", " << list[i]->description;
		std::cout << ": " << list[i]->start_time;
		std::cout << "-" << list[i]->finish_time;
		i++;
	}
	std::cout << std::endl;
}
