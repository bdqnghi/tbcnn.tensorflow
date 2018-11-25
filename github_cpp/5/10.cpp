







#include <cstdlib>
#include "insertion_sort.hpp"



void insertion_sort(int *arr, unsigned int size)
{
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}



void insertion_sort_naive(list_t *list)
{
    for (int i = 1; i < size(list); i++) {
        int key = get_node(list, i)->data;
        int j = i - 1;
        while (j >= 0 && get_node(list, j)->data > key) {
            get_node(list, j + 1)->data = get_node(list, j)->data;
            j -= 1;
        }
        get_node(list, j + 1)->data = key;
    }
}



void insertion_sort(list_t *list)
{
    for (int i = 1; i < size(list); i++) {
        node_t *key_node = get_node(list, i);
        int j = i - 1;
        node_t *j_node;
        
        while (j >= 0 && ((j_node = get_node(list, j))->data) > key_node->data) {
            j -= 1;
            swap(list, key_node);
        }
    }
}
