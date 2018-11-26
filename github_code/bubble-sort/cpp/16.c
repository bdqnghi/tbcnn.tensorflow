#include <iostream>
#include <string>
using namespace std;

const int NUM_NAMES = 20;
void printNames(string[]);
void sortNames(string[]);

int main()
{
	string names[NUM_NAMES] = {"Collins, Bill", "Smith, Bart", "Allen, Jim",
                               "Griffin, Jim", "Stamey, Marty", "Rose, Geri",
                               "Taylor, Terri", "Johnson, Jill", "Allison, Jeff",
                               "Looney, Joe", "Wolfe, Bill", "James, Jean",
                               "Weaver, Jim", "Pore, Bob", "Rutherford, Greg",
                               "Javens, Renee", "Harrison, Rose", "Setzer, Cathy",
                               "Pike, Gordon", "Holland, Beth" };

	//Shows the unsorted list on-screen
	cout << "\nUNSORTED:" << endl;
	printNames(names);

	//Sorts the names in alphabetical order
	sortNames(names);	

	//Shows the newly sorted list on-screen
	cout << "\nSORTED:" << endl;
	printNames(names);
	return 0;
}

//Prints the names on-screen
void printNames(string names[]){
	for(int i = 0; i < NUM_NAMES; i++){
		cout << names[i] << endl;
	}
	cout << endl;
}

//Sorts the names in alphabetical order
void sortNames(string names[]){
	bool swap = false;
	do {
		string temp;
		swap = false;
		for(int numID = 0; numID < NUM_NAMES-1; numID++){
			if (names[numID] > names[numID+1]){
				temp = names[numID];
				names[numID] = names[numID+1];
				names[numID+1] = temp;
				swap = true;
			}
		}
	} while (swap);
}
