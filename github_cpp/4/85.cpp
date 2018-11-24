#include "hash-table.h"

#define BUCKET_SIZE 3

HashTable::HashTable(int capacity) {
  this->capacity = capacity;

  for (int i = 0; i < capacity; ++i) {
    // Create an array of int* elements and store its address in 'bucket'.
    // Note that you can do bucket[i] or *(bucket + i) to access i'th element in this array.
    int** bucket = new int*[BUCKET_SIZE];
    buckets.push_back(bucket);

    for (int j = 0; j < BUCKET_SIZE; ++j) {
      // buckets[i] is pointer to first element in array.
      // Hence, buckets[i][j] is nothing but *(buckets[i] + j).
      buckets[i][j] = NULL;
    }
  }
}

HashTable::~HashTable() {
  for (int i = 0; i < capacity; ++i) {
    // Delete all items in this bucket.
    for (int j = 0; j < BUCKET_SIZE; ++j) {
      if (buckets[i][j]) {
        delete buckets[i][j];
      }
    }
    // Delete this bucket.
    delete[] buckets[i];
  }
}

void HashTable::Insert(int* valuePtr) {
  ++current_size;

  const int bucket_no = *valuePtr % capacity;
  
  // Insert in primary bucket at 'bucket_no' index.
  bool inserted_in_bucket = false;
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (!buckets[bucket_no][j]) {
      buckets[bucket_no][j] = valuePtr;
      return;
    }
  }

  // Insert in overflow bucket.
  overflow_bucket.push_back(valuePtr);
}

bool HashTable::Search(int value) {
  const int bucket_no = value % capacity;

  // Search in primary bucket at 'bucket_no' index.
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (buckets[bucket_no][j] && *buckets[bucket_no][j] == value) {
      return true;
    }
  }

  // Search in overflow bucket.
  for (int i = 0; i < overflow_bucket.size(); ++i) {
    if (*overflow_bucket[i] == value) 
      return true;
  }
  return false;
}