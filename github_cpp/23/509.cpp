#include<iostream>
#include<cstdlib>
#include<ctime>
#include<bits/stdc++.h>

using namespace std;


class Node {
   public:
     int val;
     Node **next;//array of next pointers
     Node(int v, int level);
     ~Node();
};

Node::~Node()
{
  delete[] next;
}

Node::Node(int v, int level)
{
    val = v;
    next = new Node*[level+1];
    memset(next, 0, sizeof(Node*)*(level+1));
}

class SkipList{
     public:
      int max_level;//max number of levels
      int cur_level; //current level
      float p;//fraction of nodes that have a val
      Node *head;
      SkipList(int max_num_levels, float fraction);
      void insertElement(int value);
      void displaySkipList();
      void deleteElement(int value);
      bool findElement(int value);
      int randomLevel();
      ~SkipList();
};

SkipList::~SkipList()
{
  Node *temp = head, *prev =NULL;
  while(temp){
   prev = temp;
   temp = temp->next[0]; 
   delete prev;
  }
}

SkipList::SkipList(int max_num_levels, float fraction)
{
   max_level = max_num_levels;
   cur_level = 0;
   p = fraction;
   head = new Node(-1, max_level);
}

int SkipList::randomLevel()
{
  int level = 0;
  float fraction = (float)rand () / RAND_MAX;
  while (fraction < p && level < max_level)
    {
      level++;
      fraction = (float)rand () / RAND_MAX;
    }
  return level;
}

bool SkipList::findElement(int val)
{
  for (int i = cur_level; i >= 0; i--)
    {
      Node *temp = head->next[i];
      while (temp)
	{
	  if (temp->val == val)
	    {
	      return true;
	    }
	  else if (temp->val < val)
	    {
	      temp = temp->next[i];
	    }
	  else
	    {
	      break;
	    }
	}
    }
  return false;
}

void SkipList::insertElement(int value)
{
  int rlevel = randomLevel ();
  Node *nnode = new Node (value, rlevel);
  if(cur_level < rlevel)
    cur_level = rlevel;

  for (int i = 0; i < rlevel + 1; i++)
    {
      Node *temp = head;
      while (temp->next[i] != NULL && temp->next[i]->val < value)
	{
	  temp = temp->next[i];
	}
      if (temp->next[i] == NULL)
	{
	  temp->next[i] = nnode;
	}
      else
	{
	  nnode->next[i] = temp->next[i];
	  temp->next[i] = nnode;
	}
    }
}

void SkipList::displaySkipList()
{
  for (int i = cur_level; i >= 0; i--)
    {
      Node *temp = head->next[i];
      cout<<i<<") ";
      while (temp)
	{
          cout<<temp->val;
          if(temp->next[i])
             cout<<"->";          
             temp = temp->next[i];
	}
        cout<<endl;
    }
}

void SkipList::deleteElement(int value)
{
  Node *element = NULL;
  for (int i = cur_level; i >= 0; i--)
    {
      Node *temp = head;
      while (temp->next[i] != NULL && temp->next[i]->val < value)
	{
	  temp = temp->next[i];
	}
      if (temp->next[i] && temp->next[i]->val == value)
	{
	  if (element == NULL){
	    element = temp->next[i];
            if(head->next[i] == element && 
               head->next[i]->next[i]==NULL &&
               i == cur_level)
                 cur_level--;
          }
	  temp->next[i] = temp->next[i]->next[i];
	}
    }
  delete element;
}

int main(int argc, char *argv[])
{
  srand(time(0));

  SkipList *sp = new SkipList(5,0.5);
#if 0
  int n = 0;
  cout<<"Enter number of values < 1000:";
  cin >> n;
  while(n){
   sp->insertElement(rand()%1000);
   n--;
  }
#endif
  sp->insertElement(26);
  sp->insertElement(21);
  sp->insertElement(19);
  sp->insertElement(17);
  sp->insertElement(12);
  sp->insertElement(9);
  sp->insertElement(7);
  sp->insertElement(6);
  sp->insertElement(3);
  sp->insertElement(25);
  sp->displaySkipList();

  cout<<"Find 24:"<<(sp->findElement(24)?"true":"false")<<endl;
  cout<<"Find 21:"<<(sp->findElement(21)?"true":"false")<<endl;
  sp->deleteElement(21);
  sp->displaySkipList();
  delete sp;
  return 0;
}
