#include"BuforsHeapSort.h"

BuforsHeapSort::BuforsHeapSort()
{
	bufors = nullptr;
	amountOfBufors = 0;
	amountOfRecords = 0;
	buforSize = 0;
	heapSortIndex = 0;
}

BuforsHeapSort::BuforsHeapSort(Bufor* bufors, int amountOfBufors)
{
	this->bufors = bufors;
	heapSortIndex = 0;
	this->amountOfBufors = amountOfBufors;
	for (int i = 0; i < amountOfBufors; i++)
	{
		heapSortIndex += bufors[i].getAmountOfRecords();
	}
	buforSize = bufors[0].getSize();		
	amountOfRecords = heapSortIndex;
}

void BuforsHeapSort::setHeapSortIndex(int amountOfBufors)
{
	for (int i = 0; i < amountOfBufors; i++)
	{
		heapSortIndex += bufors[i].getAmountOfRecords();
	}
}

int BuforsHeapSort::getHeapSortIndex() { return heapSortIndex; }

void BuforsHeapSort::heapify(int indx)
{
	Record temporary;
	Record null;
	Record* parent, *leftSon, *rightSon;
	RecordPosition position;
	position = getIndexOfRecord(indx);
	parent = bufors[position.buforIndex].getRecord(position.recordIndex);
	position = getIndexOfRecord(2 * indx + 1);
	leftSon = bufors[position.buforIndex].getRecord(position.recordIndex);
	if (2*indx + 2 < heapSortIndex)
	{
		position = getIndexOfRecord(2 * indx + 2);
		rightSon = bufors[position.buforIndex].getRecord(position.recordIndex);
	}
	else
	{
		rightSon = &null;
	}
	// check if right exists
	if (rightSon->isNull())
	{
		temporary = *parent;
		if (*leftSon > *parent)
		{
			*parent = *leftSon;
			*leftSon = temporary;
			if (2 * indx + 1 <= (heapSortIndex - 2) / 2)
			{
				heapify(2 * indx + 1);
			}
		}
	}
	else
	{
		temporary = *parent;
		if (*leftSon > *rightSon && *leftSon > *parent)
		{
			*parent = *leftSon;
			*leftSon = temporary;
			if (2 * indx + 1 <= (heapSortIndex - 2) / 2)
			{
				heapify(2 * indx + 1);
			}
		}
		else if (*leftSon <= *rightSon && *rightSon > *parent)
		{
			*parent = *rightSon;
			*rightSon = temporary;
			if (2 * indx + 2 <= (heapSortIndex - 2) / 2)
			{
				heapify(2 * indx + 2);
			}
		}
	}
}

void BuforsHeapSort::correctEndOfHeap()
{
	Record temporary;
	Record* parent, *leftSon;
	RecordPosition position;
	position = getIndexOfRecord(0);
	parent = bufors[position.buforIndex].getRecord(position.recordIndex);
	position = getIndexOfRecord(1);
	leftSon = bufors[position.buforIndex].getRecord(position.recordIndex);
	temporary = *parent;
	if (*leftSon < *parent)
	{
		*parent = *leftSon;
		*leftSon = temporary;
	}
}

void BuforsHeapSort::buildHeap()
{
	for (int i = (heapSortIndex - 2) / 2; i >= 0; i--)
	{
		heapify(i);
	}
}

void BuforsHeapSort::heapSort()
{
	buildHeap();
	heapSortIndex = amountOfRecords - 1;
	Record temporary;
	Record *root, *last;
	RecordPosition position;
	position = getIndexOfRecord(0);
	root = bufors[position.buforIndex].getRecord(position.recordIndex);
	for (int i = heapSortIndex; i > 1; i--)
	{
		position = getIndexOfRecord(i);
		last = bufors[position.buforIndex].getRecord(position.recordIndex);
		temporary = *root;
		*root = *last;
		*last = temporary;
		heapify(0);
		heapSortIndex--;
	}
	correctEndOfHeap();
	heapSortIndex--;
}