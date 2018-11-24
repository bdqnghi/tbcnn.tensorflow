/////////////////////////////////////////////////////////
// THIS FILE DEFINES ALL THE METHODS TO BE IMPLEMENTED //
// PLEASE GET RID OF ALL THE IMPLEMENT_ME() FUNCTIONS  //
/////////////////////////////////////////////////////////

#include "util.hpp"
#include "hash-table.hpp"
#include <string>

using namespace std;

HashTable::HashTable(int size){
  //cout << "creating a store with size " << size << endl;
  this->size = size;
  numElements = 0;
  hashTable = new DoublyLinkedList*[size];

  for (int i = 0; i < size; i++) {
    hashTable[i] = new DoublyLinkedList();
  }
}

int HashTable::hash(string value){
  //std::cout << "hashing." << std::endl;
  int asciiCount = 0;
  char singleChar = '\0';
  int asciiRep = 0;
  int hashPlacement = 0;

  for (int i = 0; i < (signed)value.size(); i++) {
    singleChar = value.at(i);
    asciiRep = (int) singleChar;
    asciiCount += asciiRep;
  }

  //this is my error for some reason
  hashPlacement = asciiCount % size;
  //hashPlacement = asciiCount % 10;

  //for testing
  //hashPlacement = 10;

  return hashPlacement;
}

void HashTable::resize() {
  //std::cout << "Resizing hash table." << std::endl;

  int s = size;
  int n = numElements;

  /**********************************************************
    This portion of code is for pulling all the old
    elements of the hash table out so that they can
    be deleted and rehashed

    TODO: move this to a seperate private function of its own
  **********************************************************/
  std::string *oldValues = new std::string[numElements];
  int oldValueIndex = 0;
  int hashIndex = 0;

  while (hashIndex < s) {
    if (hashTable[hashIndex]->getFront() != nullptr) {
      Node* temp = hashTable[hashIndex]->getFront();
      while (temp != nullptr) {
        //std::cout << hashIndex << ": " << temp->getValue() << " being put in index " << oldValueIndex << std::endl;
        oldValues[oldValueIndex] = temp->getValue();
        temp = temp->getNext();

        oldValueIndex++;
      }
    }

    hashIndex++;
  }

  //deleteAllElements();
  /***********************************************************
                              END
  ***********************************************************/

  size = getNextPrime((size * 2));
  delete[] hashTable;
  hashTable = new DoublyLinkedList*[size];

  for (int i = 0; i < size; i++) {
    hashTable[i] = new DoublyLinkedList();
    //std::cout << "Node at " << i << std::endl;
  }

  //rehash old elements according to the new size of the hash table
  for (int i = 0; i < n; i++) {
    numElements--;    //gets iterated in putValue() method. This is so elements dont get counted twice
    putValue(oldValues[i]);
  }

delete[] oldValues;
}

int HashTable::getNextPrime(int n) {
  while (1) {
    n++;

    if (isPrime(n)) {
      //std::cout << "New size is:" << n << std::endl;
      return n;
    }
  }

  return n;
}


/*******************************************************************************************************
 * NOTE: I did not write this code myself!
 * Taken and Adapted from https://stackoverflow.com/questions/30052316/find-next-prime-number-algorithm
 * Original author: Zoran Horvat, May 2015
 *******************************************************************************************************
*/
bool HashTable::isPrime(int number) {
  if (number == 2 || number == 3) {
    return true;
  }

  if (number % 2 == 0 || number % 3 == 0) {
    return false;
  }

  int divisor = 6;

  while (divisor * divisor - 2 * divisor + 1 <= number) {
    if (number % (divisor - 1) == 0) {
      return false;
    }

    if (number % (divisor + 1) == 0) {
      return false;
    }

    divisor += 6;
    }

    return true;
}

/*
void HashTable::deleteAllElements() {
  for (int i = 0; i < size; i++) {
    if (hashTable[i]->getFront() != nullptr) {
      delete hashTable[i];
      hashTable[i] = new DoublyLinkedList();
    }
  }
}
*/

void HashTable::putValue(string elem){
  if (numElements > (size / 2)) {
    resize();
  }

  //cout << "adding value " << elem << endl;
  int pos = hash(elem);

  if (hashTable[pos]->getFront() == nullptr) {
    //std::cout << "\nFRONT\n" << std::endl;
    hashTable[pos]->add(elem, 0);
  } else {
    //std::cout << "collision" << std::endl;
    hashTable[pos]->add(elem, 0);
  }

  numElements++;
}

bool HashTable::searchValue(string elem){
  //cout << "seraching for value " << elem << endl;
  int pos = hash(elem);

  if (hashTable[pos]->getFront() == nullptr) {
    return false;
  } else {
    Node* temp = hashTable[pos]->getFront();
    while (temp != nullptr) {
      if (temp->getValue() == elem) {
        return true;
      }
      temp = temp->getNext();
    }
  }
  return false;
}

void HashTable::deleteValue(string elem){
  if (searchValue(elem)) {
    int pos = hash(elem);

    //never will be a nullptr, because I already have used searchValue(), but not bad to double check
    if (hashTable[pos]->getFront() != nullptr) {
      Node* temp = hashTable[pos]->getFront();
      Node* prev = nullptr;
      Node* next = nullptr;

      while (temp != nullptr) {
        if (elem == temp->getValue()) {
          //DELETE IT
          prev = temp->getPrev();
          next = temp->getNext();

          //if first index of linked list
          if (temp == hashTable[pos]->getFront()) {
            hashTable[pos]->setFront(temp->getNext());
            //hashTable[pos]->getFront()->setPrev(nullptr);   //already set to nullptr
            delete temp;
            hashTable[pos]->decrementSize();
          } else {
            if (prev != nullptr) {
              prev->setNext(next);
            }

            if (next != nullptr) {
              next->setPrev(prev);
            }

            delete temp;
            temp = prev;
            hashTable[pos]->decrementSize();
          }
        }

        temp = temp->getNext();
      }
    }
  }
}

void HashTable::print(){
  for (int i = 0; i < size; i++) {
    std::cout << i << " ->";

    hashTable[i]->print();

  }
}
