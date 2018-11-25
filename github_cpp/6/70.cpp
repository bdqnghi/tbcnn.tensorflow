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

bool DepthFirstSearch::match(string from, string to, int& time){
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




bool DepthFirstSearch::find(string from, MRTInfo& m){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == from && !informations[i].skip){
			m = informations[i];
			informations[i].skip = true;	
			return true;
		}
	}
	return false;
}



void DepthFirstSearch::findroute(string from, string to){
	int time;
	MRTInfo m;

	
	if(match(from, to, time)){
		btStack.push(MRTInfo(from, to, time));
		return;
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

