/*
 * File: TowerOfHanoi.cpp
 * This program solves the tower of hanoi for the number of disks of the users choice
 */

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void moveSingleDisk(char start, char finish);
void moveSubTower(int n, char start, char finish, char temp);
int numberOfSteps(int n);

int main() {
    cout << "Welcome to our Tower of Hanoi solver" << endl << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  |    |    |  " << endl;
    }
    cout << "---------------" << endl;
    cout << "--A----B----C--" << endl;
    cout << "Please enter your prefered number of discs" << endl;
    int n;
    cin >> n;
    cout << "It will require " << numberOfSteps(n) << " steps to reach your goal" << endl;
    moveSubTower(n, 'A', 'B', 'C');

    return 0;
}

void moveSingleDisk(char start, char finish) {
    cout << start << " -> " << finish << endl;
}

void moveSubTower(int n, char start, char finish, char temp) {
    if (n == 1) moveSingleDisk(start, finish);
    else {
        moveSubTower(n - 1, start, temp, finish);
        moveSingleDisk(start, finish);
        moveSubTower(n - 1, temp, finish, start);
    }
}

int numberOfSteps(int n) {
    if (n == 1) return 1;
    else return 1 + 2*numberOfSteps(n - 1);
}
