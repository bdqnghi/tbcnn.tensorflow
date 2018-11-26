
//
// See: https://leetcode.com/submissions/detail/26838843/
//
// Runtime: 70 ms
//

#include <assert.h>

struct LRUItem {
    int         key;
    int         value;
    LRUItem *   prev;
    LRUItem *   next;
};

struct HashItem {
    int         key;
    LRUItem *   value;
};

class HashTable {
private:
    int         mSize;
    int         mMask;
    HashItem *  mTableA;
    HashItem *  mTableB;

    static const unsigned int kMaxQueryStep = 6;

public:
    HashTable(int capacity) {
        mSize = calcSize(capacity);
        mMask = mSize - 1;
        mTableA = new HashItem[mSize];
        mTableB = new HashItem[mSize];
        ::memset(mTableA, -1, sizeof(HashItem) * mSize);
        ::memset(mTableB, -1, sizeof(HashItem) * mSize);
    }

    ~HashTable() {
        /*
        if (mTableA)
            delete[] mTableA;
        if (mTableB)
            delete[] mTableB;
        //*/
    }

protected:
    int getHashA(int key) { return key & mMask; }
    int getHashB(int key) { return (key ^ 4491738) & mMask; }

    int calcSize(int capacity) {
        int size = 16;
        if (capacity > 16) {
            while (size < capacity)
                size <<= 1;
            if ((size - capacity) < size / 4)
                size = size << 1;
        }
        else size = 32;
        return size;
    }

public:
    void add(int key, LRUItem * item) {
        int indexA = getHashA(key);

        HashItem * startPtr = &mTableA[indexA];
        HashItem * endPtr   = startPtr + kMaxQueryStep;
        do {
            if (startPtr->key == -1) {
                startPtr->key   = key;
                startPtr->value = item;
                return;
            }
            if (startPtr->key == key) {
                startPtr->value = item;
                return;
            }
            startPtr++;
        } while (startPtr != endPtr);

        int indexB = getHashB(key);
        int startIndexB = indexB;
        do {
            if (mTableB[indexB].key >= 0 && mTableB[indexB].key != key) {
                indexB = (indexB + 1) & mMask;
                if (indexB == startIndexB)
                    break;
            }
            else {
                mTableB[indexB].key = key;
                mTableB[indexB].value = item;;
                return;
            }
        } while (1);
    }

    LRUItem * find(int key) {
        int indexA = getHashA(key);

        HashItem * startPtr = &mTableA[indexA];
        HashItem * endPtr   = startPtr + kMaxQueryStep;
        do {
            if (startPtr->key == key)
                return startPtr->value;
            if (startPtr->key == -1)
                break;
            startPtr++;
        } while (startPtr != endPtr);

        int indexB = getHashB(key);
        int startIndexB = indexB;
        do {
            if (mTableB[indexB].key != key) {
                if (mTableB[indexB].key != -1) {
                    indexB = (indexB + 1) & mMask;
                    if (indexB == startIndexB)
                        break;
                }
                else {
                    return NULL;
                }
            }
            else return mTableB[indexB].value;
        } while (1);

        return NULL;
    }

    void remove(int key) {
        int indexA = getHashA(key);

        HashItem * startPtr = &mTableA[indexA];
        HashItem * endPtr   = startPtr + kMaxQueryStep;
        do {
            if (startPtr->key == key) {
                startPtr->key = -2;
                return;
            }
            if (startPtr->key == -1)
                break;
            startPtr++;
        } while (startPtr != endPtr);

        int indexB = getHashB(key);
        int startIndexB = indexB;
        do {
            if (mTableB[indexB].key != key) {
                indexB = (indexB + 1) & mMask;
                if (indexB == startIndexB)
                    break;
            }
            else {
                mTableB[indexB].key = -2;
                return;
            }
        } while (1);
    }
};

class LRUCache {
private:
    int         mSize;
    int         mCapacity;
    LRUItem *   mCacheList;
    LRUItem *   mCacheListLast;
    LRUItem *   mHeadItem;
    LRUItem *   mTailItem;
    HashTable   mHashTable;

public:
    LRUCache(int capacity)
        : mSize(0), mCapacity(capacity), mHashTable(capacity) {
        mCacheList = new LRUItem[capacity];
        mCacheListLast = mCacheList;

        mHeadItem = NULL;
        mTailItem = NULL;
    }

    ~LRUCache() {
        /*
        if (mCacheList)
            delete[] mCacheList;
        //*/
    }

    int getSize() { return mSize; }

    void appendItem(int key, int value) {
        LRUItem * newItem = mCacheListLast;
        mCacheListLast++;
        mSize++;

        assert(mSize <= mCapacity);

        newItem->key   = key;
        newItem->value = value;
        newItem->prev  = NULL;
        newItem->next  = mHeadItem;

        // Add a key
        mHashTable.add(key, newItem);

        if (mHeadItem != NULL) {
            // Record the head item (the recent used item).
            mHeadItem->prev = newItem;
            mHeadItem = newItem;
        }
        else {
            // If mHeadItem is null, mTailItem must be null.
            assert(mTailItem == NULL);
            // Record the head and tail item (the recent used item and the last used item).
            mHeadItem = mTailItem = newItem;
        }
    }

    void eliminateItem(int key, int value) {
        LRUItem * oldTailItem = mTailItem;
        if (key != oldTailItem->key) {
            // Remove a key
            mHashTable.remove(oldTailItem->key);
            // Add a key
            mHashTable.add(key, oldTailItem);

            oldTailItem->key = key;
        }
        oldTailItem->value = value;

        LRUItem * newTailItem = oldTailItem->prev;
        if (newTailItem) {
            // Record the new tail item (the last used item).
            newTailItem->next = NULL;
            mTailItem = newTailItem;
        }
        oldTailItem->prev = NULL;

        // To avoid their own point to themselves.
        if (oldTailItem != mHeadItem) {
            oldTailItem->next = mHeadItem;

            // Record the head item (the recent used item).
            mHeadItem->prev = oldTailItem;
            mHeadItem = oldTailItem;
        }
        else {
            oldTailItem->next = NULL;
        }
    }

    void pickupItem(LRUItem * newItem, int value) {
        // Modify the value directly.
        newItem->value = value;

        if (newItem != mHeadItem) {
            if (newItem != mTailItem) {
                // It's not head or tail item.
                newItem->prev->next = newItem->next;
                newItem->next->prev = newItem->prev;
            }
            else {
                // It's the tail item, record the new tail item (the last used item).
                newItem->prev->next = NULL;
                mTailItem = newItem->prev;
            }

            // Insert new head item to the header and
            // record the recent used item (the head item).
            newItem->prev = NULL;
            newItem->next = mHeadItem;

            mHeadItem->prev = newItem;
            mHeadItem = newItem;
        }
    }

    LRUItem * find(int key) {
        return mHashTable.find(key);
    }

    int get(int key) {
        LRUItem * item = find(key);
        if (item) {
            pickupItem(item, item->value);
            return item->value;
        }
        return -1;
    }

    void set(int key, int value) {
        LRUItem * item = find(key);
        if (item == NULL) {
            // It's a new key.
            if (mSize < mCapacity) {
                // The cache list capacity is not full, append a new item to head only.
                appendItem(key, value);
            }
            else {
                // The cache list capacity is full, must be eliminate a item and pickup it to head.
                eliminateItem(key, value);
            }
        }
        else {
            // Pickup the item to head.
            pickupItem(item, value);
        }
    }
};
