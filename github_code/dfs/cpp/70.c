#include "DepthFirstSearch.h"


DepthFirstSearch::DepthFirstSearch(void)
{
}


DepthFirstSearch::~DepthFirstSearch(void)
{
}

void DepthFirstSearch::route(){
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

bool DepthFirstSearch::match(string from, string to, int& time){
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
bool DepthFirstSearch::find(string from, MRTInfo& m){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == from && !informations[i].skip){
			m = informations[i];
			informations[i].skip = true;	// prevent reuse
			return true;
		}
	}
	return false;
}

// Depth-first version
// Determine if there is a route between from and to.
void DepthFirstSearch::findroute(string from, string to){
	int time;
	MRTInfo m;

	// See if at destination.
	if(match(from, to, time)){
		btStack.push(MRTInfo(from, to, time));
		return;
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

