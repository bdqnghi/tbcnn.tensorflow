

#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char** argv) {
	vector<int> towers[3]; 
	int n; 

	cout << "Enter number of rings ";
	cin >> n;

	for (int i = n + 1; i >= 1; i--)
		towers[0].push_back(i);
	towers[1].push_back(n + 1); 
	towers[2].push_back(n + 1);

	
	int candidate = 1; 
	int numOfMoves = 0, to = 0, from = 0;

	to = (n % 2? 1 : 2);
	

	while (towers[1].size() < n + 1) { 

		
		cout << "Move number: " << ++numOfMoves << ". Moving ring " << candidate << " from tower" << (char) (65 + from) << " to tower" << (char) (65 + to) << endl;

		towers[from].pop_back(); 
		towers[to].push_back(candidate); 


		int x, y, z[5] = {2, 0, 1, 2, 0}; 
		for (int i = 1; i <= 3; i++) {
			if (to == z[i]) {
				x = z[i - 1];
				y = z[i + 1];
				break;
			}
		}

		from = (towers[x].back() < towers[y].back()? x : y);

		
		for (int i = 1; i <= 3; i++) { 
			if (n % 2 == 1) { 
				if (from == z[i]) { 
					if (towers[from].back() < towers[z[i + 1]].back()) { 
						to = z[i + 1]; 
					} else {
						to = z[i - 1]; 
					}
				}
			} else { 
				if (from == z[i]) {
					if (towers[from].back() < towers[z[i-1]].back()) {
						to = z[i - 1];
					} else {
						to = z[i + 1];
					}
				}
			}
		}

		
		candidate = towers[from].back();
	}
}
