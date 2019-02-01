# This file is just another version to test with 2 different AST tree on each side of the Bi-TBCNN
import os
import logging
import pickle
import tensorflow as tf
import numpy as np
import network as network
import sampling as sampling
from parameters import LEARN_RATE, EPOCHS, CHECKPOINT_EVERY, BATCH_SIZE, DROP_OUT
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score, precision_score, recall_score
import random
import sys
import json
import argparse
from data_loader import CrossLanguageProgramDataForLiveTest
import pandas as pd
from utils import scale_attention_score_by_group
import operator
# np.set_printoptions(threshold=np.nan)

parser = argparse.ArgumentParser()
parser.add_argument('--train_batch_size', type=int, default=10, help='train batch size')
parser.add_argument('--test_batch_size', type=int, default=10, help='test batch size')
parser.add_argument('--val_batch_size', type=int, default=10, help='val batch size')
parser.add_argument('--niter', type=int, default=1000, help='number of epochs to train for')
parser.add_argument('--lr', type=float, default=0.01, help='learning rate')
parser.add_argument('--verbal', type=bool, default=True, help='print training info or not')
parser.add_argument('--manualSeed', type=int, help='manual seed')
parser.add_argument('--n_classes', type=int, default=10, help='number of classes')
parser.add_argument('--test_data', default="pairwise/github_java_sort_function_pkl_train_test_val__test.txt", help='test program data')
parser.add_argument('--model_path', default="model/pairwise_java_sort_function_decomposable", help='path to save the model')
parser.add_argument('--n_hidden', type=int, default=50, help='number of hidden layers')
parser.add_argument('--training', action="store_true",help='is training')
parser.add_argument('--testing', action="store_true",help='is testing')
parser.add_argument('--training_percentage', type=float, default=1.0 ,help='percentage of data use for training')
parser.add_argument('--log_path', default="" ,help='log path for tensorboard')
parser.add_argument('--feature_size', type=int, default=100, help='size of convolutional features')
parser.add_argument('--batch_type', type=str, default="padding", help='batching type')
parser.add_argument('--embeddings_directory', default="embedding/fast_pretrained_vectors.pkl", help='pretrained embeddings url, there are 2 objects in this file, the first object is the embedding matrix, the other is the lookup dictionary')
parser.add_argument('--cuda', default="0",type=str, help='enables cuda')

opt = parser.parse_args()

print(opt)
os.environ['CUDA_VISIBLE_DEVICES'] = opt.cuda

if not os.path.isdir("cached"):
    os.mkdir("cached")


def convert_labels_to_one_hot(labels):
    labels_onehot = []
    for label in labels:      
        if label == 1: 
            labels_onehot.append([0.0,1.0])     
        if label == 0:
            labels_onehot.append([1.0,0.0])
    return labels_onehot


def generate_attention_score(attention_score, attention_score_scaled, node_ids, node_types, pb_path):
    print("Generating attention score.......")
    attention_file_path_raw_with_node_type = os.path.join(pb_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "raw_attention_with_node_type_and_subtree_size.csv")
    attention_file_path_raw_without_node_type = os.path.join(pb_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "raw_attention_without_node_type.csv")
    attention_file_path_all_1 = os.path.join(pb_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "attention_all_1.csv")
    attention_file_path_scaled_with_node_type = os.path.join(pb_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "scaled_attention_with_node_type_and_subtree_size.csv")
    attention_file_path_scaled_without_node_type = os.path.join(pb_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "scaled_attention_without_node_type.csv")

    attention_file_path_only_node_type = os.path.join(pb_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "only_node_type.csv")

    node_type_map = {}
    for i, node_id in enumerate(node_ids):
        type_of_node = node_types[i]
        if type_of_node not in node_type_map:
            node_type_map[type_of_node] = attention_score[i]
        else:
            node_type_map[type_of_node] += attention_score[i]

    node_type_weights = node_type_map.values()
    scaled_node_type_weights = scale_attention_score_by_group(list(node_type_weights))


    with open(attention_file_path_raw_with_node_type,"w") as f:
        for i, score in enumerate(attention_score):
            # subtree_ids = generate_subtree_ids(pb_path, node_ids[i])
            # line = str(node_ids[i]) + "," + str(node_types[i]) + "," + str(len(subtree_ids)) + "," + str(score)
            line = str(node_ids[i]) + "," + str(node_types[i]) + "," + str(score)
            f.write("%s\n" % line)

    with open(attention_file_path_raw_without_node_type,"w") as f1:
        for i, score in enumerate(attention_score):
            line = str(node_ids[i]) + "," + str(score)
            f1.write("%s\n" % line)

    with open(attention_file_path_all_1,"w") as f1:
        for i, score in enumerate(attention_score):
            line = str(node_ids[i]) + "," + str(1)
            f1.write("%s\n" % line)

    with open(attention_file_path_scaled_with_node_type,"w") as f2:
        for i, score in enumerate(attention_score_scaled):
            # subtree_ids = generate_subtree_ids(pb_path, node_ids[i])
            # line = str(node_ids[i]) + "," + str(node_types[i]) + "," + str(len(subtree_ids)) + "," + str(score)
            line = str(node_ids[i]) + "," + str(node_types[i]) + "," + str(score)
            f2.write("%s\n" % line)

    with open(attention_file_path_scaled_without_node_type,"w") as f3:
        for i, score in enumerate(attention_score_scaled):
            line = str(node_ids[i]) + "," + str(score)
            f3.write("%s\n" % line)

    with open(attention_file_path_only_node_type,"w") as f4:
        for i, node_type in enumerate(node_type_map.keys()):
            line = str(node_type) + "," + str(scaled_node_type_weights[i])
            f4.write("%s\n" % line)

def predict(test_left_trees, test_right_trees, test_labels, left_nodes_node, left_children_node, embeddings, right_nodes_node, right_children_node, labels_node, embedding_lookup, opt):

    for batch_left_trees, batch_right_trees, batch_labels in sampling.batch_random_samples_2_sides(test_left_trees, test_right_trees, test_labels, embeddings, embedding_lookup, opt.train_batch_size, opt.batch_type):

        if opt.batch_type == "original":
            left_nodes, left_children = batch_left_trees
            right_nodes, right_children = batch_right_trees
        else:
            left_nodes, left_children, _ = batch_left_trees
            right_nodes, right_children, _ = batch_right_trees
        
        labels_one_hot = convert_labels_to_one_hot(batch_labels)
            
        output, left_score, right_score = sess.run(
            [out_node],
            feed_dict={
                left_nodes_node: left_nodes,
                left_children_node: left_children,
                right_nodes_node: right_nodes,
                right_children_node: right_children,
                labels_node: labels_one_hot
            }
        )
    
        

def main():

    
    print("Loading embeddings....")
    with open(opt.embeddings_directory, 'rb') as fh:
        embeddings, embed_lookup = pickle.load(fh,encoding='latin1')
    

    
    logdir = opt.model_path
    epochs = opt.niter
    node_embedding_size = len(embeddings[0])


    n_classess = 2

    num_feats = len(embeddings[0])

    initializer = tf.contrib.layers.xavier_initializer()
    weights = {
        "w_t" : tf.Variable(initializer([node_embedding_size, opt.feature_size]), name="w_t"),
        "w_l" : tf.Variable(initializer([node_embedding_size, opt.feature_size]), name="w_l"),
        "w_r" : tf.Variable(initializer([node_embedding_size, opt.feature_size]), name="w_r"),
        "w_attention" : tf.Variable(initializer([opt.feature_size,1]), name="w_attention")
    }


    biases = {
        "b_conv": tf.Variable(initializer([opt.feature_size,]), name="b_conv"),
    }

    left_nodes_node, left_children_node, right_nodes_node, right_children_node, hidden_node, left_score_node, right_score_node = network.init_net_for_siamese(
        num_feats,
        opt.feature_size,
        weights, 
        biases,
        opt.aggregation,
        opt.distributed_function
    )

    out_node = network.out_layer(hidden_node)

    labels_node, loss_node = network.loss_layer(hidden_node, n_classess)

    optimizer = tf.train.AdamOptimizer(LEARN_RATE)
    train_step = optimizer.minimize(loss_node)

    sess = tf.Session()

    # sess = tf.Session()
    sess.run(tf.global_variables_initializer())

    with tf.name_scope('saver'):
        saver = tf.train.Saver()
        ckpt = tf.train.get_checkpoint_state(logdir)
        if ckpt and ckpt.model_checkpoint_path:
            print("Continue training with old model")
            saver.restore(sess, ckpt.model_checkpoint_path)
            for i, var in enumerate(saver._var_list):
                print('Var {}: {}'.format(i, var))
        # else:
        #     raise 'Checkpoint not found.'

    checkfile = os.path.join(logdir, 'cnn_tree.ckpt')
    steps = 0   

    print("Begin computing accuracy....")

    test_files = "pairwise/github_java_sort_function_pkl_train_test_val__test.txt"

    with open(test_file, "r") as f:
        data = f.readlines()
        for line in data:
            line = line.replace("\n","")


    test_dataloader = CrossLanguageProgramDataForLiveTest(file, 1,opt.n_classes)
    test_left_trees = test_dataloader.left_trees
    test_right_trees = test_dataloader.right_trees
    test_labels = test_dataloader.labels



if __name__ == "__main__":
    main()