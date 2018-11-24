/*
 Copyright 2017 - 2018 Navigator Data (Pty) Ltd

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logging/logging.hpp"
#include "linked-list.hpp"

#define TRACE_ENABLED 0
#define DEBUG_ENABLED 0

LinkedList::LinkedList(NavDBClientLogger* logger)
{
    this->logger = logger;
}

// Linked list new/delete functions

int LinkedList::create(unsigned int data_copy_type)
{
    data = (linked_list_data_struct*)malloc(sizeof(struct linked_list_data_struct));
    if (data == NULL)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "malloc");
        return RET_ERROR;
    }
    memset(data, 0, sizeof(struct linked_list_data_struct));

    data->count = 0;
    data->data_copy_type = data_copy_type;
    first = NULL;
    last = NULL;

    return RET_OK;
}

int LinkedList::destroy(bool delete_data)
{
    TPRINT(logger, "");
    if (delete_all_nodes(delete_data) == RET_ERROR)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "");
        return RET_ERROR;
    }

    TPRINT(logger, "");
    free(data);
    data = NULL;

    TPRINT(logger, "");
    return RET_OK;
}

// Linked list navigation functions

LinkedListNode* LinkedList::get_first()
{
    return first;
}

LinkedListNode* LinkedList::get_last()
{
    return last;
}

bool LinkedList::loop_start_to_end(LinkedListNode** node)
{
    if (get_count() == 0)
    {
        return false;
    }

    if (*node == NULL)
    {
        *node = first;
    } else
    {
        *node = (*node)->get_next();
    }

    if (*node != NULL)
    {
        return true;
    }

    return false;
}

bool LinkedList::loop_end_to_start(LinkedListNode** node)
{
    if (get_count() == 0)
    {
        return false;
    }

    if (*node == NULL)
    {
        *node = last;
    } else
    {
        *node = (*node)->get_prev();
    }

    if (*node != NULL)
    {
        return true;
    }

    return false;
}

// Linked list get functions

size_t LinkedList::get_count()
{
    return data->count;
}

int LinkedList::get_index_by_node(bool* found,
                                  size_t* ret_index,
                                  LinkedListNode* linked_list_node)
{
    // Start at the linked list's first node
    LinkedListNode* lle = first;

    *found = false;
    *ret_index = 0;
    size_t index = 0;
    while (lle != NULL)
    {
        // Test node
        if (lle == linked_list_node)
        {
            *found = true;
            *ret_index = index;
            return RET_OK;
        }

        // Go to the next node
        lle = lle->get_next();
        index++;
    }

    return RET_OK;
}

int LinkedList::get_node_by_index(bool* found,
                                  LinkedListNode** linked_list_node,
                                  size_t get_index)
{
    // Start at the linked list's first node
    LinkedListNode* lle = first;

    *found = false;
    size_t index = 0;
    *linked_list_node = NULL;
    while (lle != NULL)
    {
        // Test node
        DPRINT(logger,
               "if (index: %llu == get_index: %llu)",
               index,
               get_index);

        if (index == get_index)
        {
            *found = true;
            *linked_list_node = lle;
            return RET_OK;
        }

        // Go to the next node
        lle = lle->get_next();
        index++;
    }

    return RET_OK;
}

LinkedListNode* LinkedList::get_node_by_index(size_t get_index)
{
    LinkedListNode* node = NULL;
    bool found = false;

    if (get_node_by_index(&found,
                          &node,
                          get_index) == RET_ERROR)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "");
        return NULL;
    }

    return node;
}

int LinkedList::get_first_index_by_data_ref(bool* found,
                                            size_t* index,
                                            LinkedListNode* linked_list_node,
                                            void* data)
{
    // Cannot get a non-ref linked list by ref
    if (this->data->data_copy_type != DATA_COPY_REF)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot get a non-ref linked list by ref");
        return RET_ERROR;
    }

    // Start at the linked list's first node
    LinkedListNode* lle = first;

    *found = false;
    *index = 0;
    linked_list_node = NULL;
    while (lle != NULL)
    {
        // Test node
        if (lle->get_data() == data)
        {
            *found = true;
            linked_list_node = lle;
            return RET_OK;
        }

        // Go to the next node
        lle = lle->get_next();
        (*index)++;
    }

    return RET_OK;
}

int LinkedList::get_first_index_by_data_value(bool* found,
                                              size_t* index,
                                              LinkedListNode* linked_list_node,
                                              void* data)
{
    // Cannot get a non-value linked list by value
    if (this->data->data_copy_type != DATA_COPY_VALUE)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot get a non-value linked list by value");
        return RET_ERROR;
    }

    // Start at the linked list's first node
    LinkedListNode *lle = first;

    *found = false;
    *index = 0;
    linked_list_node = NULL;
    while (lle != NULL)
    {
        // Test node
        if (memcmp(lle->get_data(),
                   data,
                   lle->get_size()) == 0)
        {
            *found = true;
            linked_list_node = lle;
            return RET_OK;
        }

        // Go to the next node
        lle = lle->get_next();
        (*index)++;
    }

    return RET_OK;
}

// Linked list add/set functions

int LinkedList::add_node_with_data_ref(char** data,
                                       size_t size,
                                       bool delete_data)
{
    // Cannot add non-ref data to a ref-type linked list
    if (this->data->data_copy_type != DATA_COPY_REF)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot add non-ref data to a ref-type linked list");
        return RET_ERROR;
    }

    if (data != NULL)
    {
        DPRINT(logger,
               "data: %p",
               *data);
    }

    // Allocate new memory and setup new node
    LinkedListNode* new_node = new LinkedListNode(delete_data);
    if (new_node == NULL)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "new");
        return RET_ERROR;
    }

    if (data != NULL)
    {
        new_node->set_data_ref(*data,
                               size);
    }

    new_node->set_prev(last);

    // Set the current last link node's next to point to the new node
    DPRINT(logger,
           "last: %p",
           static_cast<void*>(last));
    if (last != NULL)
    {
        DPRINT(logger,
               "last: %p last->get_next(): %p new_node: %p",
               static_cast<void*>(last),
               static_cast<void*>(last->get_next()),
               static_cast<void*>(new_node));
        last->set_next(new_node);
    }

    // Set linked list's first node to the new node if this is the very first node
    if (this->data->count == 0)
    {
        first = new_node;
    }

    // Append means the new node is the last node
    last = new_node;

    // Increase linked list count
    this->data->count++;

    return RET_OK;
}

int LinkedList::add_node_with_data_value(char** data,
                                         size_t size,
                                         bool delete_data)
{
    // Cannot add non-value data to a value-type linked list
    if (this->data->data_copy_type != DATA_COPY_VALUE)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot add non-value data to a value-type linked list");
        return RET_ERROR;
    }

    // Allocate new memory and setup new node
    LinkedListNode* new_node = new LinkedListNode(delete_data);
    new_node->set_data_value(*data,
                             size);

    new_node->set_prev(this->last);

    // Set the current last link node's next to point to the new node
    if (last != NULL)
    {
        last->set_next(new_node);
    }

    // Set linked list's first node to the new node if this is the very first node
    if (this->data->count == 0)
    {
        first = new_node;
    }

    // Append means the new node is the last node
    last = new_node;

    // Increase linked list count
    this->data->count++;

    return RET_OK;
}

int LinkedList::add_unique_node_with_data_ref(bool* found,
                                              char** data,
                                              size_t size,
                                              bool delete_data)
{
    // Cannot add a non-ref linked list by ref
    if (this->data->data_copy_type != DATA_COPY_REF)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot add a non-ref linked list by ref");
        return RET_ERROR;
    }

    size_t index = 0;
    LinkedListNode* linked_list_node = NULL;

    get_first_index_by_data_ref(found,
                                &index,
                                linked_list_node,
                                data);

    if (*found == true)
    {
        return RET_OK;
    }

    return add_node_with_data_ref(data,
                                  size,
                                  delete_data);
}

int LinkedList::add_unique_node_with_data_value(bool* found,
                                                char** data,
                                                size_t size,
                                                bool delete_data)
{
    // Cannot get a non-value linked list by value
    if (this->data->data_copy_type != DATA_COPY_VALUE)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot get a non-value linked list by value");
        return RET_ERROR;
    }

    size_t index = 0;
    LinkedListNode* linked_list_node = NULL;

    get_first_index_by_data_value(found,
                                  &index,
                                  linked_list_node,
                                  data);

    if (*found == true)
    {
        return RET_OK;
    }

    return add_node_with_data_value(data,
                                    size,
                                    delete_data);
}

// Add nodes with the specified data until the index is reached (used for padding nodes)
int LinkedList::add_with_data_ref_null_until_index(size_t index)
{
    while (data->count < index + 1)
    {
        if (add_node_with_data_ref(NULL,
                                   0,
                                   false) == RET_ERROR)
        {
            EPRINT(logger,
                   EPRINT_ERROR__FAILED,
                   "");
            return RET_ERROR;
        }
    }

    return RET_OK;
}

// Add nodes with the specified data until the index is reached (used for padding nodes)
int LinkedList::add_with_data_value_null_until_index(size_t index)
{
    while (data->count < index + 1)
    {
        if (add_node_with_data_value(NULL,
                                     0,
                                     false) == RET_ERROR)
        {
            EPRINT(logger,
                   EPRINT_ERROR__FAILED,
                   "");
            return RET_ERROR;
        }
    }

    return RET_OK;
}

int LinkedList::set_node_by_index_with_data_ref(size_t index,
                                                char** data,
                                                size_t size,
                                                bool setting_add_with_data_value_null_until_index)
{
    // Cannot set a non-ref linked list by ref
    if (this->data->data_copy_type != DATA_COPY_REF)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot set a non-ref linked list by ref");
        return RET_ERROR;
    }

    // Add nodes until the given index is reached (if specified)
    if (setting_add_with_data_value_null_until_index == true)
    {
        if (add_with_data_ref_null_until_index(index) == RET_ERROR)
        {
            EPRINT(logger,
                   EPRINT_ERROR__FAILED,
                   "add_with_data_ref_null_until_index");
            return RET_ERROR;
        }
    }

    bool found = false;
    LinkedListNode* node = NULL;

    // Look for the object id as an index
    if (get_node_by_index(&found,
                          &node,
                          index) == RET_ERROR)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "");
        return RET_ERROR;
    }

    if (found == false)
    {
        EPRINT(logger,
               EPRINT_ERROR__NOT_FOUND,
               "");
        return RET_ERROR;
    }

    // Set data and size
    node->set_data_ref(*data,
                       size);

    return RET_OK;
}

int LinkedList::set_node_by_index_with_data_value(size_t index,
                                                  char** data,
                                                  size_t size,
                                                  bool setting_add_with_data_value_null_until_index)
{
    // Cannot set a non-value linked list by value
    if (this->data->data_copy_type != DATA_COPY_VALUE)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot set a non-value linked list by value");
        return RET_ERROR;
    }

    // Add nodes until the given index is reached (if specified)
    if (setting_add_with_data_value_null_until_index == true)
    {
        if (add_with_data_value_null_until_index(index) == RET_ERROR)
        {
            EPRINT(logger,
                   EPRINT_ERROR__FAILED,
                   "");
            return RET_ERROR;
        }
    }

    bool found = false;
    LinkedListNode* node = NULL;

    // Look for the object id as an index
    if (get_node_by_index(&found,
                          &node,
                          index) == RET_ERROR)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "");
        return RET_ERROR;
    }

    if (found == false)
    {
        EPRINT(logger,
               EPRINT_ERROR__NOT_FOUND,
               "");
        return RET_OK;
    }

    // Set data and size
    node->set_data_value(*data,
                         size);

    return RET_OK;
}


int LinkedList::delete_node_unlink_and_free(LinkedListNode** linked_list_node,
                                            size_t index)
{
    LinkedListNode* prev = (*linked_list_node)->get_prev();
    LinkedListNode* next = (*linked_list_node)->get_next();

    // Free the list node that has been deleted/unlinked
    DPRINT(logger, "freeing node: %p (index: %llu) with prev: %p and next: %p",
           static_cast<void*>(*linked_list_node),
           index,
           static_cast<void*>(prev),
           static_cast<void*>(next));

    delete *linked_list_node;
    *linked_list_node = NULL;

    if (prev != NULL)
    {
        prev->set_next(next);
    }

    if (next != NULL)
    {
        next->set_prev(prev);
    }

    if (index == 0)
    {
        first = next;
    }

    if (index + 1 == data->count)
    {
        last = prev;
    }

    return RET_OK;
}

// Linked list delete functions

int LinkedList::delete_node_with_data_ref(void* data)
{
    // Cannot delete a non-ref linked list by ref
    if (this->data->data_copy_type != DATA_COPY_REF)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot delete a non-ref linked list by ref");
        return RET_ERROR;
    }

    // If there are no nodes in the linked list then return ok
    if (this->data->count == 0)
    {
        return RET_OK;
    }

    // Start at the linked list's first node
    LinkedListNode* lle_next = NULL;
    LinkedListNode* lle = first;
    size_t index = 0;
    while (lle != NULL)
    {
        // Determine the next node before potentially deleting the current node
        lle_next = lle->get_next();

        // If the current list node matches the list node to delete the unlink the node to be deleted
        if (lle->get_data() == data)
        {
            delete_node_unlink_and_free(&lle,
                                        index);
            lle = NULL;
            this->data->count--;
        }

        // Set the current node to the next node
        lle = lle_next;
        index++;
    }

    return RET_OK;
}

int LinkedList::delete_node_with_data_value(void* data)
{
    // Cannot delete a non-value linked list by value
    if (this->data->data_copy_type != DATA_COPY_VALUE)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "cannot delete a non-value linked list by value");
        return RET_ERROR;
    }

    // If there are no nodes in the linked list then return ok
    if (this->data->count == 0)
    {
        return RET_OK;
    }

    // Start at the linked list's first node
    LinkedListNode* lle_next = NULL;
    LinkedListNode* lle = first;
    size_t index = 0;

    TPRINT(logger, "");
    while (lle != NULL)
    {
        // Determine the next node before potentially deleting the current node
        lle_next = lle->get_next();

        // A size of zero should never happen
        if (lle->get_size() == 0)
        {
            EPRINT(logger,
                   EPRINT_ERROR__UNEXPECTED_CONDITION,
                   "");
            return RET_ERROR;
        }

        // If the current list node matches the list node to delete the unlink the node to be deleted
        if (memcmp(lle->get_data(),
                   data,
                   lle->get_size()) == 0)
        {
            delete_node_unlink_and_free(&lle,
                                        index);
            lle = NULL;
            this->data->count--;
        }

        // Set the current node to the next node
        lle = lle_next;
        index++;
    }

    return RET_OK;
}

int LinkedList::delete_node_by_index(bool* found,
                                     size_t index)
{
    *found = false;
    LinkedListNode* lle = NULL;

    get_node_by_index(found,
                      &lle,
                      index);

    if (*found == true)
    {
        delete_node_unlink_and_free(&lle,
                                    index);
        lle = NULL;
        this->data->count--;
    }

    return RET_OK;
}

int LinkedList::delete_node_by_node(bool* found,
                                    LinkedListNode** node)
{
    size_t index = 0;
    if (get_index_by_node(found,
                          &index,
                          *node) == RET_ERROR)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "get_index_by_node");
        return RET_ERROR;
    }

    if (*found == false)
    {
        return RET_OK;
    }

    if (delete_node_by_index(found,
                             index) == RET_ERROR)
    {
        EPRINT(logger,
               EPRINT_ERROR__FAILED,
               "");
        return RET_ERROR;
    }

    return RET_OK;
}

int LinkedList::delete_all_nodes(bool delete_data)
{
    // Start at the linked list's first node
    LinkedListNode* lle = first;
    LinkedListNode* lle_next = NULL;

    while (lle != NULL)
    {
        // Save the next node
        lle_next = lle->get_next();

        // Free this node
        delete lle;
        lle = NULL;

        // Go to the next node
        lle = lle_next;
    }

    this->data->count = 0;
    this->first = NULL;
    this->last = NULL;

    return RET_OK;
}

// Linked list verify & print functions

int LinkedList::verify()
{
    TPRINT(logger, "");
    size_t index = 0;

    // Verify that data is not null
    if (data == NULL)
    {
        EPRINT(logger,
               EPRINT_ERROR__IS_NULL,
               "list data");
        return RET_ERROR;
    }

    // Get the count
    size_t count = data->count;

    // Start at the linked list's first node
    LinkedListNode* lle = first;
    LinkedListNode* lle_prior = NULL;

    while (lle != NULL)
    {
        DPRINT(logger,
               "node: %p node-next: %p iteration: %llu",
               static_cast<void*>(lle),
               static_cast<void*>(lle->get_next()),
               index);

        // Check the prev node link
        if (index > 0)
        {
            if (lle->get_prev() == NULL)
            {
                EPRINT(logger,
                       EPRINT_ERROR__UNEXPECTED_CONDITION,
                       "");
                return RET_ERROR;
            }
        }

        if (index == 1)
        {
            if (lle->get_prev() != first)
            {
                EPRINT(logger,
                       EPRINT_ERROR__UNEXPECTED_CONDITION,
                       "");
                return RET_ERROR;
            }
        }

        if (index + 1 == count)
        {
            if (lle->get_next() != NULL)
            {
                EPRINT(logger,
                       EPRINT_ERROR__UNEXPECTED_CONDITION,
                       "");
                return RET_ERROR;
            }
        }

        // Go to the next node and increment the index
        lle_prior = lle;
        lle = lle->get_next();
        index++;
    }

    if (lle_prior != last)
    {
        // The final node in the iteration: %p is not the list's last pointed to node
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "");
        return RET_ERROR;
    }

    // Nodes iterated through: x but count is: y
    if (index != count)
    {
        EPRINT(logger,
               EPRINT_ERROR__UNEXPECTED_CONDITION,
               "");
        return RET_ERROR;
    }

    return RET_OK;
}

int LinkedList::print(bool print_data_as_strings)
{
    IPRINT(logger,
           "count: %llu", data->count);

    if (data->data_copy_type == DATA_COPY_REF)
    {
        IPRINT(logger,
               "data_copy_type: DATA_COPY_REF");
    } else
    if (data->data_copy_type == DATA_COPY_VALUE)
    {
        IPRINT(logger,
               "data_copy_type: DATA_COPY_VALUE");
    } else {
        IPRINT(logger,
               "data_copy_type: %u (unknown)",
               data->data_copy_type);
    }

    // Start at the linked list's first node
    LinkedListNode* lle = first;
    size_t index = 0;
    while (lle != NULL)
    {
        // Print node details
        IPRINT(logger,
               "node index: %llu node: %p node->get_prev(): %p node->get_next(): %p with data: %p size: %llu",
               index,
               static_cast<void*>(lle),
               static_cast<void*>(lle->get_prev()),
               static_cast<void*>(lle->get_next()),
               static_cast<void*>(lle->get_data()),
               lle->get_size());

        if (print_data_as_strings == true)
        {
            IPRINT(logger,
                   " [%s]", lle->get_data());
        }
        TPRINT(logger, "");

        // Go to the next node
        lle = lle->get_next();
        index++;
    }

    TPRINT(logger, "");
    return RET_OK;
}
