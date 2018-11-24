#include <iostream>
#include <string>
using namespace std;

template <class T>
class HashEntry{
	public:
		HashEntry(int key, T value){
			this->key = key;
			this->value = value;
			this->next = NULL;
		}
		
		~HashEntry(){
			if(this->getNext() != NULL){
				delete this->getNext();
			}
		}
		
		int getKey(){
			return this->key;
		}
		
		T getValue(){
			return this->value;
		}
		
		HashEntry<T> * getNext(){
			return this->next;
		}
		
		void setNext(HashEntry<T> * next){
			this->next = next;
		}
		
	private:
		int key;
		T value;
		HashEntry<T> *next;
};

const int TABLE_SIZE = 8;
template <class T>
class HashTable{
	public:
		HashTable(){
			this->table = new HashEntry<T>*[TABLE_SIZE];
			for(int i=0;i<TABLE_SIZE;i++){
				this->table[i] = NULL;
			}
		}
		
		~HashTable(){
			for(int i=0;i<TABLE_SIZE;i++){
				if(this->table[i] != NULL){
					delete this->table[i];
				}
			}
			delete[] this->table;
		}
		
		T get(int key){
			HashEntry<T> *h = this->table[this->slot(key)];
			while((h != NULL) && (h->getKey() != key)){
				h = h->getNext();
			}
			if(h != NULL){
				return h->getValue();
			}
			else{
				return NULL;
			}
		}
		
		void set(int key, T value){
			int slot = this->slot(key);
			HashEntry<T> *h = new HashEntry<T>(key, value);
			h->setNext(this->table[slot]);
			this->table[slot] = h;
		}
	private:
		HashEntry<T> **table;
		
		int slot(int key){
			return (key % TABLE_SIZE);
		}
};

int main(){
	HashTable<string> *h = new HashTable<string>();
	h->set(1, "Hello");
	h->set(129, " There");
	cout << h->get(1) << h->get(129) << endl;
	delete h;
}