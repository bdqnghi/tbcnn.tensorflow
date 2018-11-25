
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void moveDisk(char start, char finish);
void towerOfHanoi(int n, char start, char finish, char temp);


int main() {
  int n;
  cout << "Enter disks : ";
  cin >> n;
  towerOfHanoi(n, 'A', 'B', 'C');
  
  system("pause");
  return 0;
}


void moveDisk(char start, char finish){
  cout<< "Moved from " << start << " to " << finish << endl;
}


void towerOfHanoi(int n, char start, char finish, char temp){
    if(n == 1){
      moveDisk(start, finish);
    } else {
        
        towerOfHanoi(n - 1, start, temp, finish);
        
        moveDisk(start, finish);
        
        towerOfHanoi(n - 1, temp, finish, start);
    }
}
