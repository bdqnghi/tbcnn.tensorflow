#include <iostream>

using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node(int value) {
        this->value = value;
        next = NULL;
    }
} *root;

void printList() {
    Node *tmp = root;
    cout<<"The list is: ";
    while(tmp) {
        cout<<tmp->value<<" ";
        tmp = tmp->next;
    }
    cout<<endl;
}

void deleteNthFromList(int pos) {
    //considering list as 1 indexed, so pos equals 1 means first element ie. root
    int counter = 1;
    Node *tmp = root;
    Node *prev;
    if(pos == counter) {
        root = root->next;
        delete(tmp);
    } else {
        while(counter != pos) {
            prev = tmp;
            tmp = tmp->next;
            ++counter;
        }
        prev->next = tmp->next;
        tmp->next = NULL;
        delete(tmp);
    }
}

void deleteFromList(int value) {
    //delete from list in O(n), deletes the first occurance of that number
    Node *tmp = root, *prev;
    if(tmp->value == value) {
        root = root->next;
        delete(tmp);
        return;
    }
    prev = tmp;
    tmp = tmp->next;
    while(tmp) {
        if(tmp->value == value) {
            prev->next = tmp->next;
            delete(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    cout<<"Can't find desired value to delete...\n";
}

void deleteAllFromList(int value) {
    //delete from list in O(n), deletes the all occurances of that number
    Node *tmp, *dummy, *prev;
    bool found = false;
    while(root!= NULL && root->value == value) {
        tmp = root;
        root = root->next;
        delete(tmp);
    }
    prev = root;
    tmp = prev->next;
    while(tmp) {
        if(tmp->value == value) {
            prev->next = tmp->next;
            dummy = tmp;
            delete(dummy);
            found = true;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if(!found)
        cout<<"Can't find desired value to delete...\n";
}

int listLength() {
    int len = 0;
    Node* tmp = root;
    while(tmp) {
        tmp = tmp->next;
        ++len;
    }
    return len;
}

void insertAt(int val, int pos) {
    //Lets make 1 indexed list, so pos = 1 means first value ie. root
    int i = 1;
    Node *tmp = root;
    
    if(pos < 1 || pos > listLength()) {
        cout<<"Invalid position..\n";
        return;
    }
    
    if(pos == 1) {
        //insert at root place
        Node *node = new Node(val);
        node->next = root;
        root = node;
        return;
    }
    while(i < pos-1) {
        tmp = tmp->next;
        ++i;
    }
    Node *node = new Node(val);
    node->next = tmp->next;
    tmp->next = node;
}

Node* kReverse(Node* root, int k) {
    Node *prev = NULL;
    Node *curr = root;
    Node *next;
    int counter = 0;
    
    while(curr && counter < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        ++counter;
    }
    
    if(next != NULL) {
        root->next = kReverse(next, k);
    }
    
    return prev;
}

Node* reverseInPlace() {
    Node *prev = NULL;
    Node *curr = root;
    Node *next;
    
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}

Node* reverseSublist(int start, int end) {
    Node *prev = NULL;
    Node *curr = root;
    Node *next, *store;
    int counter = 1;
    
    while(counter < start) {
        store = curr;
        curr = curr->next;
        ++counter;
    }
    
    while(curr && counter <= end) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        ++counter;
    }
    
    if(store) {
        store->next->next = next;
        store->next = prev;
    } else {
        return prev;
    }
    
    return root;
}

bool findLoop() {
    if(root == NULL) {
        return root;
    }
    Node *slow = root;
    Node *fast = root;
    Node *faster = root;

    while(slow && (fast = faster->next) && (faster = fast->next)) {
        if(slow == fast || slow == faster) {
            return true;
        }
        slow = slow->next;
    }
    return false;
}

int main() {
    int i, n, input;
    Node *prev;
    cout<<"Input n: ";
    cin>>n;
    for(i = 0; i < n; ++i) {
        cin>>input;
        Node *node = new Node(input);
        if(root == NULL) {
            root = node;
        }
        else {
            prev->next = node;
        }
        prev = node;
    }

    printList();
    
    //cout<<"Delete value: ";
    //cin>>input;
    //deleteFromList(input);
    //deleteAllFromList(input);
    //printList();
    
    //cout<<"Insert value: ";
    //cin>>input;
    //cout<<"Position (1 indexed): ";
    //cin>>n;
    //insertAt(input, n);
    //printList();
    
    // cout<<"After reverse, ";
    // root = reverseInPlace();
    // printList();

    // cout<<"Loop exists: " << findLoop() << endl;
    
    // cout<<"Enter position to delete (1 indexed): ";
    // cin>>input;
    // deleteNthFromList(input);
    // printList();
    
    // cout<<"Enter k value for k-Reverse: ";
    // cin>>input;
    // cout<<"After "<<input<<"-reverse, ";
    // root = kReverse(root, input);
    // printList();
    
    int start, end;
    
    cout<<"Enter start and end values for sublist to be reversed: ";
    cin>>start>>end;
    cout<<"After reversing Sublist: ";
    root = reverseSublist(start, end);
    printList();

    return 0;
}
