#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Tower {
    int id;
    stack<int> t;
    
    public:
        Tower(int id) {
            this->id = id+1;
        }
        
        void add(int val) {
            t.push(val);
        }
        
        void display() {
            cout<<"Tower "<<id<<" -> ";
            for(stack<int> dump = t; !dump.empty(); dump.pop())
                cout<<dump.top()<<" ";
            cout<<"\n";
        }
        
        void moveTopTo(Tower* dest) {
            if(!t.empty()) {
                dest->add(t.top());
                t.pop();
            }
        }
        
        void moveDisks(int n, Tower* dest, Tower* buffer) {
            if(n > 0) {
                moveDisks(n-1, buffer, dest);
                moveTopTo(dest);
                buffer->moveDisks(n-1, dest, this);
                display();
                buffer->display();
                dest->display();
                cout<<"\n";
            }
        }
};

int main() {
    int no_of_towers = 3, values = 5; 
    vector<Tower> t;
    
    for(int i=0; i<no_of_towers; i++) {
        t.push_back(Tower(i));
    }
    
    for(int i=values; i>0; i--) {
        t[0].add(i);
    }
    
    for(int i=0; i<no_of_towers; i++) {
        t[i].display();
    }
    cout<<"\n";
    
    t[0].moveDisks(values, &t[2], &t[1]);
    
    for(int i=0; i<no_of_towers; i++) {
        t[i].display();
    }
    
    return 0;
}