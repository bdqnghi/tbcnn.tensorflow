#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct data{
    int val;
    data* next;
    data(int value): val(value),next(NULL){}
};

data* add(int value,data *now){
    data *tmp = new data(value);
    if(now!=NULL){
        now->next = tmp;
        now = tmp;
    }
    return tmp;
}

void print(data *begin,data *end){
    for(data *ptr=begin->next;ptr!=end;ptr=ptr->next)
        cout << ptr->val << " ";
    cout << endl;
}

data* search(int value,data *begin,data *end){
    for(data *ptr=begin->next;ptr!=end;ptr=ptr->next)
        if(ptr->val==value)
            return ptr;
    return end;
}

void remove(int value,data* begin,data*end){
    data* tmp = search(value,begin,end);
    if(tmp==end){
        cout << "Can't find " << value << " in list" << endl;
    }else{
        data* prev = begin;
        while(prev->next!=tmp){
            prev = prev->next;
        }
        prev->next = tmp->next;
        delete tmp;
    }
}

void clear(data* begin,data* end){
    data*tmp = new data(-1);
    for(data *ptr=begin->next;ptr!=end;ptr=ptr->next){
        tmp = ptr->next;
        begin->next = tmp;
        delete ptr;
    }
    delete tmp ; 
    delete begin ;
    //delete end;
}


int main(){
    data* head = new data(-1), *cur = NULL , *tail = new data(-1);
    srand(time(0)) ;
    int v;
	for(int i=0 ; i<10; i++){
        v = rand() % 100;
        cout << v << " ";
        cur = add(v,cur);
        if(i==0)
            head->next = cur;
        if(i==9)
            cur->next = tail;
    }
    //cout << endl << &head << " " << &cur << " " << &tail << endl;
    cout << endl; print(head,tail);
    cout << "Enter a number to search and remove in list: ";
    cin >> v;
    remove(v,head,tail);
    print(head,tail);
    clear(head,tail);
    print(head,tail);
    return 0;
}