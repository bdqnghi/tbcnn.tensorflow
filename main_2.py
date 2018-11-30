"""Train the cnn model as  described in Lili Mou et al. (2015) 
https://arxiv.org/pdf/1409.5718.pdf"""
from tensorflow import saved_model
from tensorflow.python.saved_model import tag_constants
from tensorflow.python.saved_model.signature_def_utils_impl import predict_signature_def
import os
import logging
import pickle
import tensorflow as tf
import numpy as np
import network_2 as network
import sampling as sampling
import sys
import random
from parameters import LEARN_RATE, EPOCHS, CHECKPOINT_EVERY, BATCH_SIZE
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
from data_loader import load_program_data
from data_loader import MonoLanguageProgramData
import argparse
import random
import shutil
from utils import scale_attention_score

os.environ['CUDA_VISIBLE_DEVICES'] = "0"

parser = argparse.ArgumentParser()
parser.add_argument('--train_batch_size', type=int, default=15, help='train batch size')
parser.add_argument('--test_batch_size', type=int, default=10, help='test batch size')
parser.add_argument('--val_batch_size', type=int, default=10, help='val batch size')
parser.add_argument('--niter', type=int, default=300, help='number of epochs to train for')
parser.add_argument('--lr', type=float, default=0.01, help='learning rate')
parser.add_argument('--cuda', action='store_true', help='enables cuda')
parser.add_argument('--verbal', type=bool, default=True, help='print training info or not')
parser.add_argument('--manualSeed', type=int, help='manual seed')
parser.add_argument('--n_classes', type=int, default=3, help='manual seed')
parser.add_argument('--train_directory', default="ProgramData_pkl_train_test_val/train", help='train program data')
parser.add_argument('--test_directory', default="ProgramData_pkl_train_test_val/test", help='test program data')
parser.add_argument('--val_directory', default="ProgramData_pkl_train_test_val/val", help='validation program data')
parser.add_argument('--model_path', default="model/3_pku", help='path to save the model')
parser.add_argument('--n_hidden', type=int, default=50, help='number of hidden layers')
parser.add_argument('--training', action="store_true",help='is training')
parser.add_argument('--testing', action="store_true",help='is testing')
parser.add_argument('--training_percentage', type=float, default=1.0 ,help='percentage of data use for training')
parser.add_argument('--log_path', default="" ,help='log path for tensorboard')
parser.add_argument('--epoch', type=int, default=0, help='epoch to test')
parser.add_argument('--aggregation', type=int, default=0, help='0 for max pooling, 1 for global attention')
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
# def train_model(opt):
def train_model(train_trees, test_trees, val_trees, labels, embeddings, embedding_lookup, opt):
    """Train a classifier to label ASTs"""
   
    logdir = opt.model_path
    batch_size = opt.train_batch_size
    epochs = opt.niter
    num_feats = len(embeddings[0])
    
    random.shuffle(train_trees)
    random.shuffle(val_trees)
    random.shuffle(test_trees)
    

    # meta_file = os.path.join(logdir, "cnn_tree.ckpt.meta")
    # if os.path.exists(meta_file):
    #     saver = tf.train.import_meta_graph(meta_file)
    #     saver.restore(sess,tf.train.latest_checkpoint('./'))

    #     graph = tf.get_default_graph()
    #     nodes_node = graph.get_tensor_by_name("tree:0")
    #     children_node = graph.get_tensor_by_name("children:0")
    #     hidden_node = graph.get_tensor_by_name("hidden_node:0")
    #     attention_score_node = graph.get_tensor_by_name("hidden_node:0")

    nodes_node, children_node, hidden_node, attention_score_node = network.init_net(
        num_feats,
        len(labels),
        opt.aggregation
    )
    hidden_node = tf.identity(hidden_node, name="hidden_node")

    out_node = network.out_layer(hidden_node)
    labels_node, loss_node = network.loss_layer(hidden_node, len(labels))

    optimizer = tf.train.AdamOptimizer(LEARN_RATE)
    train_step = optimizer.minimize(loss_node)
    
     ### init the graph
    sess = tf.Session()#config=tf.ConfigProto(device_count={'GPU':0}))
    sess.run(tf.global_variables_initializer())

    # Initialize the variables (i.e. assign their default value)
    init = tf.global_variables_initializer()

     with tf.name_scope('saver'):
        saver = tf.train.Saver()
        ckpt = tf.train.get_checkpoint_state(logdir)
        if ckpt and ckpt.model_checkpoint_path:
            print("Continue training with old model")
            saver.restore(sess, ckpt.model_checkpoint_path)
            for i, var in enumerate(saver._var_list):
                print('Var {}: {}'.format(i, var))

    checkfile = os.path.join(logdir, 'cnn_tree.ckpt')

    if opt.training:
        print("Begin training..........")
        num_batches = len(train_trees) // batch_size + (1 if len(train_trees) % batch_size != 0 else 0)
        for epoch in range(1, epochs+1):
            for i, batch in enumerate(sampling.batch_samples(
                sampling.gen_samples(train_trees, labels, embeddings, embedding_lookup), batch_size
            )):
                nodes, children, batch_labels = batch
                # print(len(batch_labels))
                # print(len(batch_labels[0]))
                step = (epoch - 1) * num_batches + i * BATCH_SIZE

                if not nodes:
                    continue # don't try to train on an empty batch
                # print(batch_labels)
                _, err, out = sess.run(
                    [train_step, loss_node, out_node],
                    feed_dict={
                        nodes_node: nodes,
                        children_node: children,
                        labels_node: batch_labels
                    }
                )
             
                print('Epoch:', epoch, 'Step:', step, 'Loss:', err, 'Max nodes:', len(nodes[0]))
                # print(attention_score[0])
                # print(len(attention_score[0]))
                # print(pooling_output.shape)

                if step % CHECKPOINT_EVERY == 0:
                    # save state so we can resume later
                    saver.save(sess, checkfile)
                    # shutil.rmtree(savedmodel_path)
                 
                    print('Checkpoint saved, epoch:' + str(epoch) + ', step: ' + str(step) + ', loss: ' + str(err) + '.')

            correct_labels = []
            predictions = []
            for batch in sampling.batch_samples(
                sampling.gen_samples(val_trees, labels, embeddings, embedding_lookup), 1
            ):
                nodes, children, batch_labels = batch
                output = sess.run([out_node],
                    feed_dict={
                        nodes_node: nodes,
                        children_node: children,
                    }
                )
                # print(output)
                correct_labels.append(np.argmax(batch_labels))
                predictions.append(np.argmax(output))

            target_names = list(labels)
            print('Accuracy:', accuracy_score(correct_labels, predictions))
            print(classification_report(correct_labels, predictions, target_names=target_names))
            print(confusion_matrix(correct_labels, predictions))

        print("Finish all iters, storring the whole model..........")
        saver.save(sess, checkfile)
        # builder = saved_model.builder.SavedModelBuilder(savedmodel_path)
        # signature = predict_signature_def(inputs={'nodes': nodes_node, "children": children_node},
        #                                   outputs={'labels': labels_node})
        # # using custom tag instead of: tags=[tag_constants.SERVING]
        # builder.add_meta_graph_and_variables(sess=sess,
        #                                      tags=[tag_constants.TRAINING],
        #                                      signature_def_map={'predict': signature})
        # builder.save()
        # saved_model.simple_save(sess,savedmodel_path,inputs={'nodes': nodes_node, "children": children_node},
                                          # outputs={'labels': labels_node})


# def test_model(trees, labels, embeddings, embedding_lookup, opt):
    
#     logdir = opt.model_path
#     batch_size = opt.train_batch_size
#     epochs = opt.niter
#     num_feats = len(embeddings[0])

#     random.shuffle(trees)
#     # build the inputs and outputs of the network
#     nodes_node, children_node, hidden_node, pooling = network.init_net(
#         num_feats,
#         len(labels),
#         opt.aggregation
#     )

#     out_node = network.out_layer(hidden_node)
#     labels_node, loss_node = network.loss_layer(hidden_node, len(labels))

#     optimizer = tf.train.AdamOptimizer(LEARN_RATE)
#     train_step = optimizer.minimize(loss_node)

#     sess = tf.Session()#config=tf.ConfigProto(device_count={'GPU':0}))
#     sess.run(tf.global_variables_initializer())
#     with tf.name_scope('saver'):
#         saver = tf.train.Saver()
#         ckpt = tf.train.get_checkpoint_state(logdir)
#         if ckpt and ckpt.model_checkpoint_path:
#             print("Continue training with old model")
#             saver.restore(sess, ckpt.model_checkpoint_path)

#     checkfile = os.path.join(logdir, 'cnn_tree.ckpt')

#     correct_labels = []
#     predictions = []
#     print('Computing training accuracy...')
#     for batch in sampling.batch_samples(
#         sampling.gen_samples(trees, labels, embeddings, embedding_lookup), 1
#     ):
#         nodes, children, batch_labels = batch
#         output = sess.run([out_node],
#             feed_dict={
#                 nodes_node: nodes,
#                 children_node: children,
#             }
#         )
#         # print(output)
#         correct_labels.append(np.argmax(batch_labels))
#         predictions.append(np.argmax(output))

#     target_names = list(labels)
#     print('Accuracy:', accuracy_score(correct_labels, predictions))
#     print(classification_report(correct_labels, predictions, target_names=target_names))
#     print(confusion_matrix(correct_labels, predictions))


def main(opt):

    print("Loading embeddings....")
    with open(opt.embeddings_directory, 'rb') as fh:
        embeddings, embed_lookup = pickle.load(fh,encoding='latin1')
       
    # if opt.training:
    labels = [str(i) for i in range(1, opt.n_classes+1)]

    print("Loading train trees...")
    train_data_loader = MonoLanguageProgramData(opt.train_directory, 0, opt.n_classes)
    train_trees, _ = train_data_loader.trees, train_data_loader.labels

    val_data_loader = MonoLanguageProgramData(opt.val_directory, 2, opt.n_classes)
    val_trees, _ = val_data_loader.trees, val_data_loader.labels

    test_data_loader = MonoLanguageProgramData(opt.test_directory, 1, opt.n_classes)
    test_trees, _ = test_data_loader.trees, test_data_loader.labels
    print("All training trees : " + str(len(train_trees)))
    train_model(train_trees, test_trees, val_trees,  labels, embeddings, embed_lookup , opt) 

    # if opt.testing:

    #     print("Loading test trees...")
    #     test_data_loader = MonoLanguageProgramData(opt.test_directory, 1, opt.n_classes)
    #     test_trees, labels = test_data_loader.trees, test_data_loader.labels
    #     print("All testing trees : " + str(len(test_trees)))
    #     test_model(test_trees, labels, embeddings, embed_lookup , opt) 

if __name__ == "__main__":
    main(opt)