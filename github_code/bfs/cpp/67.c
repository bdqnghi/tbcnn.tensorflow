#include "BreadthFirstSearch.h"


BreadthFirstSearch::BreadthFirstSearch(void)
{
}


BreadthFirstSearch::~BreadthFirstSearch(void)
{
}

void BreadthFirstSearch::route(){
	stack<MRTInfo> rev;
	int time = 0;
	MRTInfo m;

	// Reverse the stack ti display route.
	while(!btStack.empty()){
		m = btStack.top();
		rev.push(m);
		btStack.pop();
	}

	// Display the route.
	while(!rev.empty()){
			m = rev.top();
			rev.pop();
			cout << m.from << " to ";
			time += m.time;
	}

	cout << m.to << endl;
	cout << "Time is " << time << endl;
}

bool BreadthFirstSearch::match(string from, string to, int& time){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == from &&
			informations[i].to == to && !informations[i].skip){
			informations[i].skip = true;	// prevent reuse
			time = informations[i].time;
			return true;
		}
	}
	return false;	// not found
}

// Given from, find any connection.
// Return true if a connection is found,
// and false otherwise.
bool BreadthFirstSearch::find(string from, MRTInfo& m){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == from && !informations[i].skip){
			m = informations[i];
			informations[i].skip = true;	// prevent reuse
			return true;
		}
	}
	return false;
}

// Breadth-first version
// Determine if there is a route between from and to.
void BreadthFirstSearch::findroute(string from, string to){
	int time;
	MRTInfo m;

	// This stack is needed by the breadth-first search
	stack<MRTInfo> resetStack;

	// See if at destination.
	if(match(from, to, time)){
		btStack.push(MRTInfo(from, to, time));
		return;
	}

	// This part checks all connecting informations
	// from a specified node.
	while(find(from, m)){
		resetStack.push(m);
		if(match(m.to, to, time)){
			resetStack.push(MRTInfo(m));
			btStack.push(MRTInfo(from, m.to, m.time));
			btStack.push(MRTInfo(m.to, to, time));
			return;
		}
	}

	// The following code resets the skip fields set by
	// preceding while loop. This is also part of the 
	// breadth-first modification.
	while(!resetStack.empty()){
		resetSkip(resetStack.top());
		resetStack.pop();
	}

	// Try another connection.
	if(find(from, m)){
		btStack.push(MRTInfo(from, to, m.time));
		findroute(m.to, to);
	}else if(!btStack.empty()){
		// Backtrace and try another connection.
		m = btStack.top();
		btStack.pop();
		findroute(m.from, m.to);
	}
}

// Reset the skip fields in information.
void BreadthFirstSearch::resetSkip(MRTInfo m){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == m.from &&
			informations[i].to == m.to){
			informations[i].skip = false;
		}
	}
}
