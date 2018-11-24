#include "queue.h"
#include <stack>
#include <cstring>
#include <sstream>

using namespace std;

int main() {

    queue<char> q;                  // capacity 30 elems by default
    stack<char> s;

    // read line of user input
    cout << "Enter a line to check if it's a palindrome.\n";
    string str;
    getline(std::cin, str);

    int i = 0;

    while (i < str.length()) {
        s.push(tolower(str[i]));    // std::tolower() implicit char cast
        q.insert(tolower(str[i]));
        i++;
    }

    while (!s.empty()) {
        if (s.top() != q.remove()) break;
        s.pop();
    }

    if (s.empty())
        std::cout << "Palindrome: true \n";
    else
        std::cout << "Palindrome: false \n";
}
