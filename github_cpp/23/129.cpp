#include "SkipList.h"

template<class  T>
SkipList<T>::SkipList(const T &el, int MaxSize): ITEM_NOT_FOUND(el)
{
  for(maxLevel = 0; MaxSize > 0; MaxSize >>= 1)
    maxLevel++;  // maxLevel = lg(MaxSize) + 1

  root = new nodePtr[maxLevel];

  for (int i = 0; i < maxLevel; i++)
    root[i] = NULL;

  powers = new int[maxLevel];
  choosePowers();
} // SkipList()

template<class  T>
SkipList<T>::~SkipList()
{
  while(!isEmpty())
  {
    nodePtr p = root[0]->next[0];
    delete [] root[0]->next;
    delete root[0];
    root[0] = p;
  } // for each node in the list

  delete [] root;
  delete [] powers;
} // ~SkipList()


template<class T>
void SkipList<T>::choosePowers() {
    powers[maxLevel-1] = (2 << (maxLevel-1)) - 1;  // 2^maxLevel - 1
    for (int i = maxLevel - 2, j = 0; i >= 0; i--, j++)
        powers[i] = powers[i+1] - (2 << j);        // 2^(j+1)
}  // choosePowers()

template<class T>
int SkipList<T>::chooseLevel()
{
    int i, r = (rand() * 32767) % powers[maxLevel-1] + 1;
      // RAND_MAX is 32767 so * 32767 < MAX_INT with 4 byte ints
   
    if(r > 32769)
      r = r;
    for (i = 1; i < maxLevel; i++)
        if (r < powers[i])
            return i - 1; // return a level < the highest level;
    return i - 1;         // return the highest level;
}  // chooseLevel()



template<class T>
T& SkipList<T>::find(const T& info)
{
  nodePtr prev, curr;
  int lvl;

  for (lvl = maxLevel-1; lvl >= 0 && !root[lvl]; lvl--);
    // find the highest non-null level

  prev = curr = root[lvl];
  while (true)
  {
    if (info == curr->info)                   // success if equal;
      return curr->info;
    else
      if (info < curr->info)  // if small then go down a level
      {
        if (lvl == 0)        // if already at bottom level
          return ITEM_NOT_FOUND;
        else
          if (curr == root[lvl])    // if now at root
            curr = root[--lvl];     // start from the next lower root level
          else  // not at root
            curr = *(prev->next + --lvl); // lower level of predecessor
      } // if smaller
      else  // greater than or equal
      {
        prev = curr;           // prepare to go to the next
        if (*(curr->next + lvl) != NULL)  // next at the same level is non-null
           curr = *(curr->next + lvl);   // move to next on the same level
        else // next at the same level is NULL so go down some levels
        {
          for (lvl--; lvl >= 0 && *(curr->next + lvl) == NULL; lvl--);
          if (lvl >= 0)
            curr = *(curr->next + lvl);
          else
            return ITEM_NOT_FOUND;
        }  // else next at the same level is NULL
      } // else greater than or equal
  } // while true
} // find()


template<class T>
void SkipList<T>::insert(const T& info)
{  // does NOT permit duplicates
  nodePtr curr[MAX_LEVELS], prev[MAX_LEVELS], newNode;
  int lvl, i;
  curr[maxLevel-1] = root[maxLevel-1];
  prev[maxLevel-1] = NULL;

  for (lvl = maxLevel - 1; lvl >= 0; lvl--)
  {
    while (curr[lvl] && curr[lvl]->info < info)
    { // go to the next at the same level
      prev[lvl] = curr[lvl];
      curr[lvl] = *(curr[lvl]->next + lvl);
    } // while larger and nodes at this level

    if (curr[lvl] && curr[lvl]->info == info)    // don't include duplicates
      return;

    if (lvl > 0)              // if not at bottom level
    {
			if (prev[lvl] == NULL)       // if prev is root
      {
        curr[lvl - 1] = root[lvl - 1]; // lower curr starts at root
        prev[lvl - 1] = NULL;      // lower prev set to indicate at root
      }
      else // else prev is not root
      {
        curr[lvl - 1] = *(prev[lvl]->next + lvl - 1);
          // lower curr starts at the next of the lower level of the prev
        prev[lvl - 1] = prev[lvl];
          // lower prev set to the prev of this level
      }
    }
  } // for each lvl

  lvl = chooseLevel();        // generate randomly level for newNode;
  // newNode = new SkipListNode<T>; commented out by Sean
  // newNode->next = new nodePtr[sizeof(nodePtr) * (lvl+1)]; commented out by Sean
  // newNode->info  = info;  commented out by Sean
  newNode = new SkipListNode<T>(info, new nodePtr[lvl + 1]); // line substituted by Sean

  for (i = 0; i <= lvl; i++)
  {        // initialize next fields of newNode and reset prev to newNode
    *(newNode->next + i) = curr[i];
    if (prev[i] == NULL) // prev is root
      root[i] = newNode;
    else   // prev is not root
      *(prev[i]->next + i) = newNode;
  }  // each level of the new node.
}  // insert()


template<class T>
bool SkipList<T>::deleteNode(const T& info)
{
  nodePtr curr[MAX_LEVELS], prev[MAX_LEVELS];
  int lvl, foundLevel = -1;

  curr[maxLevel-1] = root[maxLevel-1];
  prev[maxLevel-1] = NULL;

  for (lvl = maxLevel - 1; lvl >= 0; lvl--)
  {
    while (curr[lvl] && curr[lvl]->info < info)
    { // go to the next at the same level
      prev[lvl] = curr[lvl];
      curr[lvl] = *(curr[lvl]->next + lvl);
    } // while larger and nodes at this level

    if (curr[lvl] && curr[lvl]->info == info && foundLevel < 0)    // found at this level
      foundLevel = lvl;

    if (lvl > 0)              // if not at bottom level
    {
			if (prev[lvl] == NULL)       // if prev is root
      {
        curr[lvl - 1] = root[lvl - 1]; // lower curr starts at root
        prev[lvl - 1] = NULL;      // lower prev set to indicate at root
      }
      else // else prev is not root
      {
        curr[lvl - 1] = *(prev[lvl]->next + lvl - 1);
          // lower curr starts at the next of the lower level of the prev
        prev[lvl - 1] = prev[lvl];
          // lower prev set to the prev of this level
      }
    }
  } // for each lvl

  if (foundLevel < 0)
    return false;  // never found info

  for(lvl = 0; lvl <= foundLevel; lvl++)
    if(prev[lvl] != NULL)
      prev[lvl]->next[lvl] = curr[lvl]->next[lvl];
    else
      root[lvl] = curr[lvl]->next[lvl];

  delete [] curr[foundLevel]->next;
  delete curr[foundLevel];
  return true;
} // deleteNode()


