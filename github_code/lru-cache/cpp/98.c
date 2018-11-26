/*
 * LRUCache.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: chenhaoliu
 */

#include <vector>
#include "LRUCache.h"
#include <map>

using namespace std;

LRUCache::LRUCache(size_t size) {
	limit_size = size;
	current_size = 0;
	hashmap = new map<string,Node<string,string>*>;

	head = new Node<string,string>;
	tail = new Node<string,string>;

	head->next = tail;
	head->prev = NULL;

	tail->next = NULL;
	tail->prev = head;
}
LRUCache:: ~LRUCache() {
	delete hashmap;
	delete head;
	delete tail;
	for (size_t i = 0; i < entries.size(); ++i) {
		delete entries.at(i);
	}
}
size_t LRUCache::getSize() {
	return current_size;
}
string LRUCache::getRecent() {
	return head->next->key;
}
string LRUCache::getOld() {
	return tail->prev->key;
}
bool LRUCache::contains(string key) {
	Node<string,string>* node = (*hashmap)[key];
	if (node) { // if the key is already in the cache
		return true;
	} else {
		return false;
	}
}
string LRUCache::get(string key) {
	Node<string,string>* node = (*hashmap)[key];
	if (node) { // if the key is already in the cache
		detach(node);
		attach(node);
		return node->data;
	} else {
		return "";
	}
}
void LRUCache::put(string key, string data) {
	if (data.size() > limit_size) { // if the data size is larger than the size of the cache
		return;
	}
	Node<string,string>* node = new Node<string,string>;
	entries.push_back(node);
	while (isFull(data)) {
		hashmap->erase(tail->prev->key);
		current_size -= tail->prev->data.size();
		detach(tail->prev);
	}
	node->key = key;
	node->data = data;
	(*hashmap)[key] = node;
	attach(node);
	current_size += data.size();
}





