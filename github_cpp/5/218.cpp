#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>

template<class ValueType>
class Iterator;

template<class ValueType>
struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    const ValueType value;
    size_t size = 1;

    Node(ValueType val) : value(val)
    {}

    Node<ValueType>* minimum() {
        Node<ValueType>* ptr = this;
        while (ptr->left != nullptr) {
            ptr = ptr->left;
        }
        return ptr;
    }

    Node<ValueType>* maximum() {
        Node<ValueType>* ptr = this;
        while (ptr->right != nullptr) {
            ptr = ptr->right;
        }
        return ptr;
    }

    Node<ValueType>* next() {
        if (this->right != nullptr) return right->minimum();
        Node<ValueType>* ptr = this->parent;
        Node<ValueType>* cur = this;
        while (ptr != nullptr && cur == ptr->right) {
            cur = ptr;
            ptr = ptr->parent;
        }
        return ptr;
    }

    Node<ValueType>* prev() {
        if (this->left != nullptr) return left->maximum();
        Node<ValueType>* ptr = this->parent;
        Node<ValueType>* cur = this;
        while (ptr != nullptr && cur == ptr->left) {
            cur = ptr;
            ptr = ptr->parent;
        }
        return ptr;
    }
};

template<class ValueType>
class Set {
 public:
    using iterator = Iterator<ValueType>;
    ~Set() {
        clear();
    }

    Set() {}

    template<typename InputIterator>
    Set(InputIterator ItBegin, InputIterator ItEnd) : Set() {
        while (ItBegin != ItEnd) {
            insert(*ItBegin);
            ++ItBegin;
        }
    }

    Set(std::initializer_list<ValueType> List) : Set(List.begin(), List.end())
    {}

    Set(const Set& set) : Set(set.begin(), set.end())
    {}

    Set(Set&& set)
    : set_size(std::move(set.set_size))
    , root(std::move(set.root))
    , min_value(std::move(set.min_value))
    , max_value(std::move(set.max_value))
    {}

    Set& operator = (const Set& set) {
        if (this == &set) return *this;
        *this = Set(set);
        return *this;
    }

    Set& operator = (Set&& set) {
        swap(set);
        return *this;
    }

    void swap(Set& set) {
        std::swap(this->set_size, set.set_size);
        std::swap(this->root, set.root);
        std::swap(this->min_value, set.min_value);
        std::swap(this->max_value, set.max_value);
    }

    size_t size() const {
        return set_size;
    }

    bool empty() const {
        return (set_size == 0);
    }

    void insert(const ValueType& added_element) {
        if (root == nullptr) {
            root = new Node<ValueType>(added_element);
            min_value = max_value = root;
            ++set_size;
            return;
        }
        Node<ValueType>* ptr = root;
        while (ptr != nullptr) {
            if (added_element < ptr->value) {
                if (ptr->left == nullptr) {
                    ptr->left = new Node<ValueType>(added_element);
                    ptr->left->parent = ptr;
                    ptr = ptr->left;
                    break;
                }
                ptr = ptr->left;
            } else if (ptr->value < added_element) {
                if (ptr->right == nullptr) {
                    ptr->right = new Node<ValueType>(added_element);
                    ptr->right->parent = ptr;
                    ptr = ptr->right;
                    break;
                }
                ptr = ptr->right;
            } else {
                return;
            }
        }
        rebalance(ptr);
        min_value = root->minimum();
        max_value = root->maximum();
        ++set_size;
    }

    iterator begin() const {
        return iterator(min_value, this);
    }

    iterator end() const {
        return iterator(nullptr, this);
    }

    iterator find(const ValueType& searched_element) const {
        Node<ValueType>* ptr = root;
        while (ptr != nullptr) {
            if (ptr->value < searched_element) {
                ptr = ptr->right;
            } else if (searched_element < ptr->value) {
                ptr = ptr->left;
            } else {
                return iterator(ptr, this);
            }
        }
        return end();
    }

    iterator lower_bound(const ValueType& lower_element) const {
        Node<ValueType>* result = nullptr;
        Node<ValueType>* ptr = root;
        while (ptr != nullptr) {
            if (lower_element < ptr->value) {
                result = ptr;
                ptr = ptr->left;
            } else if (ptr->value < lower_element) {
                ptr = ptr->right;
            } else {
                result = ptr;
                break;
            }
        }
        return iterator(result, this);
    }

    void erase(const ValueType& value) {
        int sz = set_size;

        if (find(value) != end()) --sz;

        root = remove(root, value);
        if (root == nullptr) {
            min_value = max_value = nullptr;
        } else {
            min_value = root->minimum();
            max_value = root->maximum();
        }
    }

    void clear() {
        while (begin() != end()) {
            erase(min_value->value);
        }
    }

 private:
    friend class Iterator<ValueType>;
    size_t set_size = 0;
    Node<ValueType>* root = nullptr;
    Node<ValueType>* min_value = nullptr;
    Node<ValueType>* max_value = nullptr;

    Node<ValueType>* get_root() {
        return root;
    }

    Node<ValueType>* balance(Node<ValueType>* ptr) {
        update_size(ptr);
        int inv = get_invariant(ptr);
        if (inv == 2) {
            if (get_invariant(ptr->right) < 0) {
                ptr->right = right_rotate(ptr->right);
            }
            return left_rotate(ptr);
        }
        if (inv == -2) {
            if (get_invariant(ptr->left) > 0) {
                ptr->left = left_rotate(ptr->left);
            }
            return right_rotate(ptr);
        }
        return ptr;
    }

    void rebalance(Node<ValueType>* ptr) {
        while (ptr != nullptr) {
            ptr = balance(ptr);
            ptr = ptr->parent;
        }
    }

    size_t get_size(Node<ValueType>* ptr) {
        if (ptr == nullptr) return 0;
        return ptr->size;
    }

    void update_size(Node<ValueType>* ptr) {
        ptr->size = std::max(get_size(ptr->left), get_size(ptr->right)) + 1;
    }

    int get_invariant(Node<ValueType>* ptr) {
        return static_cast<int>(get_size(ptr->right)) - static_cast<int>(get_size(ptr->left));
    }

    Node<ValueType>* removemin(Node<ValueType>* ptr) {
        if (ptr->left == nullptr) {
            if (ptr->right != nullptr) {
                ptr->right->parent = ptr->parent;
            }
            return ptr->right;
        }
        ptr->left = removemin(ptr->left);
        if (ptr->left != nullptr) ptr->left->parent = ptr;
        ptr = balance(ptr);
        return ptr;
    }

    Node<ValueType>* remove(Node<ValueType>* ptr, const ValueType& k) {
        if (ptr == nullptr) return nullptr;
        if (k < ptr->value) {
            ptr->left = remove(ptr->left, k);
            if (ptr->left != nullptr) ptr->left->parent = ptr;
            ptr = balance(ptr);
        } else if (ptr->value < k) {
            ptr->right = remove(ptr->right, k);
            if (ptr->right != nullptr) ptr->right->parent = ptr;
            ptr = balance(ptr);
        } else {
            --set_size;
            Node<ValueType>* left_son = ptr->left;
            Node<ValueType>* right_son = ptr->right;
            Node<ValueType>* parent = ptr->parent;

            if (right_son == nullptr) {
                if (parent == nullptr) {
                    root = left_son;
                } else {
                    if (parent->left == ptr) {
                        parent->left = left_son;
                    } else {
                        parent->right = left_son;
                    }
                }
                if (left_son != nullptr) left_son->parent = parent;
                delete ptr;
                return left_son;
            }
            Node<ValueType>* min_val = right_son->minimum();

            min_val->right = removemin(right_son);
            min_val->left = left_son;
            min_val->parent = parent;

            if (min_val->right != nullptr) {
                min_val->right->parent = min_val;
            }
            if (min_val->left != nullptr) {
                min_val->left->parent = min_val;
            }

            if (parent != nullptr) {
                if (parent->left == ptr) {
                    parent->left = min_val;
                } else {
                    parent->right = min_val;
                }
            } else {
                root = min_val;
            }

            delete ptr;
            min_val = balance(min_val);

            return min_val;
        }
        return ptr;
    }

    Node<ValueType>* right_rotate(Node<ValueType>* ptr) {
        Node<ValueType>* left_son = ptr->left;
        if (left_son->right != nullptr) left_son->right->parent = ptr;
        ptr->left = left_son->right;
        left_son->right = ptr;
        left_son->parent = ptr->parent;
        ptr->parent = left_son;
        if (left_son->parent != nullptr) {
            if (left_son->parent->left == ptr) {
                left_son->parent->left = left_son;
            } else {
                left_son->parent->right = left_son;
            }
        } else {
            root = left_son;
        }
        update_size(ptr);
        update_size(left_son);
        return left_son;
    }

    Node<ValueType>* left_rotate(Node<ValueType>* ptr) {
        Node<ValueType>* right_son = ptr->right;
        if (right_son->left != nullptr) right_son->left->parent = ptr;
        ptr->right = right_son->left;
        right_son->left = ptr;
        right_son->parent = ptr->parent;
        ptr->parent = right_son;
        if (right_son->parent != nullptr) {
            if (right_son->parent->left == ptr) {
                right_son->parent->left = right_son;
            } else {
                right_son->parent->right = right_son;
            }
        } else {
            root = right_son;
        }
        update_size(ptr);
        update_size(right_son);
        return right_son;
    }
};

template<class ValueType>
class Iterator {
 private:
    friend class Set<ValueType>;
    Node<ValueType>* ptr;
    const Set<ValueType>* owner;

    Iterator(Node<ValueType>* ptr, const Set<ValueType>* owner) : ptr(ptr), owner(owner)
    {}

 public:
    Iterator()
    {}

    Iterator(const Iterator& it) : ptr(it.ptr), owner(it.owner)
    {}

    Iterator(Iterator&& it) : ptr(std::move(it.ptr)), owner(std::move(it.owner))
    {}

    Iterator& operator =(const Iterator& it) {
        if (this == &it) return *this;
        Iterator tmp(it);
        swap(tmp);
        return *this;
    }

    Iterator& operator =(Iterator&& it) {
        swap(it);
        return *this;
    }

    void swap(Iterator& it) {
        std::swap(this->ptr, it.ptr);
        std::swap(this->owner, it.owner);
    }

    Iterator& operator++() {
        if (ptr == owner->max_value) {
            ptr = nullptr;
        } else {
            ptr = ptr->next();
        }
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    Iterator& operator--() {
        if (ptr == nullptr) {
            ptr = owner->max_value;
        } else {
            ptr = ptr->prev();
        }
        return *this;
    }

    Iterator operator--(int) {
        Iterator tmp(*this);
        --(*this);
        return tmp;
    }

    bool operator==(const Iterator& it) const {
        return (owner == it.owner) && (ptr == it.ptr);
    }

    bool operator!=(const Iterator& it) const {
        return !(*this == it);
    }

    const ValueType& operator*() const {
        return ptr->value;
    }

    const ValueType* operator->() const {
        return &ptr->value;
    }
};