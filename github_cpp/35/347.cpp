#include <iostream>
#include <cassert>

using namespace std;

class link{
private:
	link(int x, link * ptr);
	link();
	int val;
	link * next;
	link * prev;
	friend class Iterator;
	friend class List;
};

class Iterator{
public:
	void operator--();
	void operator++();
	int & operator*();
private:
	Iterator(link * a);
	link * it;
	friend class List;
};

class List{
	public:
		List();
		~List();
		bool empty();
		void push_back(int x);
		void push_front(int x);
		int size();
		void pop_back();
		void pop_front();
		Iterator begin();
		Iterator end();
		void insert(Iterator & i, int x);
		Iterator erase(Iterator i);
	private:
		link * start;
		link * finish;
};

link::link(){
	val = 0;
	next = nullptr;
	prev = nullptr;
}

link::link(int x, link * ptr){
	val = x;
	next = ptr;
}

Iterator::Iterator(link * a){
	it = a;
}

void Iterator::operator++(){
	it = it->next;
}

void Iterator::operator--(){
	it = it->prev;
}

int & Iterator::operator*(){
	return it->val;
}

List::List(){
	start = nullptr;
	finish = nullptr;
}

List::~List(){
	if(!empty()){
		link * ptr = start;
		while (ptr != finish){
			ptr = ptr->next;
			delete ptr->prev;
		}
	}
	delete finish;
}

bool List::empty(){
	return (start == nullptr);
}

void List::push_back(int x){
	link * a = new link();
	a->val = x;
	if (empty()){
		start = a;
		finish = a;
	}
	finish->next = a;
	a->prev = finish;
	finish = a;
}

void List::push_front(int x){
	link * a = new link();
	a->val = x;
	if(empty()){
		start = a;
		finish = a;
	}
	a->next = start;
	start->prev = a;
	start = a;
}

int List::size(){
	int s = 1;
	link*ptr = start;
	while(ptr != finish){
		ptr = ptr->next;
		s++;
	}
	if(start == nullptr) s=0;
	return s;
}

void List::pop_back(){
	if(size() == 1) {
		delete finish;
		start = nullptr;
		finish = nullptr;
		return;
	}
	finish = finish->prev;
	delete finish->next;
}

void List::pop_front(){
	if(size() == 1) {
		delete start;
		finish = nullptr;
		start = nullptr;
		return;
	}
	start = start->next;
	delete start->prev;
	}

Iterator List::begin(){
	if (start == nullptr) return Iterator (nullptr);
	return Iterator(start);
}

Iterator List::end(){
	if (finish == nullptr) return Iterator (nullptr);
	return Iterator(finish);
}

void List::insert(Iterator & i, int x){
	link * a = new link ();
	a->val = x;
	if(empty()){
		start = a;
		finish = a;
		i.it = a;
	}
	else if(i.it->next == nullptr){
		a->prev = i.it;
		i.it->next = a;
		i.it = a;
		finish = a;
	}
	else{
		a->prev = i.it;
		a->next = i.it->next;
		i.it->next->prev=a;
		i.it->next = a;
		i.it = a;
  }
}

Iterator List::erase(Iterator i){
	if(i.it == nullptr) return i;
	else if(i.it->prev == nullptr && i.it->next == nullptr){
		start = nullptr;
		finish = nullptr;
	Iterator temp = Iterator(nullptr);
		delete i.it;
		return temp;
	}
	else if(i.it->prev == nullptr){
		Iterator temp = i.it->next;
		start = temp.it;
		temp.it->prev = nullptr;
		delete i.it;
		return temp;
	}
	else if(i.it->next == nullptr){
		Iterator temp = i.it->prev;
		finish = temp.it;
		temp.it->next = nullptr;
		delete i.it;
		return temp;
	}
	i.it->next->prev = i.it->prev;
	i.it->prev->next = i.it->next;
	Iterator temp = i.it->prev;
	delete i.it;
	return temp;
}


int main(int argc, char * args[]) {
	List a;
	Iterator it = a.begin();

	//tests for an empty list
	assert (a.empty());
	assert (a.size() == 0);

	//tests push_back and push_front functions
	a.push_back(4);
	a.push_back(5);
	it=a.begin(); 
	assert (*it == 4);
	++it;
	assert (*it == 5);
	--it;
	assert (*it == 4);
	assert (a.size() == 2);
	a.push_front(3);
	a.push_front(2);
	a.push_front(1);
	a.push_back(6);
	--it;
	--it;
	--it;
	for(int x = 1; x <= 6; x++) {
		assert(*it == x);
		++it;
	}

	//tests pop functions
	a.pop_front();
	a.pop_front();
	it = a.begin();
	assert(*it == 3);
	a.pop_back();
	a.pop_back();
	it = a.end();
	assert(*it == 4);
	a.pop_back();
	a.pop_front();
	assert(a.empty());

	//tests insert and erase functions
	it = a.begin();
	a.insert(it, 3);
	a.push_front(1);
	a.insert(it, 4);
	it = a.begin(); 
	a.insert(it, 2);
	assert(*it == 2);
	it = a.end();
	assert (*it==4);
	--it;
 	assert (*it==3);
	--it; 
	assert(*it == 2);
	--it;
	assert(*it == 1);
	
	it = a.erase(it);
	assert(*it == 2);
	++it;
	assert(*it == 3);
	it = a.end();
	it = a.erase(it);
	assert(*it == 3);
	it = a.begin();
	it = a.erase(it);
	assert(*it == 3);
	assert(a.size() == 1);
	it = a.erase(it);
	assert(a.empty());

	cout << "all tests passed" << endl;
}
