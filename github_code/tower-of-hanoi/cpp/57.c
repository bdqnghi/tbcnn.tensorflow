#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

class Tower
{
    stack<int> disks;
    string name;

public:
    Tower() {}
    Tower(string);
    void push(int);
    int pop();
    int top();
    string get_name();
    friend void tower_of_hanoi(Tower &, Tower &, Tower &, int);
};

Tower :: Tower(string str)
{
    name = str;
}

string Tower :: get_name()
{
    return name;
}

void Tower :: push(int element)
{
    disks.push(element);
}

int Tower :: top()
{
    return disks.top();
}

int Tower :: pop()
{
    int element = disks.top();
    disks.pop();
    return element;
}

void tower_of_hanoi(Tower &source, Tower &destination, Tower &buffer, int count)
{
    if(count > 0) {
        tower_of_hanoi(source, buffer, destination, count - 1);
        cout << source.get_name() << " -> " << destination.get_name() << endl;
        destination.push(source.pop());
        tower_of_hanoi(buffer, destination, source, count - 1);
    }
}

int main(int argc, char *argv[])
{
    Tower A(string("A"));
    Tower B(string("B"));
    Tower C(string("C"));
    int size = 3;

    for (int i = size; i > 0; i--)
        A.push(i);

    tower_of_hanoi(A, B, C, size);

    for (int i = size; i > 0; i--)
        cout << B.pop() << endl;
    return 0;
}

// typedef stack<int> Stack;

// void tower_of_hanoi(Stack &A, Stack &B, Stack &C, int count)
// {
    // if (count <= 0)
        // return;
    // tower_of_hanoi(A, C, B, count - 1);
    // int element = A.top();
    // A.pop();
    // B.push(element);
    // tower_of_hanoi(C, B, A, count - 1);
// }


// int main(int argc, char *argv[])
// {
    // Stack A;
    // Stack B;
    // Stack C;
    // int size = 3;

    // for (int i = size; i > 0; i--)
        // A.push(i);

    // tower_of_hanoi(A, B, C, size);

    // for (int i = size; i > 0; i--) {
        // cout << B.top() << endl;
        // B.pop();
    // }
    // return 0;
// }
