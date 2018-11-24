/*
 * File: Graphics.cpp
 * --------------------------
 * Name: Fraser Campbell
 * Section: [TODO: enter section leader here] 
 * 
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <Stack>
#include <stdlib.h>
using namespace std;

void ReverseQueue(queue<int> &q){
	stack<int> temporary;
	int count = q.size();
	for(int i=0; i<count; i++){
		temporary.push(q.front());
		q.pop();
	}

	for(int i=0; i<count; i++){
		q.push(temporary.top());
		temporary.pop();
	}
}

int main(){
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	ReverseQueue(q);
	int count = q.size();
	for(int i=0; i<count; i++){
		cout << q.front() <<endl;
		q.pop();
	}
	return 0;
}