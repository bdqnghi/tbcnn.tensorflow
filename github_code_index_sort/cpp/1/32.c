#include "LinkedList.h"
#include <stdexcept>

InsertionSortNS::LinkedList::LinkedList() {
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}

// TODO: Does this properly destroy? Just added the tail pointer
InsertionSortNS::LinkedList::~LinkedList() {
	if (this->head) {
		InsertionSortNS::Node* current = head;
		InsertionSortNS::Node* next = current->getNext();
		delete current;
		while (next) {
			current = next;
			next = current->getNext();
			delete current;
		}
		head = NULL;
		tail = NULL;
		this->length = 0;
	}
}

void InsertionSortNS::LinkedList::push_back(InsertionSortNS::NodeData data) {
	if (!this->head) {
		InsertionSortNS::Node* newNode = new InsertionSortNS::Node(data);
		this->head = newNode;
		this->tail = newNode;
		head->setNext(0);
		tail->setNext(0);
	}
	else {
		InsertionSortNS::Node* newNode = new InsertionSortNS::Node(data);
		tail->setNext(newNode);
		tail = newNode;
	}
	++length;
}

void InsertionSortNS::LinkedList::insert(int index, InsertionSortNS::NodeData data) {
	if (this->size() < index || index < 0) {
		throw std::out_of_range("Index out of bounds");
	}
	else {
		InsertionSortNS::Node* newNode = new InsertionSortNS::Node(data);
		int counter = 0;
		InsertionSortNS::Node* current = head;
		InsertionSortNS::Node* previous = NULL;
		while (counter != index) {
			previous = current;
			current = current->getNext();
			counter++;
		}

		// Inserting to HEAD
		if (!previous) {
			newNode->setNext(current);
			head = newNode;
			if (!head->getNext()) {
				tail = head;
			}
		} else if (!current) { // INSERTING TAIL
			previous->setNext(newNode);
			tail = newNode;
		}
		else { // Inserting MIDDLE
			previous->setNext(newNode);
			newNode->setNext(current);
		}
		++length;
	}
}
InsertionSortNS::NodeData InsertionSortNS::LinkedList::remove(int index) {
	// TODO: Test ArrayOutOfBounds
	if (this->size() <= index || index < 0) {
		throw std::out_of_range("Index out of bounds");
	} else {
		int counter = 0;
		InsertionSortNS::Node* current = head;
		InsertionSortNS::Node* previous = NULL;
		while (counter != index) {
			previous = current;
			current = current->getNext();
			counter++;
		}
		InsertionSortNS::NodeData data = current->getData();
		
		if (!previous) { // Deleting HEAD
			// TODO: Will this work in a one element list?
			head = current->getNext();
			if (!current->getNext()) {
				tail = head;
			}
			delete current;
			current = NULL;
		}
		else if (!current->getNext()) { // Deleting TAIL
			previous->setNext(0);
			tail = previous;
			delete current;
			current = NULL;
		}
		else { // Deleting middle
			previous->setNext(current->getNext());
			delete current;
			current = NULL;
		}
		--length;
		return data;
	}
}

InsertionSortNS::NodeData InsertionSortNS::LinkedList::get(int index) {
	// TODO: Test ArrayOutOfBounds
	if (this->size() <= index || index < 0) {
		throw std::out_of_range("Index out of bounds");
	}
	else {
		int counter = 0;
		InsertionSortNS::Node* current = head;
		while (current->getNext() && counter != index) {
			current = current->getNext();
			counter++;
		}
		return current->getData();
	}
}

int InsertionSortNS::LinkedList::size() {
	return static_cast<int>(this->length);
}

// TODO: Does this work as expected?
void InsertionSortNS::LinkedList::clear() {
	this->~LinkedList();
}


void InsertionSortNS::LinkedList::merge(InsertionSortNS::LinkedList* other)
{
  for(int i=0; other->size()!=0;i++)
    {
      this->push_back(other->remove(0));
    }
}
