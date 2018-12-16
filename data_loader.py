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
   
    def __init__(self, path):
        pairs = load_pairwise_programs(path)
        random.shuffle(pairs)

        left_trees = []
        right_trees = []
        labels = []
        for i in trange(len(pairs)):
            left_trees.append(pairs[i][0])
            right_trees.append(pairs[i][1])
            labels.append(pairs[i][2])

        self.left_trees = left_trees
        self.right_trees = right_trees
        self.labels = labels


def load_pairwise_programs(path):
    print("Loading pairwise data............")
    pairs = []
    with open(path,"r") as f:
      
        csv_reader = csv.reader(f, delimiter=',')
        count = 0
        for row in tqdm(csv_reader):
            if count < 5000:
                left_path = row[0]
                right_path = row[1]
                left_tree = load_single_program(left_path)
                right_tree = load_single_program(right_path)
                pairs.append((left_tree,right_tree,int(row[2])))
            count += 1
            # print(count)
            # labels.append(row[2])

    return pairs

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
  
    return result

def load_single_program_for_live_test(file_path):
    result = []
    labels = []
    nodes_ids_list = []
    nodes_types_list = []
    splits = file_path.split("/")
    
    label = splits[len(splits)-2]
    # print(label)
    ast_representation = build_tree(file_path)
    if ast_representation.HasField("element"):
        root = ast_representation.element
        tree, size, node_ids, node_types = _traverse_tree(root)

    result.append({
        'tree': tree, 'label': label
    })
    labels.append(label)
    nodes_ids_list.append(node_ids)
    nodes_types_list.append(node_types)

    return result, labels, nodes_ids_list, nodes_types_list

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