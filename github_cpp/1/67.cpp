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

	
	while(!btStack.empty()){
		m = btStack.top();
		rev.push(m);
		btStack.pop();
	}

	
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
			informations[i].skip = true;	
			time = informations[i].time;
			return true;
		}
	}
	return false;	
}




bool BreadthFirstSearch::find(string from, MRTInfo& m){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == from && !informations[i].skip){
			m = informations[i];
			informations[i].skip = true;	
			return true;
		}
	}
	return false;
}



void BreadthFirstSearch::findroute(string from, string to){
	int time;
	MRTInfo m;

	
	stack<MRTInfo> resetStack;

	
	if(match(from, to, time)){
		btStack.push(MRTInfo(from, to, time));
		return;
	}

	
	
	while(find(from, m)){
		resetStack.push(m);
		if(match(m.to, to, time)){
			resetStack.push(MRTInfo(m));
			btStack.push(MRTInfo(from, m.to, m.time));
			btStack.push(MRTInfo(m.to, to, time));
			return;
		}
	}

	
	
	
	while(!resetStack.empty()){
		resetSkip(resetStack.top());
		resetStack.pop();
	}

	
	if(find(from, m)){
		btStack.push(MRTInfo(from, to, m.time));
		findroute(m.to, to);
	}else if(!btStack.empty()){
		
		m = btStack.top();
		btStack.pop();
		findroute(m.from, m.to);
	}
}


void BreadthFirstSearch::resetSkip(MRTInfo m){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == m.from &&
			informations[i].to == m.to){
			informations[i].skip = false;
		}
	}
}
