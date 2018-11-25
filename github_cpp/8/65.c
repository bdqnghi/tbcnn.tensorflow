#include "TopologicalSort.h"

int* TopologicalSort::Sort(int count, TList<Condition>* conditions)
{
	_count = count;
	
	CreatePrecursors();
	CreateLinks();
	FillLinksAndPrecursors(conditions);
	AddFirstCandidates();

	
	int* ordered = SortByOrder();

	
	DeleteArrays();

	return ordered;
}


void TopologicalSort::CreatePrecursors()
{
	_precursors = new int[_count];
	for(int i = 0; i < _count; i++)
	{
		_precursors[i] = 0;
	}
}


void TopologicalSort::CreateLinks()
{
	_links = new TList<int>*[_count];
	for (int i = 0; i < _count; i++)
	{
		_links[i] = new TList<int>();
	}
}


void TopologicalSort::FillLinksAndPrecursors( TList<Condition>* conditions )
{
	int conditionsCount = conditions->GetCount();
	for (int i = 0; i < conditionsCount; i++)
	{
		Condition condition = conditions->GetElement(i);
		_links[condition.first-1]->Add(condition.second);
		_precursors[condition.second-1]++;
	}
}


void TopologicalSort::AddFirstCandidates()
{
	_candidates = new TStack<int>();
	for (int i = 0; i < _count; i++)
	{
		if (_precursors[i] == 0)
		{
			_candidates->Push(i+1);
		}
	}
}

int* TopologicalSort::SortByOrder()
{
	int* ordered = new int[_count];
	int currentOrder = 0;
	
	while (_candidates->GetCount() > 0)
	{
		
		int toAdd = _candidates->Pop();
		ordered[currentOrder] = toAdd;
		currentOrder++;

		
		TList<int>* successors = _links[toAdd-1];
		int successorsCount = successors->GetCount();
		for (int i = 0; i < successorsCount; i++)
		{
			int successor = successors->GetElement(i);
			_precursors[successor-1]--;
			if (_precursors[successor-1] == 0)
			{
				_candidates->Push(successor);
			}
		}
	}

	
	if (currentOrder != _count)
	{
		delete ordered;
		return NULL;
	}

	return ordered;
}

void TopologicalSort::DeleteArrays()
{
	delete _precursors;
	delete _candidates;
	for (int i = 0; i < _count; i++)
	{
		delete _links[i];
	}
	delete _links;
}
