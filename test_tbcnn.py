import argparse
import random
import pickle
import tensorflow.compat.v1 as tf
from util.data.data_loader.base_data_loader import BaseDataLoader
from util.threaded_iterator import ThreadedIterator
import os
import sys
import re
import copy
import time
import argument_parser
import copy
import numpy as np
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score, f1_score, precision_score, recall_score
from datetime import datetime
from keras_radam.training import RAdamOptimizer
import logging
from util.network.tbcnn import TBCNN
from util import util_functions
logging.basicConfig(filename='training.log',level=logging.DEBUG)
np.set_printoptions(threshold=sys.maxsize)
tf.compat.v1.disable_eager_execution()
tf.disable_v2_behavior()

def main(test_opt):

    test_opt.model_path = os.path.join(test_opt.model_path, util_functions.form_tbcnn_model_path(test_opt))
    checkfile = os.path.join(test_opt.model_path, 'cnn_tree.ckpt')
    ckpt = tf.train.get_checkpoint_state(test_opt.model_path)
    print("The model path : " + str(checkfile))
    if ckpt and ckpt.model_checkpoint_path:
        print("-------Continue training with old model-------- : " + str(checkfile))


    tbcnn_model = TBCNN(test_opt)
    tbcnn_model.feed_forward()
    
    test_data_loader = BaseDataLoader(test_opt.batch_size, test_opt.label_size, test_opt.tree_size_threshold_upper, test_opt.tree_size_threshold_lower, test_opt.test_path, False)

    saver = tf.train.Saver(save_relative_paths=True, max_to_keep=5)  
    init = tf.global_variables_initializer()

    try:
        os.remove("eval.txt")
    except Exception as e:
        print(e)

    with tf.Session() as sess:
        sess.run(init)
        if ckpt and ckpt.model_checkpoint_path:
            print("Continue training with old model")
            print("Checkpoint path : " + str(ckpt.model_checkpoint_path))
            saver.restore(sess, ckpt.model_checkpoint_path)
            for i, var in enumerate(saver._var_list):
                print('Var {}: {}'.format(i, var))

        correct_labels = []
        predictions = []
        test_batch_iterator = ThreadedIterator(test_data_loader.make_minibatch_iterator(), max_queue_size=test_opt.worker)
        for test_step, test_batch_data in enumerate(test_batch_iterator):
            print("***************")

            # print(test_batch_data["batch_size"])
            scores = sess.run(
                    [tbcnn_model.softmax],
                    feed_dict={
                        tbcnn_model.placeholders["node_type"]: test_batch_data["batch_node_type_id"],
                        tbcnn_model.placeholders["node_token"]:  test_batch_data["batch_node_sub_tokens_id"],
                        tbcnn_model.placeholders["children_index"]:  test_batch_data["batch_children_index"],
                        tbcnn_model.placeholders["children_node_type"]: test_batch_data["batch_children_node_type_id"],
                        tbcnn_model.placeholders["children_node_token"]: test_batch_data["batch_children_node_sub_tokens_id"],
                        tbcnn_model.placeholders["labels"]: test_batch_data["batch_labels_one_hot"],
                        tbcnn_model.placeholders["dropout_rate"]: 0.0
                    }
                )

            
            batch_correct_labels = list(np.argmax(test_batch_data["batch_labels_one_hot"],axis=1))
            batch_predictions = list(np.argmax(scores[0],axis=1))
            
            print(batch_correct_labels)
            print(batch_predictions)
            # with open("eval.txt", "a") as f:
            #     for i, correct_label in enumerate(correct_labels):
            #         prediction = predictions[i]
            #         line = f'{correct_label},{prediction}'
            #         f.write(line)
            #         f.write("\n")

            correct_labels.extend(np.argmax(test_batch_data["batch_labels_one_hot"],axis=1))
            predictions.extend(np.argmax(scores[0],axis=1))

        print(correct_labels)
        print(predictions)
        target_names = [str(i) for i in range(1,11)]
        precision = float(precision_score(correct_labels, predictions, average="micro"))
        recall = float(recall_score(correct_labels, predictions, average="micro"))
        f1 = float(f1_score(correct_labels, predictions, average="micro"))
        print(classification_report(correct_labels, predictions))

        print("Finished producing test results for model : ", str(test_opt.model_path))
        print('Precision:', recall)
        print('Recall:', recall)
        print('F1:', f1)
        # print(confusion_matrix(correct_labels, predictions))



if __name__ == "__main__":
    test_opt = argument_parser.parse_arguments()

    os.environ['CUDA_VISIBLE_DEVICES'] = test_opt.cuda

    main(test_opt)
   