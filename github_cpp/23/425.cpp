// =====================================================================================
// 
//       Filename:  skip_list.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/25/2016 08:34:11 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  李锐, root@lirui.in
//        License:  Copyright © 2016 李锐. All Rights Reserved.
// 
// =====================================================================================
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int MAX_LEVEL = 10;

template<class T>
class skip_node
{
public:
    int key;
    T value;
    skip_node<T> *next_in_level[MAX_LEVEL];//every node's next in every level
    ~skip_node();
};

template<class T>
skip_node<T>::~skip_node()
{
    printf("skip node destructor...\n");
    for(int i = 0; i < MAX_LEVEL; i++)
    {
         delete next_in_level[i];
    }
}

template<class T>
class skip_list
{
public:
    int level;//skip list's current level num
    skip_list();
    ~skip_list();
    skip_node<T> *header;
    skip_node<T>* search_by_key(int key);
    bool insert_node(int key, T value);
    bool delete_by_key(int key);
private:
    skip_node<T>* create_skip_node(int key, T value);
    int get_random_level();
};

template<class T>
skip_list<T>::skip_list()
{
    //header no key no value
    header = new skip_node<T>;
    for(int i = 0; i < MAX_LEVEL; i++)
    {
        header->next_in_level[i] = NULL;
    }
    level = 0;
}

template<class T>
skip_list<T>::~skip_list()
{
    printf("skip list destructor\n");
    //delete header;
}

template<class T>
skip_node<T>* skip_list<T>::create_skip_node(int key, T value)
{
    skip_node<T> *p = new skip_node<T>;
    p->key = key;
    p->value = value;
    for(int i = 0; i < MAX_LEVEL; i++)
    {
        p->next_in_level[i] = NULL;
    }
    return p;
}

template<class T>
int skip_list<T>::get_random_level()
{
    int level = 0;
    while(rand() % 2)
    {
        level++;
    }
    if(level >= MAX_LEVEL)
        level = MAX_LEVEL - 1;
    return level;
}

template<class T>
bool skip_list<T>::insert_node(int key, T value)
{
    //find in every level in the past skip list
    //which node is the last smaller than key
    skip_node<T> *last_smaller_in_level[MAX_LEVEL];
    skip_node<T> *tmp = header;
    for(int i = 0; i <= level; i++)
    {
        while(tmp->next_in_level[i] != NULL)
        {
            if(tmp->next_in_level[i]->key == key)
            {
                printf("can't insert same key\n");
                return false;
            }
            if(tmp->next_in_level[i]->key > key)
                break;
            else
                tmp = tmp->next_in_level[i];
        }
        last_smaller_in_level[i] = tmp;
    }
    //random how much level to inserit
    //build a new skip list
    int insert_level = get_random_level();
    printf("key %d insert_level %d\n", key, insert_level);
    skip_node<T> *p = create_skip_node(key, value);
    if(insert_level > level)
    {
        for(int i = 0; i <= level; i++)
        {
            skip_node<T> *tmp2 = last_smaller_in_level[i]->next_in_level[i];
            last_smaller_in_level[i]->next_in_level[i] = p;
            p->next_in_level[i] = tmp2;
        }
        for(int i = level + 1; i <= insert_level; i++)
        {
            header->next_in_level[i] = p;
        }
        level = insert_level;
    }
    else
    {
        for(int i = 0; i <= insert_level; i++)
        {
            skip_node<T> *tmp2 = last_smaller_in_level[i]->next_in_level[i];
            last_smaller_in_level[i]->next_in_level[i] = p;
            p->next_in_level[i] = tmp2;
        }
    }
    return true;
}

template<class T>
skip_node<T>* skip_list<T>::search_by_key(int key)
{
    //from top to bottom
    //from left to right
    skip_node<T> *tmp = header;
    for(int i = 0; i <= level; i++)
    {
        while(tmp->next_in_level[i] != NULL)
        {
            if(tmp->next_in_level[i]->key > key)
            {
                break;
            }
            else if(tmp->next_in_level[i]->key == key)
            {
                return tmp->next_in_level[i];
            }
            tmp = tmp->next_in_level[i];
        }
    }
    return NULL;
}

template<class T>
bool skip_list<T>::delete_by_key(int key)
{
    //first serach it
    //find last node in all level
    skip_node<T> *last_in_level[MAX_LEVEL];
    for(int i = 0; i < MAX_LEVEL; i++)
        last_in_level[i] = NULL;
    skip_node<T> *tmp = header;
    for(int i = 0; i <= level; i++)
    {
        while(tmp->next_in_level[i] != NULL)
        {
            if(tmp->next_in_level[i]->key > key)
            {
                break;
            }
            else if(tmp->next_in_level[i]->key == key)
            {
                last_in_level[i] = tmp;
                break;
            }
            tmp = tmp->next_in_level[i];
        }
    }
    for(int i = 0; i <= level; i++)
    {
        if(last_in_level[i] == NULL)
            return false;
        tmp = last_in_level[i]->next_in_level[i];
        last_in_level[i]->next_in_level[i] = tmp->next_in_level[i];
    }
    delete tmp;
    for(int i = level; i > 0; i--)
    {
        if(header->next_in_level[i] == NULL)
            level--;
    }
}

int main()
{
    skip_list<int> test_list;
    for(int i = 10; i >=0; i--)
    {
        test_list.insert_node(i, i);
    }
    test_list.delete_by_key(0);
    test_list.delete_by_key(1);
    for(int i = 0; i < 10; i++)
    {
        skip_node<int> *res = test_list.search_by_key(i);
        if(res != NULL)
            printf("%d ", res->value);
        else
            printf("%d NULL\n", i);
    }
    return 0;
}
