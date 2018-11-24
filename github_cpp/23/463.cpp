#include <limits>
#include "skipList.h"

SkipList::SkipList()
    :maxLevel(20)
{   
    int min = numeric_limits<int>::min();
    head = createNode(min, "head", maxLevel);

    int max = numeric_limits<int>::max();
    nil = createNode(max, "nil", maxLevel);

    for(auto i : head->forward) {
        i = nil;
    }
}

SkipNode* SkipList::createNode(int key, string val, int level) {
    return new SkipNode(key, val, level);
}

int SkipList::randomLevel() {
    int level = 1;
    if( rand()/ RAND_MAX < 0.5 ) ++level;
    return level <= maxLevel ? level : maxLevel;
}

SkipNode* SkipList::find(int searchKey) {
    auto it = head;
    for(int i = maxLevel -1 ; i >= 0; i--) {
        while(it->forward[i]->key < searchKey) {
            it = it->forward[i];
        }
    }
    it = it->forward[0];
    if(it->key == searchKey) {
        return it;
    } else {
        return nullptr;
    }
}

void SkipList::insert(int searchKey, string newValue) {
    auto i = find(searchKey);
    if(i != nullptr) {
        i->value = newValue;
        return;
    }

    int newLevel = randomLevel();
    vector<SkipNode*> update(newLevel);

    auto it = head;
    for(int i = newLevel - 1; i >= 0; i--) {
        while(it->forward[i]->key < searchKey) {
            it = it->forward[i];
        }
        update[i] = it;
    }
    auto x = createNode(searchKey, newValue, newLevel);
    for(int i = 0; i < newLevel; ++i) {
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x; 
    }
}

void SkipList::erase(int searchKey) {
    auto i = find(searchKey);
    if(i == nullptr) return;

    int level = i->forward.size();
    vector<SkipNode*> update(level);
    auto it = head;
    
    for(int i = level-1; i >= 0; i--) {
        while(it->forward[i]->key < searchKey) {
            it = it->forward[i];
        }
        update[i] = it;
    }
    for(int j = 0; j < update.size(); j++) {
        update[j]->forward[j] = i->forward[j];
    }
}


