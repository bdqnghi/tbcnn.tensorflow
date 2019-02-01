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


def scale_attention(matrix_aggregation):
    attention_score_sorted = sorted(matrix_aggregation.items(), key=operator.itemgetter(1))
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

    return attention_score_scaled_map
        
def test_model(test_dataloader, embeddings, embedding_lookup, opt):

    logdir = opt.model_path
    epochs = opt.niter
    node_embedding_size = len(embeddings[0])

    test_left_trees = test_dataloader.left_trees
    test_right_trees = test_dataloader.right_trees
    test_labels = test_dataloader.labels
    test_left_node_ids_list = test_dataloader.left_node_ids_list
    test_right_node_ids_list = test_dataloader.right_node_ids_list

    print(test_left_node_ids_list)
    print("Num id left : " + str(len(test_left_node_ids_list[0])))
    print("Num id right : " + str(len(test_right_node_ids_list[0])))
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

    left_nodes_node, left_children_node, right_nodes_node, right_children_node, logits_node, left_mask_nodes, right_mask_nodes, attention_matrix_nodes = network.init_net_for_siamese_2(
        num_feats,
        opt.feature_size,
        weights, 
        biases,
    )

    # left_nodes_node, left_children_node, right_nodes_node, right_children_node, logits_node, left_mask_nodes, right_mask_nodes, attention_matrix_nodes = network.init_net_for_siamese_3(
    #     num_feats,
    #     opt.feature_size
    # )

    out_node = network.out_layer(logits_node)

    labels_node, loss_node = network.loss_layer(logits_node, n_classess)

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

    correct_labels = []
    predictions = []

    for batch_left_trees, batch_right_trees, batch_labels in sampling.batch_random_samples_2_sides(test_left_trees, test_right_trees, test_labels, embeddings, embedding_lookup, opt.train_batch_size,opt.batch_type):

        left_nodes, left_children, left_masks = batch_left_trees
        right_nodes, right_children, right_masks = batch_right_trees
        
        labels_one_hot = convert_labels_to_one_hot(batch_labels)
            
        matching_matrices, output = sess.run(
            [attention_matrix_nodes, out_node],
            feed_dict={
                left_nodes_node: left_nodes,
                left_children_node: left_children,
                right_nodes_node: right_nodes,
                right_children_node: right_children,
                labels_node: labels_one_hot,
                left_mask_nodes: left_masks,
                right_mask_nodes: right_masks,
            }
        )
        matrix = matching_matrices[0]
     
        if len(test_left_node_ids_list[0]) < len(test_right_node_ids_list[0]):
            matrix = matrix[:len(test_left_node_ids_list[0]),...]
        else:
            matrix = matrix[...,:len(test_right_node_ids_list[0])]


        matrix_pd = pd.DataFrame(data=matrix,index=test_left_node_ids_list[0], columns=test_right_node_ids_list[0])
        matrix_pd.to_csv("live_test/github_pairwise_java/sort/1_matrix.csv", sep=",")
        
        left_matrix_aggregate_idx = matrix_pd.idxmax(axis=1)
        left_matrix_aggregate_idx.to_csv("live_test/github_pairwise_java/sort/left_aggregate_attention_idx.csv", sep=",")

        right_matrix_aggregate_idx = matrix_pd.idxmax(axis=0)
        right_matrix_aggregate_idx.to_csv("live_test/github_pairwise_java/sort/right_aggregate_attention_idx.csv", sep=",")
     

        left_matrix_aggregate = matrix_pd.max(axis=1)
        left_matrix_aggregate.to_csv("live_test/github_pairwise_java/sort/left_aggregate_attention.csv", sep=",")
        left_matrix_max_dict = left_matrix_aggregate.to_dict()


        right_matrix_aggregate = matrix_pd.max(axis=0)
        right_matrix_aggregate.to_csv("live_test/github_pairwise_java/sort/right_aggregate_attention.csv", sep=",")
        right_matrix_max_dict = right_matrix_aggregate.to_dict()
        

        left_scaled_attention_map = scale_attention(left_matrix_max_dict)
        right_scaled_attention_map = scale_attention(right_matrix_max_dict)

        left_attention_path = "live_test/github_pairwise_java/sort/left_attention_scaled.csv"
        left_pb_path = "github_java_sort_function_pb/5/3.java.pb"
        left_normal_html_path = "live_test/github_pairwise_java/sort/left_normal.html"
        with open("live_test/github_pairwise_java/sort/left_attention_scaled.csv","w") as f1:
            for key, score in enumerate(left_scaled_attention_map):
                line = str(key) + "," + str(score)
                f1.write("%s\n" % line)

        normal_cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H 0 -t -x " + left_attention_path + " " + left_pb_path  + " > " + left_normal_html_path
        print(normal_cmd)
        os.system(normal_cmd)


        
        right_attention_path = "live_test/github_pairwise_java/sort/right_attention_scaled.csv"
        right_pb_path = "github_java_sort_function_pb/5/105.java.pb"
        right_normal_html_path = "live_test/github_pairwise_java/sort/right_normal.html"
        with open("live_test/github_pairwise_java/sort/right_attention_scaled.csv","w") as f1:
            for key, score in enumerate(right_scaled_attention_map):
                line = str(key) + "," + str(score)
                f1.write("%s\n" % line)

        normal_cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H 0 -t -x " + right_attention_path + " " + right_pb_path  + " > " + right_normal_html_path
        print(normal_cmd)
        os.system(normal_cmd)




        print(output)
        print(labels_one_hot)
        correct = np.argmax(labels_one_hot, axis=1)
        predicted = np.argmax(output, axis=1)

        correct_labels.extend(correct)
        predictions.extend(predicted)

    print('Accuracy:', accuracy_score(correct_labels, predictions))
    print(classification_report(correct_labels, predictions))
    print(confusion_matrix(correct_labels, predictions))


def main():

    file = "live_test/github_pairwise_java/sort/1.txt"
    print("Loading embeddings....")
    with open(opt.embeddings_directory, 'rb') as fh:
        embeddings, embed_lookup = pickle.load(fh,encoding='latin1')
   
    test_dataloader = CrossLanguageProgramDataForLiveTest(file, 1,opt.n_classes)
  
    test_model(test_dataloader,  embeddings, embed_lookup, opt) 

if __name__ == "__main__":
    main()