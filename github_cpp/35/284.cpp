//#include <iostream>
//using namespace std;
//
//struct Node {
//    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
//    int data;
//    Node* next;
//};
//
///*
//  add, remove
//  size/length
//  clear
//  duplicate
// */
//
//void listDisplay(Node* headPtr) {
//    //void listDisplay(const Node* headPtr) {
//    Node* p = headPtr;
//    //const Node* p = headPtr;
//    //while (p->next != nullptr) {
//    while (p != nullptr) {
//    //while (p) {
//        cout << p->data << ' ';
//        p = p->next;
//    }
//    cout << endl;
//}
//
//int listLength(Node* headPtr) {
//    Node* p = headPtr;
//    int counter = 0;
//    while (p != nullptr) {
//        ++counter
//        p = p->next;
//    }
//    return counter;
//}
//
//void listDisplay(Node* headPtr) {
//    while (headPtr != nullptr) {
//        cout << headPtr->data << ' ';
//        headPtr = headPtr->next;
//    }
//    cout << endl;
//}
//
//void listAddHead(Node*& headPtr, int data) {
//    // 1. make a node for the data
//    Node* p = new Node(data);
//    // 2. have the node "point to" the old head
//    p->next = headPtr;
//    // 3. have the headPtr point to the new node
//    headPtr  = p;
//}
//
//int main() {
//    Node* myList = nullptr;
//
//    listAddHead(myList, 17);
//
//    //myList = new Node(17);
//    myList->next = new Node(28);
//
//    cout << myList->data << ' ' << myList->next->data << endl;
//    listDisplay(myList);
//
//    //myList->next = new Node(64);
//
//    listAddHead(myList, 6);
//}
//
