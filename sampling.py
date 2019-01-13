"""Functions to help with sampling trees."""

import pickle
import numpy as np
import random
from tqdm import *

from keras.preprocessing.sequence import pad_sequences

def gen_samples(trees, labels, vectors, vector_lookup):
    """Creates a generator that returns a tree in BFS order with each node
    replaced by its vector embedding, and a child lookup table."""

    # encode labels as one-hot vectors
    label_lookup = {label: _onehot(i, len(labels)) for i, label in enumerate(labels)}
    # print vector_lookup

    for tree in trees:

        nodes = []
        children = []
        label = label_lookup[tree['label']]

        queue = [(tree['tree'], -1)]
        # print queue
        while queue:
            # print "############"
            node, parent_ind = queue.pop(0)
            # print node
            # print parent_ind
            node_ind = len(nodes)
            # print "node ind : " + str(node_ind)
            # add children and the parent index to the queue
            queue.extend([(child, node_ind) for child in node['children']])
            # create a list to store this node's children indices
            children.append([])
            # add this child to its parent's child list
            if parent_ind > -1:
                children[parent_ind].append(node_ind)
            
            n = str(node['node'])
            look_up_vector = vector_lookup[n]
            nodes.append(vectors[int(n)])
        # print "children list length: " + str(len(children))

        if len(nodes) > 5500 :
            print("Skipping nodes : " + str(len(nodes)))
            if len(children) < 800:
                yield (nodes, children, label)
        else:
            yield (nodes, children, label)


def batch_samples(gen, batch_size):
    """Batch samples from a generator"""
    nodes, children, labels = [], [], []
    samples = 0
    for n, c, l in gen:
        # print n
        # print c
        # print l
        nodes.append(n)
        children.append(c)
        labels.append(l)
        samples += 1
        if samples >= batch_size:
            yield _pad_batch(nodes, children, labels)
            nodes, children, labels = [], [], []
            samples = 0

    if nodes:
        yield _pad_batch(nodes, children, labels)

def batch_random_samples_2_sides(left_trees, right_trees, labels, vectors, vector_lookup, batch_size, batch_type="original"):
    """Creates a generator that returns a tree in BFS order with each node
    replaced by its vector embedding, and a child lookup table."""

  
    batch_left_nodes, batch_left_children, = [], []

    batch_right_nodes, batch_right_children = [], []
    samples = 0

    batch_labels = []
    for i in range(0,len(left_trees)):
      
        left_tree = left_trees[i]

        left_nodes = []
        left_children = []
        left_queue = [(left_tree['tree'], -1)]
        # print queue
        while left_queue:   
            node, parent_ind = left_queue.pop(0)    
            node_ind = len(left_nodes)   
            left_queue.extend([(child, node_ind) for child in node['children']])  
            left_children.append([])    
            if parent_ind > -1:
                left_children[parent_ind].append(node_ind)  
            
            n = str(node['node'])
            left_nodes.append(vectors[int(n)])
        

        
        
        right_tree = right_trees[i]
        right_nodes = []
        right_children = []
        right_queue = [(right_tree['tree'], -1)]
        # print queue
        while right_queue:   
            node, parent_ind = right_queue.pop(0)    
            node_ind = len(right_nodes)   
            right_queue.extend([(child, node_ind) for child in node['children']])  
            right_children.append([])    
            if parent_ind > -1:
                right_children[parent_ind].append(node_ind)      
            n = str(node['node'])
            right_nodes.append(vectors[int(n)])
      
        if (len(left_nodes) < 7000 and len(left_nodes) > 50) and (len(right_nodes) < 7000 and len(right_nodes) > 50):

            batch_left_nodes.append(left_nodes)
            batch_left_children.append(left_children)

            batch_right_nodes.append(right_nodes)
            batch_right_children.append(right_children)

            batch_labels.append(labels[i])

            samples += 1
        if samples >= batch_size:
            if batch_type == "original": 
                yield _pad_batch_siamese_2_side_original(batch_left_nodes, batch_left_children, batch_right_nodes, batch_right_children, batch_labels)
            else:
                yield _pad_batch_siamese_2_side(batch_left_nodes, batch_left_children, batch_right_nodes, batch_right_children, batch_labels)
            batch_left_nodes, batch_left_children = [], []

            batch_right_nodes, batch_right_children = [], []

            batch_labels = []
            samples = 0

    if batch_left_nodes and batch_right_nodes:
        if batch_type == "original": 
            yield _pad_batch_siamese_2_side_original(batch_left_nodes, batch_left_children, batch_right_nodes, batch_right_children, batch_labels)
        else:
            yield _pad_batch_siamese_2_side(batch_left_nodes, batch_left_children, batch_right_nodes, batch_right_children, batch_labels)


def _pad_batch(nodes, children, labels):
    if not nodes:
        return [], [], []
    max_nodes = max([len(x) for x in nodes])
    max_children = max([len(x) for x in children])
    feature_len = len(nodes[0][0])
    child_len = max([len(c) for n in children for c in n])

    nodes = [n + [[0] * feature_len] * (max_nodes - len(n)) for n in nodes]
    # pad batches so that every batch has the same number of nodes
    children = [n + ([[]] * (max_children - len(n))) for n in children]
    # pad every child sample so every node has the same number of children
    children = [[c + [0] * (child_len - len(c)) for c in sample] for sample in children]

    return nodes, children, label


def _onehot(i, total):
    return [1.0 if j == i else 0.0 for j in range(total)]


def _pad_batch_siamese_2_side(batch_left_nodes, batch_left_children, batch_right_nodes, batch_right_children, labels):
    max_left_nodes = max([len(x) for x in batch_left_nodes])
    max_right_nodes = max([len(x) for x in batch_right_nodes])

    max_left_children = max([len(x) for x in batch_left_children])
    max_right_children = max([len(x) for x in batch_right_children])

    max_nodes = max(max_left_nodes, max_right_nodes)
    max_children = max(max_left_children, max_right_children)

    left_masks, right_masks = _produce_mask_vector_2_side(batch_left_nodes, batch_right_nodes, max_left_nodes, max_right_nodes)
    batch_left_nodes, batch_left_children = _pad_batch_siamese(batch_left_nodes, batch_left_children, max_nodes, max_children)
    batch_right_nodes, batch_right_children = _pad_batch_siamese(batch_right_nodes, batch_right_children, max_nodes, max_children)

    # return (_pad_batch_siamese(batch_left_nodes, batch_left_children),left_masks), (_pad_batch_siamese(batch_right_nodes, batch_right_children),right_masks), labels
    return (batch_left_nodes, batch_left_children,left_masks), (batch_right_nodes, batch_right_children,right_masks), labels

def _produce_mask_vector(nodes, max_nodes):

    masks = []
    mask = [1 for i in range(max_nodes)]
    for n in nodes:        
        masks.append(mask)

    return masks

def _produce_mask_vector_2_side(left_nodes, right_nodes, max_left_nodes, max_right_nodes):
    # print(nodes)
    
    left_masks = _produce_mask_vector(left_nodes,max_left_nodes)
    right_masks = _produce_mask_vector(right_nodes,max_right_nodes)
    
    left_masks.extend(right_masks)
    all_padded = pad_sequences(left_masks, padding='post')
    
    return all_padded[:len(left_nodes), ...], all_padded[len(left_nodes):, ...]

def _pad_batch_siamese(nodes, children, max_nodes, max_children):
    if not nodes:
        return [], [], []
   
    feature_len = len(nodes[0][0])
    child_len = max([len(c) for n in children for c in n])

    nodes = [n + [[0] * feature_len] * (max_nodes - len(n)) for n in nodes]
    # pad batches so that every batch has the same number of nodes
    children = [n + ([[]] * (max_children - len(n))) for n in children]
    # pad every child sample so every node has the same number of children
    children = [[c + [0] * (child_len - len(c)) for c in sample] for sample in children]

  
    return nodes, children


def _pad_batch_siamese_2_side_original(batch_left_nodes, batch_left_children, batch_right_nodes, batch_right_children, labels):
    return _pad_batch_siamese_original(batch_left_nodes, batch_left_children), _pad_batch_siamese_original(batch_right_nodes, batch_right_children), labels


def _pad_batch_siamese_original(nodes, children):
    if not nodes:
        return [], [], []
    max_nodes = max([len(x) for x in nodes])
    max_children = max([len(x) for x in children])
    feature_len = len(nodes[0][0])
    child_len = max([len(c) for n in children for c in n])

    nodes = [n + [[0] * feature_len] * (max_nodes - len(n)) for n in nodes]
    # pad batches so that every batch has the same number of nodes
    children = [n + ([[]] * (max_children - len(n))) for n in children]
    # pad every child sample so every node has the same number of children
    children = [[c + [0] * (child_len - len(c)) for c in sample] for sample in children]

    return nodes, children

