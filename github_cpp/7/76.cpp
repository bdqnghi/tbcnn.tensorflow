/* 
 * File:   main.cpp
 * Author: Hubert Majewski (23476002)
 *
 * Created on April 24, 2018, 6:57 PM
 */

#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char** argv) {
	vector<int> towers[3]; //Make 3 towers which are vectors
	int n; //Number of rings to be moved one by one

	cout << "Enter number of rings ";
	cin >> n;

	for (int i = n + 1; i >= 1; i--)
		towers[0].push_back(i);
	towers[1].push_back(n + 1); //Create base ring for comparison
	towers[2].push_back(n + 1);

	
	int candidate = 1; //The ring (element) which is to be moved that is first available 
	int numOfMoves = 0, to = 0, from = 0;

	to = (n % 2? 1 : 2);
	

	while (towers[1].size() < n + 1) { //Keep going untill the to tower is filled with all rings (excluding base ring which it should stop at once counted)

		//Print the item that will be moved
		cout << "Move number: " << ++numOfMoves << ". Moving ring " << candidate << " from tower" << (char) (65 + from) << " to tower" << (char) (65 + to) << endl;

		towers[from].pop_back(); //Remove the candidate
		towers[to].push_back(candidate); //Place candidate onto to tower


		int x, y, z[5] = {2, 0, 1, 2, 0}; //Cycle through towers
		for (int i = 1; i <= 3; i++) {
			if (to == z[i]) {
				x = z[i - 1];
				y = z[i + 1];
				break;
			}
		}

		from = (towers[x].back() < towers[y].back()? x : y);

		//Next tower to transport candidate to
		for (int i = 1; i <= 3; i++) { //For every tower
			if (n % 2 == 1) { //If odd
				if (from == z[i]) { //if is tower
					if (towers[from].back() < towers[z[i + 1]].back()) { //if end is smaller than next tower
						to = z[i + 1]; //Go to next tower
					} else {
						to = z[i - 1]; //Go to previous tower
					}
				}
			} else { //if even
				if (from == z[i]) {
					if (towers[from].back() < towers[z[i-1]].back()) {
						to = z[i - 1];
					} else {
						to = z[i + 1];
					}
				}
			}
		}

		//get next candidate after finding the from tower
		candidate = towers[from].back();
	}
}
