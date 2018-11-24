#include "SkipList.hpp"

/***********************************************************/
/********************** PROVIDED FUNCTIONS *****************/
/***********************************************************/

void SkipList::init(int maxHeight) {
    m_maxHeight = maxHeight;
    m_head = new SkipListNode("", m_maxHeight);
}

SkipList::~SkipList() {
    while (m_head != NULL) {
        SkipListNode* head = m_head;
        m_head = m_head->nextAtLevel(0);
        delete head;
    }
}

int SkipList::add(const Key& key, bool verbose) {
    if (find(key, false)) {
        if (verbose) {
            cout << "Node " << key << " is already in the list." << endl;
        }
        return 0;
    }

    SkipListNode* newNode = new SkipListNode(key, randHeight());
    if (verbose) {
      cout << "Add new node "<< *newNode << " with height "
             << newNode->height() << endl;
    }
    int ret = add(m_head, newNode, m_maxHeight - 1);
    if (ret == 0) {
        return ret;
    }
    return 1;
}

int SkipList::find(const Key& key, bool verbose) {
    //cout<<"In FIND"<<endl;
    SkipListNode* ret = find(m_head, key, m_maxHeight - 1) ;
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<< key << " is not in the list" << endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<< "Node " << key << " is in the list" << endl;
        }
        return 1;
    }

}
int SkipList::del(const Key& key, bool verbose) {
    if (key.length() == 0){
      return 1;
    }
    SkipListNode* toBeDeleted = del(m_head, key, m_maxHeight - 1);

    if (toBeDeleted == NULL) {
        if (verbose) {
            cout<< "Node " << key << " is not in the list" << endl;
        }
    } else {
        delete toBeDeleted;
        if (verbose) {
            cout << "Node " << key << " is deleted from the list" << endl;
        }
    }
    return 1;
}

void SkipList::dump(char sep) {
    int length = -1;
    cout << "Current List: ";
    for (SkipListNode* iter = m_head; iter != NULL; iter = iter->nextAtLevel(0)) {
        length++;
        cout << string(*iter) << " ";
        cout << "(" << iter->height() << ":";
        for (unsigned i = 0; i < iter->height(); i++) {
            if (iter->nextAtLevel(i)) {
                cout << " "<< i << ":" << *(iter->nextAtLevel(i));
                cout.flush();
            }
        }
        cout << ")" << sep;
    }
    cout << length << " nodes in total." << endl;
}


/***********************************************************/
/***************  FUNCTIONS TO BE COMPLETED  ****************/
/***********************************************************/

/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

unsigned int SkipList::randHeight() {
    ////////////// Write your code below  ////////////////////////

    int t = rand();
    int j = 2;
    int i; 
    for (i=1; i < RAND_MAX; i++){
      if (t > RAND_MAX/j) break;
      j += j;
    }
    return i; 
}


int SkipList::add(SkipListNode* target, SkipListNode* newNode,
                  unsigned level) {

    if (target->nextAtLevel(level) != NULL &&
            *target->nextAtLevel(level) < *newNode) {
        countAdd++;
        //cout<<"count add : "<<countAdd<<endl;
        return SkipList::add(target->nextAtLevel(level), newNode, level);  
        }

    if (target->nextAtLevel(level) == NULL) // if we get to the end of the level without finding the right place
    {
        level--;
        if ( (level==0) ) // && (level < newNode->height() ))  // if we get to the end of the list add it as the last
        {
            newNode->setNextAtLevel(level, target->nextAtLevel(level)); // fix newnode's pointer 
            target->setNextAtLevel(level, newNode); // adding new node as next 
            return 1;
        }
        //level--;
        if (level>0) return SkipList::add(target, newNode, level);
        //SkipList::dump(' ');
        return 1; // new node added and links for all levels were adjusted 
    }

    if (target->nextAtLevel(level) != NULL && *target->nextAtLevel(level) > *newNode) 
    {
        if (level<newNode->height()) 
        {
            newNode->setNextAtLevel(level, target->nextAtLevel(level));
            target->setNextAtLevel(level, newNode);
        }
        level--;
        if (level>0) return SkipList::add(target, newNode, level);
        SkipList::dump(' ');
        return 1; // new node added and links for all levels were adjusted 
    }
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::find(SkipListNode* target, const Key& key,
                             unsigned level) {
    // countFind is a protected field of DataStructure
    //SkipList::dump(' ');
    //if (target==NULL) cout<<"NULL"<<endl;

    // SD: Should this be if(*target == key) return target; ?
    //if (*target->nextAtLevel(level)==key) 
    if(*target == key)  
        return target; 
    
    //cout<<" IN FIND !!!!!!!!!"<<endl;
    if (target->nextAtLevel(level) != NULL &&
            *target->nextAtLevel(level) < key) {
        countFind++;
        //cout<<" going forward"<<endl;
        return SkipList::find(target->nextAtLevel(level), key, level);
    }
    
    if ((target->nextAtLevel(level) !=NULL) && *target->nextAtLevel(level) > key) {
        if (level>0)
        {
            level--;
            countFind++;
            //cout<< " going down one level"<<endl;
            return SkipList::find(target, key, level);
        }
        return NULL; // if level is 0
    } 
    
    if (target->nextAtLevel(level) == NULL)
    {
        if (level>0) 
        {
            level--; 
            countFind++;
            return SkipList::find(target, key, level);
        }
        return NULL; //if level is 0
    }



}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::del(SkipListNode* target, const Key& key,
                            unsigned level) {
    //printList(m_head, 0);
    //SkipList::dump(' ');
    if (target->nextAtLevel(level) != NULL &&
            *target->nextAtLevel(level) < key) {
        countDelete++;
        return SkipList::del(target->nextAtLevel(level), key, level);
    }
    ////////////// Write your code below  ////////////////////////
    if ((target->nextAtLevel(level) !=NULL) && *target->nextAtLevel(level) > key) {
        if (level>0)
        {
            level--;
            countFind++;
            //cout<< " going down one level"<<endl;
            return SkipList::find(target, key, level);
        }
        return NULL; // if level is 0
    } 
    
    if (target->nextAtLevel(level) == NULL)
    {
        if (level>0) 
        {
            level--; 
            countFind++;
            return SkipList::find(target, key, level);
        }
        return NULL; 
    }

    if (*target->nextAtLevel(level)==key) 
    {
        SkipListNode* deletedNode = target->nextAtLevel(level); 
        target->setNextAtLevel(level, target->nextAtLevel(level)->nextAtLevel(level));
        return deletedNode;
    }   

}

