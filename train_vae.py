"""Train the cnn model as  described in Lili Mou et al. (2015) 
https://arxiv.org/pdf/1409.5718.pdf"""

import os
import logging
import pickle
import tensorflow as tf
import numpy as np
import network as network
import sampling as sampling
import sys
import random
from parameters import LEARN_RATE, EPOCHS, CHECKPOINT_EVERY, BATCH_SIZE
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score

import itertools
import numpy as np
import matplotlib.pyplot as plt

os.environ['CUDA_VISIBLE_DEVICES'] = "0"

# def extract_vector_representation(vectors):
    

def train_model(logdir, infile, embedfile, training="True", testing="False"):
    """Train a classifier to label ASTs"""

    epochs = 100
    print("Loading trees...")
    print("Training = " + training)
    print("testing = " + testing)
    with open(infile, 'rb') as fh:
        trees, test_trees, labels = pickle.load(fh)

        random.shuffle(trees)
        
    print("Loading embeddings....")
    with open(embedfile, 'rb') as fh:
        embeddings, embed_lookup = pickle.load(fh)
        print("Len embeddings : " + str(len(embeddings[0])))
        num_feats = len(embeddings[0])

    # build the inputs and outputs of the network
    nodes_node, children_node, loss_node, pooling_node, x_reconstructed = network.init_vae_net(30, 100)

    optimizer = tf.train.AdamOptimizer(LEARN_RATE)
    train_step = optimizer.minimize(loss_node)


    ### init the graph
    sess = tf.Session()#config=tf.ConfigProto(device_count={'GPU':0}))
    sess.run(tf.global_variables_initializer())

    with tf.name_scope('saver'):
        saver = tf.train.Saver()
        ckpt = tf.train.get_checkpoint_state(logdir)
        if ckpt and ckpt.model_checkpoint_path:
            print("Continue training with old model")
            saver.restore(sess, ckpt.model_checkpoint_path)

    checkfile = os.path.join(logdir, 'cnn_tree.ckpt')

    
    if training == "True":
        print("Begin training..........")
        num_batches = len(trees) // BATCH_SIZE + (1 if len(trees) % BATCH_SIZE != 0 else 0)
        for epoch in range(1, epochs+1):
            for i, batch in enumerate(sampling.batch_samples(
                sampling.gen_samples(trees, labels, embeddings, embed_lookup), BATCH_SIZE
            )):
                nodes, children, _, _ = batch
                step = (epoch - 1) * num_batches + i * BATCH_SIZE

               
                if not nodes:
                    continue # don't try to train on an empty batch
                # print(batch_labels)
                _, err, pooling_vector, x_reconstructed_vector = sess.run(
                    [train_step, loss_node, pooling_node, x_reconstructed],
                    feed_dict={
                        nodes_node: nodes,
                        children_node: children
                    }
                )
                print("---------------------------------------------------------")

                # print(pooling_vector)
                # print("###########################")
                print(x_reconstructed_vector)
                print('Epoch:', epoch, 'Step:', step, 'Loss:', err)

                if step % CHECKPOINT_EVERY == 0:
                    # save state so we can resume later
                    saver.save(sess, os.path.join(checkfile), step)
                    print('Checkpoint saved, epoch:' + str(epoch) + ', step: ' + str(step) + ', loss: ' + str(err) + '.')

        saver.save(sess, os.path.join(checkfile), step)


    if testing == "True":
        for batch in sampling.batch_samples(
            sampling.gen_samples(test_trees, labels, embeddings, embed_lookup), 1
        ):
            nodes, children, _, _ = batch
            x_reconstructed_vector = sess.run([x_reconstructed],
                feed_dict={
                    nodes_node: nodes,
                    children_node: children,
                }
            )
            print("---------------------------------------")
            print(x_reconstructed_vector)
         

def main():
    # logdir = "bi-tbcnn/bi-tbcnn/logs/20_classes_pku_no_dependency"
    logdir = sys.argv[1]
    inputs = sys.argv[2]
    embeddings = sys.argv[3]
    training = sys.argv[4]
    testing = sys.argv[5]

    train_model(logdir,inputs,embeddings, training, testing) 

if __name__ == "__main__":
    main()