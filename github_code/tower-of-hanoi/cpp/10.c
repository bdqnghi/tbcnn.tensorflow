/*
 * towerofhanoi.h
 *
 *  Created on: Jan 15, 2014
 *      Author: siddesh
 */

#include "solver.h"
#ifndef TOWEROFHANOI_H_
#define TOWEROFHANOI_H_

class towerofhanoi: public Puzzle<vector<stack<int> > > {
public:
	towerofhanoi(int noofpegs, int noofdiscs) :
			_no_of_pegs(noofpegs), _no_of_discs(noofdiscs) {
		disk = 0;
	}
	bool checksol(vector<stack<int> > current_config);
	void print_config(vector<stack<int> > key);
	void printsol(vector<stack<int> > key,
			map<vector<stack<int> >, vector<stack<int> > > timemap);
	void firstconfig();
	vector<vector<stack<int> > > next_config(
			vector<stack<int> > current_config);
private:
	int disk;
	int _no_of_pegs;
	int _no_of_discs;
	vector<stack<int> > current_config;
	stack<int> disk_stack;
	stack<int> blank_stack;
	vector<stack<int> > destination_config;

};

void towerofhanoi::firstconfig() {
	for (unsigned int k = _no_of_discs; k > 0; k--) {
		disk_stack.push(k);
	}

	for (unsigned int i = _no_of_pegs; i > 0; i--) {
		if (i == 1) {
			current_config.push_back(disk_stack);
		} else {
			current_config.push_back(blank_stack);
		}
	}

	for (unsigned int i = _no_of_pegs; i > 0; i--) {
		if (i == _no_of_pegs) {
			destination_config.push_back(disk_stack);
		} else {
			destination_config.push_back(blank_stack);
		}
	}
	solve(current_config);
}

bool towerofhanoi::checksol(vector<stack<int> > current_config) {
	return current_config == destination_config;
}

vector<vector<stack<int> > > towerofhanoi::next_config(
		vector<stack<int> > current_config) {
	vector<vector<stack<int> > > vector_configurations;
	vector<stack<int> > configurations_generated;

	for (unsigned int i = 0; i < _no_of_pegs; i++) {
		if ( !current_config[i].empty() ) {
			disk = current_config[i].top();
			for (unsigned int j = 0; j < _no_of_pegs; j++) {
				if (current_config[j].empty()
						|| current_config[j].top() > disk) {
					configurations_generated = current_config;
					configurations_generated[i].pop();
					configurations_generated[j].push(disk);
					vector_configurations.push_back(configurations_generated);
				}
			}
		}
	}
	return vector_configurations;
}

void towerofhanoi::printsol(vector<stack<int> > key,
		map<vector<stack<int> >, vector<stack<int> > > timemap) {

	map<vector<stack<int> >, vector<stack<int> > >::iterator it =
			timemap.begin();

	while (true) {
		it = timemap.find(key);
		if (it == timemap.end()) {
			cout << "ERROR: cannot print!" << endl;
		}
		print_config(key);
		if (key == it->second) {
			break;
		} else {
			key = it->second;
		}
	}
}

void towerofhanoi::print_config(vector<stack<int> > key) {
	int index = 1;
	for (vector<stack<int> >::iterator iter = key.begin(); iter != key.end();
			++iter) {
		stack<int> s = *iter;
		stack<int> solution;
		while (!s.empty()) {
			solution.push(s.top());
			s.pop();
		}
		cout << "Peg#" << index++ << " ";
		while (!solution.empty()) {
			if (solution.top() != 9999)
				cout << solution.top() << " ";
			solution.pop();
		}
		cout << endl;
	}
	cout << endl;
}

#endif /* TOWEROFHANOI_H_ */
