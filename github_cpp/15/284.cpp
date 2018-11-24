#include "Heap.h"
#include <iostream>
#include <cstring>

Heap::Heap()
{
  table = nullptr;
  size = 0;
}

Heap::~Heap()
{
  if(size>0)
    delete[] table;
}

void Heap::push(int value)
{
 if(!isInHeap(value))
 {
  int *newTable = new int[size + 1];
  std::memcpy(newTable, table, size * sizeof(int));
  newTable[size] = value;

  delete[] table;

  table = newTable;

  repairHeap();

  size++;
 }
}

void Heap::pop()
{
  int *newTable = new int[size -1];
  for(int i = 1 ; i<size; i++)
  {
    newTable[i-1] = table[i];
  }
  delete[]table;
  table = newTable;
  repairHeap();
}

bool Heap::isInHeap(int value)
{
  for(int i = 0; i < size; i++)
  {
    if(value == table[i])
    {
      std::cout<<"Wartosc znajduje sie juz w kopcu"<<std::endl;
      return true;
    }
  }
  std::cout<<"Szukanej wartosci nie ma w kopcu"<<std::endl;
  return false;
}
void Heap::printBT(std::string sp, std::string sn, int v)
{
	std::string cr, cl, cp ,s;
	cr = cl = cp = "  ";
	cr[0] = ' '; cr[1] = ' ';
	cl[0] = ' '; cl[1] = ' ';
	cp[0] = ' ';

	if (v < size)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printBT(s + cp, cr, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		std::cout << s << sn << table[v] << std::endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printBT(s + cp, cl, 2 * v + 1);
	}


}
void Heap::display()
{
    printBT("","",0);
}

void Heap::repairHeap()
{
  int temporary = 0;

  for(int i = size; 0 < i; i--)
  {
    if(table[i - 1] < table[i])
    {
      temporary = table[i - 1];
      table[i - 1] = table[i];
      table[i] = temporary;
    }
  }
}
void Heap::removeValue(int value)
{
  int* newTable = new int[size-1];

  for(int i=0;i<size;i++)
  {
    if(table[i] == value)
    {
      for(int k=0;k<i;k++)
      {
        newTable[k] = table[k];
      }
      for(int k=i+1;k<size;k++)
      {
        newTable[k-1] = table[k];
      }
      delete[] table;
      table = newTable;
      size--;
      repairHeap();
      return;
    }
  }
}
