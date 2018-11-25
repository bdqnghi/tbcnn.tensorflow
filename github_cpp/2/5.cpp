








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
        
        if(head == nullptr && tail==nullptr)
        {
            return -1;
        }
        
        unordered_map<int,doubly_link_node*>::iterator it = my_map.find(key);
        if( it == my_map.end())
        {
            return -1;
        }
        
        else
        {
            doubly_link_node* current_node = it->second;
            int value = current_node->val;
            
            if(current_node == tail)
            {
                
            }
            else
            {
                
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
                
                current_node->next==nullptr;
                current_node->prev = tail;
                tail->next = current_node;
                tail=current_node;
            }
            return value;
        }
        
    }
    
    void put(int key, int value) {
        
        unordered_map<int,doubly_link_node*>::iterator it = my_map.find(key);
        
        if( it == my_map.end())
        {
            
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
            
            if(current_size > capacity)
            {
                
                doubly_link_node* temp_node = head;
                head = head->next;
                head->prev=nullptr;
                
                my_map.erase(temp_node->key);
                
                delete temp_node;
                --current_size;
            }
            
            my_map.insert(pair<int,doubly_link_node*>(key,new_node));
        }
        else
        
        {
            doubly_link_node* current_node = it->second;
            
            current_node->val = value;
            
            it->second->val = value;
            
            if(current_node == tail)
            {
                
            }
            else
            {
                
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
                
                current_node->next==nullptr;
                current_node->prev = tail;
                tail->next = current_node;
                tail=current_node;
            }
        }
        
    }
};