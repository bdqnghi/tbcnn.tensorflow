// to do cache lookup in o(1), we will need to use a hash table (unordered_map)
// to implement LRU policy, we can use a queue. Idea is to keep the least recently used
// entry at top of the queue. Whenever we get an (key,value), if the key is already present in queue,
// we remove that node and insert is on back of the queue as its now the most recent entry.
// if the queue is full and we get a new key, we remove the top element from queue and insert new entry at the
// back of the queue.
// since there is a need to remove and add entries, to be able to do that in o(1) time, we will need a doubly
// linked list or dequeue. To do a lookup in o(1), we will use hash table which will store key and the node address of the DLL.
// doubly linked list data structure
class LRUCache{
    struct doubly_link_node
    {
        int key;
        int val;
        doubly_link_node *prev;
        doubly_link_node *next;
        doubly_link_node(int key, int value):key(key),val(value),prev(nullptr),next(nullptr){};
    };
    int current_size;
    int capacity;
    unordered_map<int,doubly_link_node*> my_map;
    doubly_link_node *head, *tail;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        current_size = 0;
        head=nullptr;
        tail=nullptr;
    }
    
    int get(int key) {
        // no key exists
        if(head == nullptr && tail==nullptr)
        {
            return -1;
        }
        //current key doesnt exists
        unordered_map<int,doubly_link_node*>::iterator it = my_map.find(key);
        if( it == my_map.end())
        {
            return -1;
        }
        // key exists
        else
        {
            doubly_link_node* current_node = it->second;
            int value = current_node->val;
            // if already in tail, no need to move it to tail. just return key
            if(current_node == tail)
            {
                //return key;
            }
            else
            {
                //remove the node
                if(current_node == head)
                {
                     current_node->next->prev = nullptr;
                     head = current_node->next;
                }
                else
                {
                    current_node->next->prev = current_node->prev;
                    current_node->prev->next = current_node->next;
                    
                }
                // add it to tail
                current_node->next==nullptr;
                current_node->prev = tail;
                tail->next = current_node;
                tail=current_node;
            }
            return value;
        }
        
    }
    
    void put(int key, int value) {
        //check if key exists
        unordered_map<int,doubly_link_node*>::iterator it = my_map.find(key);
        // if it doesnt, add it to tail and remove a node from head if capacity is full
        if( it == my_map.end())
        {
            // add the key to tail
            doubly_link_node* new_node = new doubly_link_node(key,value);
            if((tail == nullptr) && (head == nullptr))
            {
                tail = new_node;
                head = tail;
            }
            else
            {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }
            ++current_size;
            //if size is more than capacity
            if(current_size > capacity)
            {
                // remove a node from head
                doubly_link_node* temp_node = head;
                head = head->next;
                head->prev=nullptr;
                // also remove node from hashtable
                my_map.erase(temp_node->key);
                // free the node
                delete temp_node;
                --current_size;
            }
            // insert the new node in hash table
            my_map.insert(pair<int,doubly_link_node*>(key,new_node));
        }
        else
        // else remove it and move to tail
        {
            doubly_link_node* current_node = it->second;
            // update value
            current_node->val = value;
            // update hash table value
            it->second->val = value;
            // if already in tail, no need to move it to tail. 
            if(current_node == tail)
            {
                
            }
            else
            {
                //remove the node
                if(current_node == head)
                {
                     current_node->next->prev = nullptr;
                     head = current_node->next;
                }
                else
                {
                    current_node->next->prev = current_node->prev;
                    current_node->prev->next = current_node->next;
                    
                }
                // add it to tail
                current_node->next==nullptr;
                current_node->prev = tail;
                tail->next = current_node;
                tail=current_node;
            }
        }
        
    }
};