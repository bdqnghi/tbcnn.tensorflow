#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node
{
     int val;
     Node * next;
};

class IntList {
private:
     Node * head;
public:
     /* Class to access the elements of the list. We need a seperate class
      * for this as we want to keep the pointers to the nodes private.
      */
     class Iterator {
     private:
	  Node * node;
     public:
	  /* Constructor */
	  Iterator();
	  /* Copy constructor */
	  Iterator(const Iterator & iter)
	       {
		    node = iter

	  /* Assignment operator */
	  Iterator operator=(const Iterator &);

	  /* Prefix and postfix operators, to move forward in the list
	   */
	  Iterator operator++();
	  Iterator operator++(int);
           
	  /* Operators to return elements contained in the list */
	  int &operator*();
	  node *operator->();

	  /* Operators to compare two iterators */
	  bool operator==(Iterator &) const;
	  bool operator!=(Iterator &) const;
     };
public:
     /* Constructor */
     IntList();

     /* Copy constructor */
     IntList(const IntList &);

     /* Assignment Operator */
     IntList &operator=(const IntList &);

     /* Function to check if the list is empty */
     bool empty() const;
     /* Function to return the number of elements */
     unsigned int size() const;
        
     /* Functions to add an element to the start and end of the list */
     void push_back(int);
     void push_front(int);

     /* Functions to remove an element from the start and end of the list */
     int pop_back();
     int pop_front();

     /* Function to delete all elements from the list */
     void clear();

     /* Functions to start and end an iteration
      * begin returns an Iterator corresponding to the first element
      *
      * end should return an element that indicates that iterator is
      * complete. That is it should return the value obtained on
      * incrementing an iterator corresponding to the last element.
      */
     Iterator first() const;
     Iterator end() const;

     /* insert adds an element after the given iterator */
     void insert(const Iterator &);
     void remove(Iterator &);
     /* remove, deletes the element at the iterator and moves the iterator
      * to the next element
      */

     /* Destructor to delete elements */
     ~IntList();
};



int main(){
     return 0;
}
