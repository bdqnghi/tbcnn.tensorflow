
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

struct Node {
    int data;
    Node* next;
};

void split(Node*& list1, Node*& list2) {
      
    if (list1 == nullptr || list1->next == nullptr)
        return;
        
    Node* l = list1->next;
    list1->next = l->next;
    l->next = list2;
    list2 = l;
    split(list1->next, list2);
}

void merge(Node*& list1, Node* list2) {
    if (list1 == nullptr) {list1 = list2; return;}
    if (list2 == nullptr) {return;}
    if (list1->data <= list2->data) {
        merge(list1->next, list2);
    }
    else {
        merge(list2->next, list1);
        list1 = list2;
    }
}

void mergesort(Node*& list1) {
    if (list1 == nullptr || list1->next == nullptr)
        return;
        
    Node* list2 = nullptr;
    
    split(list1, list2);
    
    mergesort(list1);
    
    mergesort(list2);
    
    merge(list1, list2);
}

int msbits(int x, int minValue, int n) {
    return (int)(floor((x - minValue)/n));
}

void bucketsort(std::vector<int>& arr) {
    int n = arr.size();
    int minValue = *(std::min_element(arr.begin(), arr.end()));   
    
    
    Node* bucketList[n];
    
    for (int i = 0; i < n; i++) {
        bucketList[i] = nullptr;
    }
    
    
    for (int i = 0; i < n; i++) {
        int index = msbits(arr[i],minValue,n); 
        Node* p = new Node;
        p->data = arr[i];
        p->next = bucketList[index];
        bucketList[index] = p;
    }
    
    
    for (int i = 0; i < n; i++) {
        mergesort(bucketList[i]);
    }
    
    
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (Node* p = bucketList[i]; p != nullptr; p = p->next) {
            arr[k++] = p->data;    
        }
    }
}

int main()
{
    std::vector<int> arr = {29,25,3,49,9,37,21,43};
    bucketsort(arr);
    for (auto i: arr) {
        std::cout << i << " ";
    }
    
    return 0;
}
