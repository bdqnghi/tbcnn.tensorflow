#include <iostream>
#include <vector>

using namespace std;

struct DataItem {
    int key;
    int data;
    DataItem(int key, int data) : key(key), data(data) {}
};


class hashTable {
    vector<DataItem*> hashArray;
    DataItem* dummyItem;
    int SIZE = 101;

public:
    hashTable() : hashArray(SIZE, nullptr), dummyItem(new DataItem(-1, -1)) {};
    int hashCode(int key) {
        return key % SIZE;
    }

    // Search
    // Use linear probing to get the element ahead if the element is not found
    // at the computed hash code.
    DataItem* search(int key) {
        //get the hash
        int hashIndex = hashCode(key);

        //move in array until an empty
        while(hashArray[hashIndex] != nullptr) {

            if(hashArray[hashIndex]->key == key)
                return hashArray[hashIndex];

            //go to next cell
            ++hashIndex;

            //wrap around the table
            hashIndex %= SIZE;
        }

        return nullptr;
    }


    // Insert
    // Use linear probing for empty location, if an element is found at the
    // computed hash code.
    void insert(int key,int data) {
        auto item = new DataItem(key, data);

        //get the hash
        int hashIndex = hashCode(key);

        //move in array until an empty or deleted cell
        while(hashArray[hashIndex] != nullptr && hashArray[hashIndex]->key != -1) {
            //go to next cell
            ++hashIndex;

            //wrap around the table
            hashIndex %= SIZE;
        }

        hashArray[hashIndex] = item;
    }


    // Delete
    // Use linear probing to get the element ahead if an element is not found
    // at the computed hash code.
    // When found, store a dummy item there to keep the performance of the
    // hash table intact.
    DataItem* remove(DataItem* item) {
        int key = item->key;

        //get the hash
        int hashIndex = hashCode(key);

        //move in array until an empty
        while(hashArray[hashIndex] != nullptr) {

            if(hashArray[hashIndex]->key == key) {
                struct DataItem* temp = hashArray[hashIndex];

                //assign a dummy item at deleted position
                hashArray[hashIndex] = dummyItem;
                return temp;
            }

            //go to next cell
            ++hashIndex;

            //wrap around the table
            hashIndex %= SIZE;
        }

        return nullptr;
    }
};
