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
from utils import scale_attention_score
from data_loader import load_single_pair_for_live_test
import operator
from tqdm import trange
from tqdm import *
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
parser.add_argument('--test_data', default="pairwise/github_java_sort_function_pkl_train_test_val__val.txt", help='test program data')
parser.add_argument('--model_path', default="model//pairwise_java_sort_function_attention_sum_softmax", help='path to save the model')
parser.add_argument('--n_hidden', type=int, default=50, help='number of hidden layers')
parser.add_argument('--training', action="store_true",help='is training')
parser.add_argument('--testing', action="store_true",help='is testing')
parser.add_argument('--training_percentage', type=float, default=1.0 ,help='percentage of data use for training')
parser.add_argument('--log_path', default="" ,help='log path for tensorboard')
parser.add_argument('--feature_size', type=int, default=100, help='size of convolutional features')
parser.add_argument('--aggregation', type=int, default=1, choices=range(0,4), help='0 for max pooling, 1 for attention with sum pooling, 2 for attention with max pooling, 3 for attention with average pooling')
parser.add_argument('--distributed_function', type=int, default=0, choices=range(0,2), help='0 for softmax, 1 for sigmoid')
parser.add_argument('--batch_type', type=str, default="original", help='batching type')
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

def scale_attention(attention_score, max_node, node_ids):
    # max_node = len(nodes[0])
    node_ids = node_ids[0]

    attention_score = np.reshape(attention_score, (max_node))

    attention_score_map = {}
    for i, score in enumerate(attention_score):
        key = str(node_ids[i])
        attention_score_map[key] = float(score)

    
    attention_score_sorted = sorted(attention_score_map.items(), key=operator.itemgetter(1))
    attention_score_sorted.reverse() 

    node_ids = []
    attention_score = []
    for element in attention_score_sorted:
        node_ids.append(element[0])
        attention_score.append(element[1])

    attention_score_scaled = scale_attention_score_by_group(attention_score)

    attention_score_scaled_map = {}
    for i, score in enumerate(attention_score_scaled):
        key = str(node_ids[i])
        attention_score_scaled_map[key] = float(score)

    score_str = []
    for node_id, score in attention_score_scaled_map.items():
        line = str(node_id) + ":" + str(score)
        score_str.append(line)

    # score_str = []
    # for i, score in enumerate(attention_score):
    #     print("ASDSDOPIhSPDSPDOIPHDIOHIOSHIODHSDSd")
    #     line = str(node_ids[i]) + ":" + str(score)
    #     print(line)
    #     score_str.append(line)

    return ",".join(score_str)


def generate_pb(src_path):
    # path_splits = src_path.split("/")
  
  
    pb_path = os.path.join(src_path.replace(".java",".java.pb"))
    if not os.path.exists(pb_path):
        cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -p " + src_path + " " + pb_path
        os.system(cmd)
    return pb_path


# def generate_diff_visualization()
def predict(sess, index, left_path, right_path, pairs, left_node_ids_list, right_node_ids_list, out_node, left_score_node, right_score_node, left_nodes_node, left_children_node, right_nodes_node, right_children_node, labels_node, embeddings, embedding_lookup, opt):
    
    test_left_trees = []
    test_right_trees = []
    test_labels = []
    test_left_trees.append(pairs[0][0])
    test_right_trees.append(pairs[0][1])
    test_labels.append(pairs[0][2])


    for batch_left_trees, batch_right_trees, batch_labels in sampling.batch_random_samples_2_sides(test_left_trees, test_right_trees, test_labels, embeddings, embedding_lookup, opt.train_batch_size, opt.batch_type):

        if opt.batch_type == "original":
            left_nodes, left_children = batch_left_trees
            right_nodes, right_children = batch_right_trees
        else:
            left_nodes, left_children, _ = batch_left_trees
            right_nodes, right_children, _ = batch_right_trees
        
        labels_one_hot = convert_labels_to_one_hot(batch_labels)
        
        output, left_attention_score, right_attention_score = sess.run(
            [out_node, left_score_node, right_score_node],
            feed_dict={
                left_nodes_node: left_nodes,
                left_children_node: left_children,
                right_nodes_node: right_nodes,
                right_children_node: right_children,
                labels_node: labels_one_hot
            }
        )

        left_scaled_attention_score = scale_attention(left_attention_score, len(left_nodes[0]), left_node_ids_list)

        right_scaled_attention_score = scale_attention(right_attention_score, len(right_nodes[0]), right_node_ids_list)

        left_pb_path = left_path.replace("github_java_sort_function_pkl_train_test_val","github_java_sort_function_pb").replace(".pkl","").replace("/val","")
        right_pb_path = right_path.replace("github_java_sort_function_pkl_train_test_val","github_java_sort_function_pb").replace(".pkl","").replace("/val","")

        left_java_path = left_path.replace("github_java_sort_function_pkl_train_test_val","github_java_sort_function").replace(".pb.pkl","").replace("/val","")
        right_java_path = right_path.replace("github_java_sort_function_pkl_train_test_val","github_java_sort_function").replace(".pb.pkl","").replace("/val","")

        # print(cmd)
       
        temp_left_java_path = left_java_path.split("/")[-1]
        temp_right_java_path = right_java_path.split("/")[-1]

        temp_left_pb_path = left_pb_path.split("/")[-1]
        temp_right_pb_path = right_pb_path.split("/")[-1]

        # print(left_pb_path)
        # print(right_pb_path)
        from shutil import copyfile

        copyfile(left_java_path, temp_left_java_path)
        copyfile(right_java_path, temp_right_java_path)

        generate_pb(temp_left_java_path)
        generate_pb(temp_right_java_path)

        save_file = "github_java_pairwise_visualization/" + "pair_" + str(index) + ".html"
        cmd = "docker run -v $(pwd):/e yijun/fast -H 0 -a 0 -D " + temp_left_pb_path + " " + temp_right_pb_path + " -x " + "'" + left_scaled_attention_score + "'" + " -y " + "'" + right_scaled_attention_score + "'" + " > " + save_file
        # cmd = "docker run -v $(pwd):/e yijun/fast -D -H -x " + "'" + left_scaled_attention_score + "'" + " -y " + "'" + right_scaled_attention_score + "'" + " -p " + temp_left_path + " " + temp_right_path
        print(cmd)
        os.system(cmd)
        # gumtree_cmd = "docker run -v $(pwd):/e --entrypoint gumtree -it yijun/fast diff " + temp_left_path + " " + temp_right_path
        # print(gumtree_cmd)

        # os.system(gumtree_cmd)

        if os.path.exists(temp_left_java_path):
            os.remove(temp_left_java_path)

        if os.path.exists(temp_right_java_path):
            os.remove(temp_right_java_path)

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

    test_file = opt.test_data

    # with open(test_file, "r") as f:
    #     data = f.readlines()
    #     for line in data:
    #         line = line.replace("\n","")


    # test_dataloader = CrossLanguageProgramDataForLiveTest(test_file, 1,opt.n_classes)
    # test_left_trees = test_dataloader.left_trees
    # test_right_trees = test_dataloader.right_trees
    # test_labels = test_dataloader.labels
    all_pairs_index = []
    with open(opt.test_data,"r") as f:
        data = f.readlines()
        for line in data:
            print(line)
            all_pairs_index.append(line.replace("\n",""))
  
    for i, pair in tqdm(enumerate(all_pairs_index)):
        splits = pair.split(",")
        left_path = splits[0]
        right_path = splits[1]
        label = splits[2]

        pairs, left_node_ids_list, right_node_ids_list = load_single_pair_for_live_test(left_path, right_path, label)
        predict(sess, i, left_path, right_path, pairs, left_node_ids_list, right_node_ids_list, out_node, left_score_node, right_score_node, left_nodes_node, left_children_node, right_nodes_node, right_children_node, labels_node, embeddings, embed_lookup, opt)

if __name__ == "__main__":
    main()