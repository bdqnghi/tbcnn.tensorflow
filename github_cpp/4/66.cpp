#include <iostream>
#include <string>
using namespace std;

void Hanoi(int size, string source, string destination, string transit) {
   if (size == 1) {
      cout << "Move from " << source << " to " << destination << endl;
   } else {
      Hanoi(size-1, source, transit, destination);
      cout << "Move from " << source << " to " << destination << endl;
      Hanoi(size-1, transit, destination, source);
   }
}

int main(int argc, char** argv) {
   if (argc != 1) {
      int size = stoi(argv[1]);
      Hanoi(size, "source", "destination", "transit");
   }
}
