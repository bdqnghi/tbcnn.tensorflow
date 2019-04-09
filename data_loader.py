import numpy as np
import os
from os import listdir
from os.path import isfile, join
import collections
import re
from tqdm import trange
from tqdm import *
import random
import pickle
import msgpack
import csv

class MonoLanguageProgramData():
   
    def __init__(self, path, train_test_val, n_classes):
        cached_path = "cached"
        base_name = os.path.basename(path)
        if train_test_val == 0:
           saved_input_filename = "%s/%s-%d-train.pkl" % (cached_path, path.split("/")[-2], n_classes)
        if train_test_val == 1:
           saved_input_filename = "%s/%s-%d-test.pkl" % (cached_path, path.split("/")[-2], n_classes)
        if train_test_val == 2:
           saved_input_filename = "%s/%s-%d-val.pkl" % (cached_path, path.split("/")[-2], n_classes)
        print(saved_input_filename)
        if os.path.exists(saved_input_filename):
            with open(saved_input_filename, 'rb') as file_handler:
                trees, labels = pickle.load(file_handler)

        else:
            trees, labels = load_program_data(path,n_classes)
            data = (trees, labels)
            with open(saved_input_filename, 'wb') as file_handler:
                pickle.dump(data, file_handler, protocol=pickle.HIGHEST_PROTOCOL)


        print("Number of all data : " + str(len(trees)))
      
        self.trees = trees
        self.labels = labels

class CrossLanguageProgramData():
   
    def __init__(self, path, train_test_val, n_classes):
        cached_path = "cached"

        
        saved_input_filename = "%s/pairwise_%s.pkl" % (cached_path, path.split("/")[-1].split(".")[0])
    
        print(saved_input_filename)
        if os.path.exists(saved_input_filename):
            with open(saved_input_filename, 'rb') as file_handler:
                pairs = pickle.load(file_handler)
        else:
            pairs = load_pairwise_programs(path, train_test_val)
            with open(saved_input_filename, 'wb') as file_handler:
                pickle.dump(pairs, file_handler, protocol=pickle.HIGHEST_PROTOCOL)

        # random.shuffle(pairs)

        # if train_test_val == 0:
        #     pairs = random.sample(pairs,10000)
            
        left_trees = []
        right_trees = []
        labels = []
        for i in trange(len(pairs)):
            left_trees.append(pairs[i][0])
            right_trees.append(pairs[i][1])
            labels.append(pairs[i][2])


        print("Number of all data : " + str(len(left_trees)))
        self.left_trees = left_trees
        self.right_trees = right_trees
        self.labels = labels
        

class CrossLanguageProgramDataForLiveTest():
   
    def __init__(self, path, train_test_val, n_classes):
        cached_path = "cached"

        
        pairs, left_node_ids_list, right_node_ids_list = load_pairwise_programs_for_live_test(path, train_test_val)
          
        left_trees = []
        right_trees = []
        labels = []
        for i in trange(len(pairs)):
            left_trees.append(pairs[i][0])
            right_trees.append(pairs[i][1])
            labels.append(pairs[i][2])


        print("Number of all data : " + str(len(left_trees)))
        self.left_trees = left_trees
        self.right_trees = right_trees
        self.left_node_ids_list = left_node_ids_list
        self.right_node_ids_list = right_node_ids_list
        self.labels = labels

def load_pairwise_programs(path, train_test_val):
    print("Loading pairwise data............")
    pairs = []
    all_pairs_index = []
    with open(path,"r") as f:
        data = f.readlines()
        for line in data:
            all_pairs_index.append(line.replace("\n",""))
  
    if train_test_val == 0:
        all_pairs_index = random.sample(all_pairs_index, 100)
    

    for i, pair in tqdm(enumerate(all_pairs_index)):
        splits = pair.split(",")
        left_path = splits[0]
        right_path = splits[1]
        left_tree = load_single_program(left_path)
        right_tree = load_single_program(right_path)
        pairs.append((left_tree,right_tree,int(splits[2])))

    return pairs


def load_single_pair_for_live_test(left_path, right_path, label):
    print("Loading pairwise data............")
    pairs = []
    
    left_node_ids_list = []
    right_node_ids_list = []
  
    left_tree, _ , left_node_ids, _, = load_single_program(left_path)
    right_tree, _ , right_node_ids, _ = load_single_program(right_path)
    pairs.append((left_tree,right_tree,int(label)))
    left_node_ids_list.append(left_node_ids)
    right_node_ids_list.append(right_node_ids)

    return pairs, left_node_ids_list, right_node_ids_list


def load_pairwise_programs_for_live_test(path, train_test_val):
    print("Loading pairwise data............")
    pairs = []
    all_pairs_index = []
   
    left_node_ids_list = []
    right_node_ids_list = []
    with open(path,"r") as f:
        data = f.readlines()
        for line in data:
            print(line)
            all_pairs_index.append(line.replace("\n",""))
  
    for i, pair in tqdm(enumerate(all_pairs_index)):
        splits = pair.split(",")
        left_path = splits[0]
        right_path = splits[1]
        left_tree, _ , left_node_ids, _, = load_single_program(left_path)
        right_tree, _ , right_node_ids, _ = load_single_program(right_path)
        pairs.append((left_tree,right_tree,int(splits[2])))
        left_node_ids_list.append(left_node_ids)
        right_node_ids_list.append(right_node_ids)

    return pairs, left_node_ids_list, right_node_ids_list

def build_tree(script):
    """Builds an AST from a script."""
  
    with open(script, 'rb') as file_handler:
        data_source = pickle.load(file_handler)
    return data_source


def load_single_program(file_path):
    splits = file_path.split("/")
    label = splits[len(splits)-2]
    # print(label)
    ast_representation = build_tree(file_path)
    if ast_representation.HasField("element"):
        root = ast_representation.element
        tree, size, node_ids, node_types = _traverse_tree(root)

    result = {
        'tree': tree, 'label': label
    }
  
    return result, label, node_ids, node_types

def load_single_program_for_live_test(file_path):
    result = []
    splits = file_path.split("/")
    label = "1"
    # print(label)
    ast_representation = build_tree(file_path)
    if ast_representation.HasField("element"):
        root = ast_representation.element
        tree, size, node_ids, node_types = _traverse_tree(root)

    result.append({
        'tree': tree, 'label': label
    })
  
    return result, label, node_ids, node_types

def load_single_program_for_bilateral_live_test(file_pkl_path, common_part, node_count):
    result = []
    # labels = []
    # nodes_ids_list = []
    # nodes_types_list = []
    splits = file_pkl_path.split("/")
    
    label = splits[len(splits)-3]
    # print(label)
    ast_representation = build_tree(file_pkl_path)
    if ast_representation.HasField("element"):
        root = ast_representation.element
        tree, size, node_ids, node_types, nodes_common_part_vector = _traverse_tree_2(root, common_part, node_count)

    result.append({
        'tree': tree, 'label': label
    })
    # labels.append(label)
    # nodes_ids_list.append(node_ids)
    # nodes_types_list.append(node_types)
    return result, label, node_ids, node_types, nodes_common_part_vector
    # return result, labels, nodes_ids_list, nodes_types_list

def load_program_data(directory, n_classes):

    result = []
    labels = []
    for i in trange(1, n_classes + 1):
        dir_path = os.path.join(directory, str(i))
        for file in listdir(dir_path):
            file_path = os.path.join(dir_path, file)
            # print(file_path)
            splits = file_path.split("/")
          
            label = splits[len(splits)-2]
            # print(label)
            ast_representation = build_tree(file_path)

            if ast_representation.HasField("element"):
                root = ast_representation.element
                tree, size, _, _ = _traverse_tree(root)

            result.append({
                'tree': tree, 'label': label
            })
            labels.append(label)
    # random.shuffle(result)
    # random.shuffle(result)
    return result, list(set(labels))

def _traverse_tree(root):
    num_nodes = 1
    queue = [root]

    root_json = {
        "node": str(root.kind),

        "children": []
    }
    queue_json = [root_json]
    node_ids = []
    node_types = []
    # nodes_id.append(root.id)
    while queue:
      
        current_node = queue.pop(0)
        num_nodes += 1
        # print (_name(current_node))
        current_node_json = queue_json.pop(0)

        node_ids.append(current_node.id)
        node_types.append(current_node.kind)
        
        children = [x for x in current_node.child]
        queue.extend(children)
       
        for child in children:
            # print "##################"
            #print child.kind

            child_json = {
                "node": str(child.kind),
                "children": []
            }

            current_node_json['children'].append(child_json)
            queue_json.append(child_json)
            
            # print current_node_json
  
    return root_json, num_nodes, node_ids, node_types

def _traverse_tree_2(root, common_part, node_count):
    print(common_part)
    print(node_count)
    num_nodes = 1
    queue = [root]

    root_json = {
        "node": str(root.kind),

        "children": []
    }
    queue_json = [root_json]
    node_ids = []
    node_types = []
    node_ids_vector = []
    # nodes_id.append(root.id)
    while queue:
      
        current_node = queue.pop(0)
        num_nodes += 1
        # print (_name(current_node))
        current_node_json = queue_json.pop(0)

        node_ids.append(current_node.id)
        node_types.append(current_node.kind)
       
        if str(current_node.kind) in common_part.keys() and str(current_node.kind) in node_count.keys():
            if node_count[str(current_node.kind)] <= common_part[str(current_node.kind)]:
                node_ids_vector.append(1)
        else:
            node_ids_vector.append(0)
        
        children = [x for x in current_node.child]
        queue.extend(children)
       
        for child in children:
            # print "##################"
            #print child.kind

            child_json = {
                "node": str(child.kind),
                "children": []
            }

            current_node_json['children'].append(child_json)
            queue_json.append(child_json)
            
            # print current_node_json
  
    return root_json, num_nodes, node_ids, node_types, node_ids_vector

def search_child_with_name(function_node, keyword):
    children = [x for x in function_node.child]
    found_correct_function = False
    for child in children:
        if "sort" in str(child.text.lower()):
            found_correct_function = True
    return found_correct_function

def search_function_node(ast_representation, keyword):
    function_node_id = None
    if ast_representation.HasField("element"):
        root = ast_representation.element
        queue = [root]
       
        root_json = {
            "node": str(root.kind),

            "children": []
        }
        queue_json = [root_json]
     
       
        while queue:
          
            current_node = queue.pop(0)
            children = [x for x in current_node.child]

            current_node_json = queue_json.pop(0)
            # print(current_node.text.lower(), current_node.kind)

            if current_node.kind == 12:
                found_correct_function = search_child_with_name(current_node, keyword)
                if found_correct_function:
                    for child in children:
                        if child.kind == 60:
                            function_node_id = child.id
                            return function_node_id


            
            queue.extend(children)
           
            for child in children:
                # print "##################"
                #print child.kind

                child_json = {
                    "node": str(child.kind),
                    "children": []
                }

                current_node_json['children'].append(child_json)
                queue_json.append(child_json)
            
            # print current_node_json
  
    return function_node_id


# if __name__ == "__main__":
#     file = "github_cpp_pkl/1/12.cpp.pb.pkl"
#     ast_representation = build_tree(file)
#     print(ast_representation)

#     if ast_representation.HasField("element"):
#         root = ast_representation.element
#         tree, size, nodes_id = _traverse_tree(root)
#         print(nodes_id)
#         print(len(nodes_id))
#         print(size)