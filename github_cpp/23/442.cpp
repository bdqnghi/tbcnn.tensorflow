/**
 * Basic Skip List implementation
 * Based on blog: http://codeforces.com/blog/entry/13218
**/ 

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

const int oo = 2e9;

struct skip_list
{
  // Node definition
  struct node
  {
    int val;
    deque <node*> nxt;
    deque <node*> prv;
    node(int val)
      : val(val), nxt(), prv() {} 
  } *begin, *end;

  // Default constructor
  skip_list()
  {
     begin = new node(-oo);
     end   = new node(+oo);
     begin->nxt = {  end};
     begin->prv = { NULL};
     end  ->nxt = { NULL};
     end  ->prv = {begin};
  }

  // find lower_bound of X
  node *find(int x)
  {
    node *cur = begin;
    int lvl = begin->nxt.size();
    while(lvl >= 0)
    {
      while( (lvl<cur->nxt.size()) &&
             (cur->nxt[lvl]->val < x))
      {
        cur = cur->nxt[lvl];
      }
      lvl--;
    }
    return cur->nxt[0];
  }

  // Insert x: Invariant L0 contain all elements
  void insert(int x)
  {
    node *R = find(x);
    node *L = R->prv[0];
    node *it = new node(x);
    int lvl = -1;
    while(lvl==-1 || rand()&1)
    {
      lvl++;
      // Create new level
      if(lvl >= begin->nxt.size())
      {
        begin->nxt.push_back(NULL);
        begin->prv.push_back(NULL);
        end->nxt.push_back(NULL);
        end->prv.push_back(NULL);
      }
      while(lvl >= L->nxt.size()) L = L->prv[lvl-1]; 
      while(lvl >= R->nxt.size()) R = R->nxt[lvl-1];
      L->nxt[lvl] = it;
      R->prv[lvl] = it;
      it->nxt.push_back(R);
      it->prv.push_back(L);
    }

  }

  // Delete element X
  void remove(int x)
  {
    node *it = find(x);
    for(int i=0; i<it->nxt.size(); ++i)
    {
      it->nxt[i]->prv[i] = it->prv[i];
      it->prv[i]->nxt[i] = it->nxt[i];
    }
    delete it;
    it = NULL;
  }
}; 

int main() {
  skip_list SL;
  skip_list::node* nd;
  
  SL.insert( 5);
  SL.insert( 4);
  SL.insert(11);
  SL.insert( 9);
  SL.insert(14);
  SL.insert( 7);
  SL.insert( 6);
  SL.insert( 1);
  SL.insert( 2);

  SL.remove(5);
  nd = SL.find(5);
  printf("%d\n",nd->val);
  return 0;
}


