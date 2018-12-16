# This file is just another version to test with 2 different AST tree on each side of the Bi-TBCNN
import os
import logging
import pickle
import tensorflow as tf
import numpy as np
import network as network
import sampling as sampling
from parameters import LEARN_RATE, EPOCHS, CHECKPOINT_EVERY, BATCH_SIZE, DROP_OUT
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
import random
import sys
import json
import argparse
from data_loader import CrossLanguageProgramData

parser = argparse.ArgumentParser()
parser.add_argument('--train_batch_size', type=int, default=10, help='train batch size')
parser.add_argument('--test_batch_size', type=int, default=10, help='test batch size')
parser.add_argument('--val_batch_size', type=int, default=10, help='val batch size')
parser.add_argument('--niter', type=int, default=300, help='number of epochs to train for')
parser.add_argument('--lr', type=float, default=0.01, help='learning rate')
parser.add_argument('--verbal', type=bool, default=True, help='print training info or not')
parser.add_argument('--manualSeed', type=int, help='manual seed')
parser.add_argument('--n_classes', type=int, default=3, help='manual seed')
parser.add_argument('--train_data', default="pairwise/github_java_sort_pkl_train_test_val__train.txt", help='train program data')
parser.add_argument('--test_data', default="pairwise/github_java_sort_pkl_train_test_val__test.txt", help='test program data')
parser.add_argument('--val_data', default="pairwise/github_java_sort_pkl_train_test_val__val.txt", help='validation program data')
parser.add_argument('--model_path', default="model/pairwise_java", help='path to save the model')
parser.add_argument('--n_hidden', type=int, default=50, help='number of hidden layers')
parser.add_argument('--training', action="store_true",help='is training')
parser.add_argument('--testing', action="store_true",help='is testing')
parser.add_argument('--training_percentage', type=float, default=1.0 ,help='percentage of data use for training')
parser.add_argument('--log_path', default="" ,help='log path for tensorboard')
parser.add_argument('--aggregation', type=int, default=2, choices=range(0,4), help='0 for max pooling, 1 for attention with sum pooling, 2 for attention with max pooling, 3 for attention with average pooling')
parser.add_argument('--embeddings_directory', default="embedding/fast_pretrained_vectors.pkl", help='pretrained embeddings url, there are 2 objects in this file, the first object is the embedding matrix, the other is the lookup dictionary')
parser.add_argument('--cuda', default="0",type=str, help='enables cuda')

opt = parser.parse_args()

os.environ['CUDA_VISIBLE_DEVICES'] = opt.cuda

if not os.path.isdir("cached"):
    os.mkdir("cached")

if opt.aggregation == 0:
    print("Using max pooling...........")
if opt.aggregation == 1:
    print("Using attention with sum pooling...........")
if opt.aggregation == 2:
    print("Using attention with max pooling...........")
if opt.aggregation == 3:
    print("Using attention with average pooling...........")


def convert_labels_to_one_hot(labels):
    labels_onehot = []
    for label in labels:      
        if label == 1: 
            labels_onehot.append([0.0,1.0])     
        if label == 0:
            labels_onehot.append([1.0,0.0])
    return labels_onehot



def train_model(train_dataloader, embeddings, embedding_lookup, opt):
    
    logdir = opt.model_path
    epochs = opt.niter

    train_left_trees = train_dataloader.left_trees
    train_right_trees = train_dataloader.right_trees
    train_labels = train_dataloader.labels

    # val_left_trees = val_dataloader.left_trees
    # val_right_trees = val_dataloader.right_trees
    # val_labels = val_dataloader.labels

    n_classess = 2

    num_feats = len(embeddings[0])


    left_nodes_node, left_children_node, left_aggregation_node, left_score_node = network.init_net_for_siamese(
        num_feats,
        opt.aggregation,
        opt.distributed_function
    )

    right_nodes_node, right_children_node, right_aggregation_node, right_score_node  = network.init_net_for_siamese(
        num_feats,
        opt.aggregation,
        opt.distributed_function
    )

    merge_node = tf.concat([left_aggregation_node, right_aggregation_node], -1)

    # hidden_node = network.hidden_layer(merge_node, 200, )
    hidden_node = network.hidden_layer(merge_node, 200, n_classess)

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
        # else:
        #     raise 'Checkpoint not found.'

    checkfile = os.path.join(logdir, 'cnn_tree.ckpt')
    steps = 0   

    print("Begin training....")

    # with tf.device(device):
    for epoch in range(1, epochs+1):
        print("----------------------------------------------------")
        for batch_left_trees, batch_right_trees, batch_labels in sampling.batch_random_samples_2_sides(train_left_trees, train_right_trees, train_labels, embeddings, embedding_lookup, opt.train_batch_size):
           
            left_nodes, left_children = batch_left_trees

            right_nodes, right_children = batch_right_trees
            # print(batch_labels)
            labels_one_hot = convert_labels_to_one_hot(batch_labels)
                
            _, err, out = sess.run(
                [train_step, loss_node, out_node],
                feed_dict={
                    left_nodes_node: left_nodes,
                    left_children_node: left_children,
                    right_nodes_node: right_nodes,
                    right_children_node: right_children,
                    labels_node: labels_one_hot
                }
            )

            # print "hidden : " + str(loss)
            print('Epoch:', epoch,'Steps:', steps,'Loss:', err)
         

            if steps % CHECKPOINT_EVERY == 0:
                # save state so we can resume later
                saver.save(sess, os.path.join(checkfile), steps)
                print('Checkpoint saved.')

    
            steps+=1
        steps = 0

def main():
        
   
    print("Loading embeddings....")
    with open(opt.embeddings_directory, 'rb') as fh:
        embeddings, embed_lookup = pickle.load(fh,encoding='latin1')
    
    train_data_loader = CrossLanguageProgramData(opt.train_data)
    # val_data_loader = CrossLanguageProgramData(opt.val_data)
 
  
    train_model(train_data_loader,  embeddings, embed_lookup, opt) 


if __name__ == "__main__":
    main()
