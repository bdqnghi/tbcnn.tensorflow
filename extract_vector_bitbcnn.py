import os
import logging
import pickle
import tensorflow as tf
import numpy as np
import network as network
import sampling as sampling
from parameters import LEARN_RATE, EPOCHS, CHECKPOINT_EVERY, TEST_BATCH_SIZE, DROP_OUT
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
import sys
import json

os.environ['CUDA_VISIBLE_DEVICES'] = '-1'

def get_one_hot_similarity_label(left_labels, right_labels):
    sim_labels = []
    sim_labels_num = []
    for i in range(0,len(left_labels)):
        # print "---------------------------------"
        # print left_labels[i] + "," + right_labels[i]
        if left_labels[i] == right_labels[i]:
            sim_labels.append([0.0,1.0])
            sim_labels_num.append(1)
        else:
            sim_labels.append([1.0,0.0])
            sim_labels_num.append(0)
    return sim_labels, sim_labels_num

def get_trees_from_pairs(all_pairs):

    left_trees = []
    right_trees = []
    for pair in all_pairs:
        left_trees.append(pair[0])
        right_trees.append(pair[1])
    
    return left_trees, right_trees


def test_model(logdir, left_inputs, right_inputs, left_embedfile, right_embedfile, epochs=EPOCHS):
    """Train a classifier to label ASTs"""


    n_classess = 2
    # left_algo_labels = ['mergesort', 'linkedlist', 'quicksort', 'bfs', 'bubblesort', 'knapsack']
    # right_algo_labels = ['mergesort', 'linkedlist', 'quicksort', 'bfs', 'bubblesort', 'knapsack']
    left_algo_labels = ["bfs","bubblesort","knapsack","linkedlist","mergesort","quicksort","heap","dfs","stack","queue"]
    right_algo_labels = ["bfs","bubblesort","knapsack","linkedlist","mergesort","quicksort","heap","dfs","stack","queue"]
    # with open(left_inputs, 'rb') as fh:
    #     _, left_trees, left_algo_labels = pickle.load(fh)


    # with open(right_inputs, 'rb') as fh:
    #     _, right_trees, right_algo_labels = pickle.load(fh)
   
    print("Loading trees...")
  
    with open(left_inputs, 'rb') as fh:
        _, left_trees, left_labels = pickle.load(fh)

        # random.shuffle(trees)

    with open(right_inputs, 'rb') as fh:
        _, right_trees, right_labels = pickle.load(fh)
        # random.shuffle(trees)

        
    print("num left trees : " + str(len(left_trees)))
    print("num right trees : " + str(len(right_trees)))
    print(left_labels)
    print(right_labels)

    diff = len(left_trees) - len(right_trees)

    # print("diff : " + str(diff))
    # temp_trees = right_trees[0:diff]
    # print("temp trees : " + str(len(temp_trees)))

    right_trees.extend(right_trees[0:499])
    right_trees.extend(right_trees[0:155])

    print("new right trees : " + str(len(right_trees)))
    print "Loading embdding vectors...."
    with open(left_embedfile, 'rb') as fh:
        left_embeddings, left_embed_lookup = pickle.load(fh)
        
    with open(right_embedfile, 'rb') as fh:
        right_embeddings, right_embed_lookup = pickle.load(fh)

    num_feats = len(left_embeddings[0])


    # build the inputs and outputs of the network
    left_nodes_node, left_children_node, left_pooling_node = network.init_net_for_siamese(
        num_feats
    )

    right_nodes_node, right_children_node, right_pooling_node = network.init_net_for_siamese(
        num_feats
    )

    merge_node = tf.concat([left_pooling_node, right_pooling_node], -1)


    hidden_node = network.hidden_layer(merge_node, 200, 200)
    # hidden_node = tf.layers.dropout(hidden_node, rate=0.2, training=False)

    hidden_node = network.hidden_layer(hidden_node, 200, 200)
    # hidden_node = tf.layers.dropout(hidden_node, rate=0.2, training=False)

    hidden_node = network.hidden_layer(hidden_node, 200, n_classess)


    out_node = network.out_layer(hidden_node)

    labels_node, loss_node = network.loss_layer(hidden_node, n_classess)

    optimizer = tf.train.AdamOptimizer(LEARN_RATE)
    train_step = optimizer.minimize(loss_node)

    # tf.summary.scalar('loss', loss_node)

    ### init the graph
    sess = tf.Session()#config=tf.ConfigProto(device_count={'GPU':0}))
    sess.run(tf.global_variables_initializer())

    with tf.name_scope('saver'):
        saver = tf.train.Saver()
        ckpt = tf.train.get_checkpoint_state(logdir)
        if ckpt and ckpt.model_checkpoint_path:
            saver.restore(sess, ckpt.model_checkpoint_path)
        else:
            raise 'Checkpoint not found.'

    checkfile = os.path.join(logdir, 'cnn_tree.ckpt')
    steps = 0

   

    using_vector_lookup_left = False
    if os.path.isfile("/input/config.json"):
	    file_handler = open(config_file, 'r')
	    contents = json.load(file_handler)
	    using_vector_lookup_left = contents['using_vector_lookup_left'] == "false"

    correct_labels = []
    predictions = []
    print('Computing testing accuracy...')
    for left_gen_batch, right_gen_batch in sampling.batch_random_samples_2_sides(left_trees, left_algo_labels, right_trees, right_algo_labels, left_embeddings, left_embed_lookup, right_embeddings, right_embed_lookup, using_vector_lookup_left, False, TEST_BATCH_SIZE):
        left_nodes, left_children, left_labels_one_hot, left_labels = left_gen_batch

        right_nodes, right_children, right_labels_one_hot, right_labels = right_gen_batch
        sim_labels, _ = get_one_hot_similarity_label(left_labels,right_labels)
        print("sim labels : " + str(sim_labels))
        output, left_vectors, right_vectors = sess.run([out_node, left_pooling_node, right_pooling_node],
            feed_dict={
                left_nodes_node: left_nodes,
                left_children_node: left_children,
                right_nodes_node: right_nodes,
                right_children_node: right_children,
                labels_node: sim_labels
            }
        )
        print(left_labels)
        print(right_labels)
        print("---------------------------------------")
        # print(vector_representation)
        # print(len(vector_representation))
        # print(len(vector_representation[0]))
        
        left_vector_str = ""
        right_vector_str = ""
        for v in left_vectors[0]:
            left_vector_str = left_vector_str + " " + str(v)
        left_temp = str(left_labels[0]) + left_vector_str

        for v in right_vectors[0]:
            right_vector_str = right_vector_str + " " + str(v)

        right_temp = str(right_labels[0]) + right_vector_str
        
        with open("./test_vectors/cpp_vectors_bitbcnn_def_use.txt", "a") as f:
            f.write(left_temp + "\n")
        with open("./test_vectors/java_vectors_bitbcnn_def_use.txt", "a") as f:
            f.write(right_temp + "\n")
  

    # target_names = ["0","1"]
    # print('Accuracy:', accuracy_score(correct_labels, predictions))
    # print(classification_report(correct_labels, predictions, target_names=target_names))
    # print(confusion_matrix(correct_labels, predictions))

   
def main():

     # example params : 
        # argv[1] = ./bi-tbcnn/bi-tbcnn/logs/1
        # argv[2] = ./sample_pickle_data/all_training_pairs.pkl
        # argv[3] = ./sample_pickle_data/python_pretrained_vectors.pkl
        # argv[4] = ./sample_pickle_data/fast_pretrained_vectors.pkl
    # test_model(sys.argv[1],sys.argv[2],sys.argv[3], sys.argv[4])
    test_model("bi-tbcnn/bi-tbcnn/logs/logs/def_use","data/cpp_algorithms_tree_def_use.pkl","data/java_algorithms_tree_def_use.pkl","sample_pickle_data/sample_pickle_data/fast_pretrained_vectors.pkl","sample_pickle_data/sample_pickle_data/fast_pretrained_vectors.pkl")


if __name__ == "__main__":
    main()
