#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int tableSize = 0; //Table size
float load_ratio = 0.0; //Load Ratio
int totalElements = 0; //Total no. of elements
int new_tableSize = 0; //New size of hashtable
int capacity = 0; //Capacity of current hashtable
struct node *hashTable = NULL;
struct node *new_hashTable = NULL; // a temp hash table, for swapping values of old hssh table to new resized hash table

struct node
{
    int id, key;
    char name[100];
    int marker;
};

void insert(int key, char *name, int id)
{
    int hashIndex = key % tableSize;
    if (tableSize == totalElements)
    {
        cout << "Cannot perform insertion. Hash Table is full." << endl;
        return;
    }
    while (hashTable[hashIndex].marker == 1)
    {
        hashIndex = (hashIndex + 1)%tableSize;
    }
    hashTable[hashIndex].key = key;
    hashTable[hashIndex].id = id;
    strcpy(hashTable[hashIndex].name, name);
    hashTable[hashIndex].marker = 1;
    totalElements++;
    cout << "Inserted " << totalElements << " elements.\n" << endl;
    capacity = tableSize-totalElements;
    cout << "Remaining Capacity = " << capacity << ".\n" << endl;
    load_ratio = (float)capacity/tableSize;

    if(load_ratio == 0.5)
    {
        new_tableSize = tableSize*2;
        new_hashTable = (struct node*)calloc(new_tableSize, sizeof(struct node));
        new_hashTable = hashTable;
        hashTable = (struct node*)calloc(new_tableSize, sizeof(struct node));
        hashTable = new_hashTable;
        tableSize = new_tableSize;
    }
    if(new_tableSize > 0)
    {
        cout << "New Capacity of HashTable = " << new_tableSize << ".\n" << endl;
    }
    return;
}

void display()
{
    int i;
    if (totalElements == 0)
    {
            cout << "Hash Table is empty.\n" << endl;
            return;
    }

    for (i = 0; i < tableSize; i++)
    {
        if (hashTable[i].marker == 1)
        {
            cout << "Key: " << hashTable[i].key << endl;
            cout << "Name: " << hashTable[i].name << endl;
            cout << "ID: " << hashTable[i].id << endl;
            cout << "Index: " << i << endl;
        }
    cout << "\n" << endl;
    }
    cout << "\n" << endl;
    return;
}

  int main()
  {
        int key, id, choice;
        int tmp;
        char name[100];
        cout << "Enter the no of elements:" << endl;
        cin >> tableSize;
        tmp = tableSize;
        hashTable = (struct node *)calloc(tableSize, sizeof(struct node));
        while (1)
        {
                cout << "1. Insertion \n2. Display \n3. Exit \n" << endl;
                cout << "Enter your choice:" << endl;
                cin >> choice;
                switch (choice) {
                        case 1:
                                cout << "Enter the key value:" << endl;
                                cin >> key;
                                getchar();
                                cout << "Name:" << endl;
                                fgets(name, 100, stdin);
                                name[strlen(name) - 1] = '\0';
                                cout << "id:" << endl;
                                cin >> id;
                                insert(key, name, id);
                                break;
                        case 2:
                                display();
                                break;
                        case 3:
                                exit(0);
                        default:
                                cout << "You have entered a wrong choice!\n" << endl;
                                break;
                }
        }
        return 0;
  }
