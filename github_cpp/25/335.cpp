#include "Permutation.h"
using CSC2110::Permutation;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;

Permutation::Permutation(int q, int n)
{
   random = Random::getRandom();

   r = q;
   numbers = new ListArray<Integer>();
   for (int i = 1; i <= n; i++)
   {
      Integer* num = new Integer(i);
      numbers->add(num);
   }
}

Permutation::~Permutation()
{
   ListArrayIterator<Integer>* iter = numbers->iterator();
   while(iter->hasNext())
   {
      Integer* i = iter->next();
      delete i;
   }
   delete iter;
   delete numbers;
}

int Permutation::next()
{
   if (r == 0) return -1;

   int rand = random->getRandomInt(1, numbers->size());
   Integer* num = numbers->get(rand);
   int value = num->getValue();
   numbers->remove(rand);
   delete num;
   r--;

   return value;
}
