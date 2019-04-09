from tensorflow import saved_model
from tensorflow.python.saved_model import tag_constants
from tensorflow.python.saved_model.signature_def_utils_impl import predict_signature_def
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
from data_loader import load_program_data
from data_loader import MonoLanguageProgramData
from data_loader import load_single_program_for_live_test
from data_loader import build_tree
from data_loader import search_function_node
import argparse
import random
import shutil
from utils import scale_attention_score
from utils import scale_attention_score_by_group
from utils import robust_scale
import math
import operator
from numpy import dot
from numpy.linalg import norm




os.environ['CUDA_VISIBLE_DEVICES'] = "0"

parser = argparse.ArgumentParser()
parser.add_argument('--test_batch_size', type=int, default=10, help='test batch size')
parser.add_argument('--niter', type=int, default=300, help='number of epochs to train for')
parser.add_argument('--lr', type=float, default=0.01, help='learning rate')
parser.add_argument('--cuda', action='store_true', help='enables cuda')
parser.add_argument('--verbal', type=bool, default=True, help='print training info or not')
parser.add_argument('--manualSeed', type=int, help='manual seed')
parser.add_argument('--n_classes', type=int, default=10, help='manual seed')
parser.add_argument('--test_file', default="live_test/github_cpp/26/10.cpp", help='test program')
parser.add_argument('--model_path', default="model/github_sort_10_java_attention_sum_softmax", help='path to save the model')
parser.add_argument('--n_hidden', type=int, default=50, help='number of hidden layers')
parser.add_argument('--log_path', default="" ,help='log path for tensorboard')
parser.add_argument('--epoch', type=int, default=0, help='epoch to test')
parser.add_argument('--feature_size', type=int, default=100, help='epoch to test')
parser.add_argument('--aggregation', type=int, default=1, help='0 for max pooling, 1 for global attention')
parser.add_argument('--distributed_function', type=int, default=1, choices=range(0,2), help='0 for softmax, 1 for sigmoid')
parser.add_argument('--embeddings_directory', default="embedding/fast_pretrained_vectors.pkl", help='pretrained embeddings url, there are 2 objects in this file, the first object is the embedding matrix, the other is the lookup dictionary')


opt = parser.parse_args()

aggregation_name = ""
if opt.aggregation == 0:
    print("Using max pooling...........")
if opt.aggregation == 1:
    print("Using attention with sum pooling...........")
    aggregation_name = "sum"
if opt.aggregation == 2:
    print("Using attention with max pooling...........")
    aggregation_name = "max"
if opt.aggregation == 3:
    print("Using attention with average pooling...........")
    aggregation_name = "average"


distributed_function_name = ""
if opt.distributed_function == 0:
    print("Using softmax as the distributed_function...........")
    distributed_function_name = "softmax"
if opt.distributed_function == 1:
    print("Using sigmoid as the distributed_function...........")
    distributed_function_name = "sigmoid"



if not os.path.isdir("cached"):
    os.mkdir("cached")


def generate_pb(src_path):
    path_splits = src_path.split("/")
    file_name = path_splits[len(path_splits)-1].split(".")[0]
    generated_dir = os.path.join("/".join(path_splits[:len(path_splits)-1]),file_name)
    if not os.path.isdir(generated_dir):
        os.mkdir(generated_dir)
    pb_path = os.path.join(generated_dir, file_name + ".pb")
    if not os.path.exists(pb_path):
        cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -p " + src_path + " " + pb_path
        os.system(cmd)
    return pb_path


def generate_pkl(pb_path):
    pkl_path = os.path.join(pb_path.split(".")[0] + ".pkl")

    if not os.path.exists(pkl_path):
        cmd = "docker run --rm -v $(pwd):/e -it yijun/fast " + pb_path + " " + pkl_path
        print(cmd)
        os.system(cmd)
    return pkl_path

# def generate_visualization_accumulation(pkl_path):
#     path_splits = src_path.split("/")
#     file_name = path_splits[len(path_splits)-1].split(".")[0]
#     attention_path = os.path.join(file_name + "_raw_attention_without_node_type.csv")
#     pb_path = os.path.join(file_name + ".pb")
#     html_path = os.path.join(file_name + "_" + aggregation_name + "_" + distributed_function_name + "_" + "accumulation.html")
#     cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H -a -t -y " + attention_path + " " + pb_path  + " > " + html_path
#     os.system(cmd)
#     return html_path

def generate_visualization(pkl_path):
  
    attention_path = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "scaled_attention_without_node_type.csv")
    attention_path_all_1 = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "attention_all_1.csv")
    node_type_attention_path = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "only_node_type.csv")
    pb_path = os.path.join(pkl_path.split(".")[0] + ".pb")
   
    normal_html_path = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "normal.html")
    normal_node_html_path = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "normal_node_type.html")

    accumulation_html_path = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "accumulation.html")
    spreading_html_path = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "spreading.html")
    spreading_with_subtree_size_html_path = os.path.join(pkl_path.split(".")[0] + "_" + aggregation_name + "_" + distributed_function_name + "_" +  "spreading_with_weight.html")

    normal_node_id_cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H 0 -t -x " + attention_path + " " + pb_path  + " > " + normal_html_path
    normal_node_type_cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H 0 -t -x " + attention_path_all_1 + " " + " -Y " + node_type_attention_path + " " + pb_path  + " > " + normal_node_html_path

    accumulation_cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H 0 -a 0 -x " + attention_path + " " + pb_path  + " > " + accumulation_html_path
    spreading_cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H 0 -a 1 -x " + attention_path + " " + pb_path  + " > " + spreading_html_path
    spreading__with_weight_cmd = "docker run --rm -v $(pwd):/e -it yijun/fast -H 0 -a 2 -x " + attention_path + " " + pb_path  + " > " + spreading_with_subtree_size_html_path
    
    os.system(normal_node_id_cmd)
    os.system(normal_node_type_cmd)
    os.system(accumulation_cmd)
    os.system(spreading_cmd)
    os.system(spreading__with_weight_cmd)
    return normal_html_path,accumulation_html_path, spreading_html_path, spreading_with_subtree_size_html_path

def generate_sort_function_subtree_ids(pb_path, node_id):
    subtree_ids_path = os.path.join(pb_path.split(".")[0] + "_subtree_ids.txt")
    if not os.path.exists(subtree_ids_path):
        cmd = "docker run -v $(pwd):/e yijun/fast -CA " +  str(node_id) + " " + pb_path + " > " + subtree_ids_path
        os.system(cmd)

    subtree_ids = list()
    with open(subtree_ids_path) as fp:
        data = fp.readlines()
        for line in data:
            subtree_ids.append(line.replace("\n",""))

    return subtree_ids_path, subtree_ids

def generate_subtree_ids(pb_path, node_id):
    subtree_ids_path = os.path.join(pb_path.split(".")[0] + "_temp_subtree_ids.txt")
    
    cmd = "docker run -v $(pwd):/e yijun/fast -CA " +  str(node_id) + " " + pb_path + " > " + subtree_ids_path
    os.system(cmd)

    subtree_ids = list()
    with open(subtree_ids_path) as fp:
        data = fp.readlines()
        for line in data:
            subtree_ids.append(line.replace("\n",""))

    # os.remove(subtree_ids_path)
    return subtree_ids

def generate_histogram(pb_path):

    histogram_path = os.path.join(pb_path.split(".")[0] + "_histogram.txt")

    cmd = "docker run -v $(pwd):/e yijun/fast -d --histogram " + pb_path + " > " + histogram_path
    os.system(cmd)

    return histogram_path

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

def predict(sess, out_node, attention_score_node, nodes_node, children_node, pkl_path, pb_path, subtree_ids, test_trees, labels, node_ids, node_types, nodes_common_part_vector, embeddings, embedding_lookup):
    for batch in sampling.batch_samples(
            sampling.gen_samples(test_trees, labels, embeddings, embedding_lookup), 1
        ):
        nodes, children, batch_labels = batch
        output, attention_score = sess.run([out_node, attention_score_node],
            feed_dict={
                nodes_node: nodes,
                children_node: children,
            }
        )

        # print(output)

        splits = pkl_path.split(".")
        # node_ids = node_ids[0]
        # node_types = node_types[0]

        confidence_score = output[0]
        actual = str(np.argmax(batch_labels)+1)
        predicted = str(np.argmax(output)+1)

        print("Probability : " + str(confidence_score))
        print("Actual classes : " + str(np.argmax(batch_labels)+1))
        print("Predicted classes : " + str(np.argmax(output)+1))

        max_node = len(nodes[0])

        attention_score = np.reshape(attention_score, (max_node))
        # print(attention_score)

        attention_score_map = {}
        for i, score in enumerate(attention_score):
            key = str(node_ids[i])
            attention_score_map[key] = float(score)

        # Sort the scores
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
        
        generate_attention_score(attention_score, attention_score_scaled, node_ids, node_types, pb_path)

        # Conduct vector
        oracle_score_map = {}
        reverse_oracle_score_map = {}

        for node_id, score in attention_score_map.items():
            if node_id in subtree_ids:
                oracle_score_map[node_id] = 1
                reverse_oracle_score_map[node_id] = 0
            else:
                oracle_score_map[node_id] = 0
                reverse_oracle_score_map[node_id] = 1


        ratio = float(len(subtree_ids)/len(node_ids))
        # print("Ratio : " + str(ratio))
        # Produce 3 vectors
        oracle_vector = list()
        reverse_oracle_vector = list()
        attention_vector = list()

        for element in attention_score_sorted:
            node_id, score = element[0], element[1]
            attention_vector.append(attention_score_map[node_id])
            oracle_vector.append(oracle_score_map[node_id])
            reverse_oracle_vector.append(reverse_oracle_score_map[node_id])

        # print(attention_vector)
        # print(reverse_oracle_vector)
        # print(oracle_vector)

        cos_sim_oracle = cosine_simlarity(np.array(attention_vector), np.array(oracle_vector))
        cos_sim_reverse_oracle = cosine_simlarity(np.array(attention_vector), np.array(reverse_oracle_vector))

        cos_sim_common_part = cosine_simlarity(np.array(attention_vector), np.array(reverse_oracle_vector))
        # cos_sim_oracle = cos_sim_oracle * ratio
        # cos_sim_reverse_oracle = cos_sim_reverse_oracle * (1 - ratio)
        # print(cos_sim_oracle)
        # print(cos_sim_reverse_oracle)

        generate_visualization(pkl_path)
        return cos_sim_oracle, cos_sim_reverse_oracle, cos_sim_common_part, ratio, actual, predicted, confidence_score

def cosine_simlarity(a, b):
    return dot(a, b)/(norm(a)*norm(b))


def read_node_count(histogram_path):
    node_count_map = {}
    with open(histogram_path,"r") as f:
        data = f.readlines()
        for line in data:
           
            line = line.replace("\n","")
            splits = line.split(",")
            node_count_map[splits[1].split(":")[0]] = int(splits[1])
    return node_count_map


def read_common_part():
    common_part = "github_java_sort_function_histogram/" 
    common_part_map = {}
    for i in range(1,10):
        common_part_map[str(i)] = {}
        path = common_part + str(i) + ".txt"
        with open(path,"r") as f:
            data = f.readlines()
            for line in data:
                line = line.replace("\n","")
                splits = line.split(",")
                common_part_map[str(i)][splits[1].split(":")[0]] = int(splits[1])

    return common_part_map


def load_program(file_path):

    pb_path = generate_pb(file_path)
    pkl_path = generate_pkl(pb_path)
    
    histogram_path = generate_histogram(pb_path)
    node_count_map = read_node_count(histogram_path)
    common_part_map = read_common_part()
    # print(common_part_map)

    ast_representation = build_tree(pkl_path)
    sort_function_id = search_function_node(ast_representation, "sort")
   
    subtree_ids_path, subtree_ids = generate_sort_function_subtree_ids(pb_path, sort_function_id)
   
    ast_representation_path = pkl_path.split(".")[0] + "_ast.txt"
    if not os.path.exists(ast_representation_path):
        with open(ast_representation_path,"w") as f:
            f.write(str(ast_representation))    


    label = file_path.split("/")[-2]

    # print(label)
    # an array of only 1 tree, just wrap it into 1 more dimension to make it consistent with the training process
    test_trees, _ , node_ids, node_types, nodes_common_part_vector = load_single_program_for_live_test(pkl_path, common_part_map[label], node_count_map)
    print(nodes_common_part_vector)
    return test_trees, node_ids, node_types, nodes_common_part_vector, subtree_ids, sort_function_id, pkl_path, pb_path

def main(opt):

    target_directory = "live_test/github_java/sort_function/"
    file_name = aggregation_name + "_" + distributed_function_name + "_function.csv"

    print("Loading embeddings....")
    with open(opt.embeddings_directory, 'rb') as fh:
        embeddings, embed_lookup = pickle.load(fh,encoding='latin1')
    labels = [str(i) for i in range(1, opt.n_classes+1)]
    logdir = opt.model_path
    batch_size = opt.test_batch_size
    epochs = opt.niter
    node_embedding_size = len(embeddings[0])

    # Loading program file
    # test_trees, node_ids, node_types, subtree_ids, pkl_path = load_program(opt)

   
    # Init model
    checkfile = os.path.join(logdir, 'cnn_tree.ckpt')   
    ckpt = tf.train.get_checkpoint_state(logdir)
    
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

    nodes_node, children_node, hidden_node, attention_score_node = network.init_net(
        node_embedding_size,
        len(labels),
        opt.feature_size,
        weights,
        biases,
        opt.aggregation,
        opt.distributed_function
    )
   
    out_node = network.out_layer(hidden_node)
    labels_node, loss_node = network.loss_layer(hidden_node, len(labels))

    optimizer = tf.train.AdamOptimizer(LEARN_RATE)
    train_step = optimizer.minimize(loss_node)
    
    saver = tf.train.Saver(save_relative_paths=True, max_to_keep=5)
    # Initialize the variables (i.e. assign their default value)
    init = tf.global_variables_initializer()
    logdir = opt.model_path
    batch_size = opt.test_batch_size
    epochs = opt.niter
    node_embedding_size = len(embeddings[0])

    with tf.Session() as sess:
        sess.run(init)
        ckpt = tf.train.get_checkpoint_state(logdir)
        if ckpt and ckpt.model_checkpoint_path:
            print("Continue training with old model")
            print("Checkpoint path : " + str(ckpt.model_checkpoint_path))
            saver.restore(sess, ckpt.model_checkpoint_path)
            for i, var in enumerate(saver._var_list):
                print('Var {}: {}'.format(i, var))

        
        analysis_file = "analysis_single/" + file_name

        if os.path.exists(analysis_file):
            os.remove(analysis_file)
        with open(analysis_file,"a") as f:
            # f.write("file,oracle_cosim,reverse_oracle_cosim,function_node_id,function_size,program_size,function_ratio,actual,predicted,confidence_score")
            f.write("file,common_part_cosim,actual,predicted,confidence_score")
            f.write("\n")

        for i in range(1, 11):
            algorithm_directory = os.path.join(target_directory,str(i))
            print(algorithm_directory)
            files = os.listdir(algorithm_directory)
            for file in files:
              
                file_path = os.path.join(algorithm_directory,file)
                print(file_path)
                if os.path.isfile(file_path):

                    test_trees, node_ids, node_types, nodes_common_part_vector, subtree_ids, sort_function_id, pkl_path, pb_path = load_program(file_path)

                    cos_sim_oracle, cos_sim_reverse_oracle, cos_sim_common_part, ratio, actual, predicted, confidence_score = predict(sess, out_node, attention_score_node, nodes_node, children_node, pkl_path, pb_path, subtree_ids, test_trees, labels, node_ids, node_types, nodes_common_part_vector, embeddings, embed_lookup)
                    
                    with open(analysis_file,"a") as f:
                        # f.write(file_path + "," + str(cos_sim_oracle) + "," + str(cos_sim_reverse_oracle) + "," + str(sort_function_id) + "," + str(len(subtree_ids)) + "," + str(len(node_ids)) + "," + str(ratio) + "," + str(actual) + "," + str(predicted) + "," + str(" ".join(str(v) for v in confidence_score)))
                        f.write(file_path + "," + str(cos_sim_common_part) + "," + str(actual) + "," + str(predicted) + "," + str(" ".join(str(v) for v in confidence_score)))
                        f.write("\n")

if __name__ == "__main__":
    main(opt)