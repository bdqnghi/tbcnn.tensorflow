#include"heap.h"


Heap::Heap (constexpr int option)
{
	list = (Event**) calloc(1, sizeof(Event *));;
	list_length = 0;
	this->option = option;
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
	while (child_index > 1 && 
		(std::get<(option)>(*list[child_index-1])> 
		std::get<(option)>(*list[parent_index-1])))
	{
		//tmp = list[child_index-1];
		//list[child_index-1] = list[parent_index-1];
		//list[parent_index-1] = tmp;
		//child_index = parent_index;
		//parent_index = child_index/2;
	}
}


Event * Heap::removeNode () 
{
	void *output = &list[0];
}


void Heap::printHeap () 
{
	if (list_length > 0)
	{
		std::cout << std::get<0>(list[0]->info);
		std::cout << ": " << std::get<1>(list[0]->info);
		std::cout << "-" << std::get<2>(list[0]->info);
	}

	int i = 1;
	while (i < list_length)
	{
		std::cout << ", " << std::get<0>(list[i]->info);
		std::cout << ": " << std::get<1>(list[i]->info);
		std::cout << "-" << std::get<2>(list[i]->info);
		i++;
	}
	std::cout << std::endl;
}
