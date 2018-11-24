#include <iostream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

//Kitty cat proof provided by Paul Conrad.
int getInt(string prompt)
{
	int value;
	
	do 
	{
		bool validInput;
		
		cout << prompt;

		cin >> value;
		validInput = cin.good();
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		
		// if validInput is true, return from the function with our value from user
		if (validInput) return value;
		else
		{
			// otherwise, let the user know they did an invalid entry
			cout << "Invalid Entry! " << endl;
			
			// clear the cin object's status (this clears the bad input flag)
			cin.clear();
			cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		}
	} while (true);
}

static vector<int> source, tempo, destin;

void visuals();
void move(vector<int> &, vector<int> &, vector<int> &, long);

int main() {
    long n;
    
    cout << "Tower of Hanoi " << endl;
    n = getInt("Enter the number of disks: ");
    long counter = n;

    for (long i = 0; i < n; i++) {
        source.push_back(counter);
    counter--;
    }

    visuals();
    move(source,destin,tempo,n);

}

void visuals() {
    cout << "Start: ";
    for (vector<int >::const_iterator iter = source.begin(); iter != source.end(); iter++)
        cout << *iter << " ";
    cout << " | ";
    cout << "Final: ";
    for (vector<int >::const_iterator iter = destin.begin(); iter != destin.end(); iter++)
        cout << *iter << " ";
    cout << " | ";
    cout << "Aux: ";
    for (vector<int >::const_iterator iter = tempo.begin(); iter != tempo.end(); iter++)
        cout << *iter << " ";
    cout << endl;
}

void move(vector<int> &source, vector<int> &destin, vector<int> &tempo, long size) {
    if (size > 0) 
	{
        move(source, tempo, destin, size - 1);
        system("pause");
        destin.push_back(source.back());
        system("CLS");
        source.pop_back();
        visuals();
        move(tempo, destin, source, size - 1);
    }
}
