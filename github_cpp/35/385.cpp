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

#include "logging/ccl_logging.h"
#include "linked-list.h"
#include "types/lists/linked-list.hpp"

extern "C" {

    LinkedList* newLinkedList(NavDBClientLogger* logger)
    {
        return new LinkedList(logger);
    }

    void deleteLinkedList(LinkedList* linked_list)
    {
        delete linked_list;
    }

    // Linked list new/delete functions

    int LinkedList_create(LinkedList* linked_list,
                          unsigned int data_copy_type)
    {
        return linked_list->create(data_copy_type);
    }

    int LinkedList_destroy(LinkedList* linked_list,
                           bool delete_data)
    {
        return linked_list->destroy(delete_data);
    }

    // Linked list navigation functions

    LinkedListNode* LinkedList_get_first(LinkedList* linked_list)
    {
        return linked_list->get_first();
    }

    LinkedListNode* LinkedList_get_last(LinkedList* linked_list)
    {
        return linked_list->get_last();
    }

    bool LinkedList_loop_start_to_end(LinkedList* linked_list,
                                      LinkedListNode** node)
    {
        return linked_list->loop_start_to_end(node);
    }

    bool LinkedList_loop_end_to_start(LinkedList* linked_list,
                                      LinkedListNode** node)
    {
        return linked_list->loop_end_to_start(node);
    }

    // Linked list get functions

    size_t LinkedList_get_count(LinkedList* linked_list)
    {
        return linked_list->get_count();
    }

    int LinkedList_get_index_by_node(LinkedList* linked_list,
                                     bool* found,
                                     size_t* ret_index,
                                     LinkedListNode* linked_list_node)
    {
        return linked_list->get_index_by_node(found,
                                              ret_index,
                                              linked_list_node);
    }

    LinkedListNode* LinkedList_get_node_by_index(LinkedList* linked_list,
                                                 size_t get_index)
    {
        return linked_list->get_node_by_index(get_index);
    }

    int LinkedList_get_first_index_by_data_ref(LinkedList* linked_list,
                                               bool* found,
                                               size_t* index,
                                               LinkedListNode* linked_list_node,
                                               char* data)
    {
        return linked_list->get_first_index_by_data_ref(found,
                                                        index,
                                                        linked_list_node,
                                                        data);
    }

    int LinkedList_get_first_index_by_data_value(LinkedList* linked_list,
                                                 bool* found,
                                                 size_t* index,
                                                 LinkedListNode* linked_list_node,
                                                 char* data)
    {
        return linked_list->get_first_index_by_data_value(found,
                                                          index,
                                                          linked_list_node,
                                                          data);
    }

    // Linked list add/set functions

    int LinkedList_add_node_with_data_ref(LinkedList* linked_list,
                                          char** data,
                                          size_t size,
                                          bool delete_data)
    {
        return linked_list->add_node_with_data_ref(data,
                                                   size,
                                                   delete_data);
    }

    int LinkedList_add_node_with_data_value(LinkedList* linked_list,
                                            char** data,
                                            size_t size,
                                            bool delete_data)
    {
        return linked_list->add_node_with_data_value(data,
                                                     size,
                                                     delete_data);
    }

    int LinkedList_add_unique_node_with_data_ref(LinkedList* linked_list,
                                                 bool* found,
                                                 char** data,
                                                 size_t size,
                                                 bool delete_data)
    {
        return linked_list->add_unique_node_with_data_ref(found,
                                                          data,
                                                          size,
                                                          delete_data);
    }

    int LinkedList_add_unique_node_with_data_value(LinkedList* linked_list,
                                                   bool* found,
                                                   char** data,
                                                   size_t size,
                                                   bool delete_data)
    {
        return linked_list->add_unique_node_with_data_value(found,
                                                            data,
                                                            size,
                                                            delete_data);
    }

    int LinkedList_add_with_data_ref_null_until_index(LinkedList* linked_list,
                                                      size_t index)
    {
        return linked_list->add_with_data_ref_null_until_index(index);
    }

    int LinkedList_add_with_data_value_null_until_index(LinkedList* linked_list,
                                                        size_t index)
    {
        return linked_list->add_with_data_value_null_until_index(index);
    }

    int LinkedList_set_node_by_index_with_data_ref(LinkedList* linked_list,
                                                   size_t index,
                                                   char** data,
                                                   size_t size,
                                                   bool setting_add_with_data_value_null_until_index)
    {
        return linked_list->set_node_by_index_with_data_ref(index,
                                                            data,
                                                            size,
                                                            setting_add_with_data_value_null_until_index);
    }

    int LinkedList_set_node_by_index_with_data_value(LinkedList* linked_list,
                                                     size_t index,
                                                     char** data,
                                                     size_t size,
                                                     bool setting_add_with_data_value_null_until_index)
    {
        return linked_list->set_node_by_index_with_data_value(index,
                                                              data,
                                                              size,
                                                              setting_add_with_data_value_null_until_index);
    }

    int LinkedList_delete_node_unlink_and_free(LinkedList* linked_list,
                                               LinkedListNode** linked_list_node,
                                               size_t index)
    {
        return linked_list->delete_node_unlink_and_free(linked_list_node,
                                                        index);
    }

    // Linked list delete functions

    int LinkedList_delete_node_with_data_ref(LinkedList* linked_list,
                                             char* data)
    {
        return linked_list->delete_node_with_data_ref(data);
    }

    int LinkedList_delete_node_with_data_value(LinkedList* linked_list,
                                               char* data)
    {
        return linked_list->delete_node_with_data_value(data);
    }

    int LinkedList_delete_node_by_index(LinkedList* linked_list,
                                        bool* found,
                                        size_t index)
    {
        return linked_list->delete_node_by_index(found,
                                                 index);
    }

    int LinkedList_delete_node_by_node(LinkedList* linked_list,
                                       bool* found,
                                       LinkedListNode** node)
    {
        return linked_list->delete_node_by_node(found,
                                                node);
    }

    int LinkedList_delete_all_nodes(LinkedList* linked_list,
                                    bool delete_data)
    {
        return linked_list->delete_all_nodes(delete_data);
    }

    // Linked list verify & print functions

    int LinkedList_verify(LinkedList* linked_list)
    {
        return linked_list->verify();
    }

    int LinkedList_print(LinkedList* linked_list,
                         bool print_data_as_strings)
    {
        return linked_list->print(print_data_as_strings);
    }

}
