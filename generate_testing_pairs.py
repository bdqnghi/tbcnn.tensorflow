import pickle
import sampling
import random
import sys
from tqdm import *

def get_all_pairs_for_testing(left_inputs,right_inputs):
    all_1_pairs = []
    all_0_pairs = []
    count = 0
    for left_tree in left_inputs:
        for right_tree in right_inputs:
            if left_tree["label"] == right_tree["label"]:
                all_1_pairs.append((left_tree,right_tree))
            else:
                all_0_pairs.append((left_tree,right_tree))
            print(count)
            count += 1
    return all_1_pairs, all_0_pairs

# def generate_testing_pairs():

# 	with open("./data/cpp_algorithms_tree_def_use.pkl", 'rb') as fh:
# 	 	# left_trees, _, left_algo_labels = pickle.load(fh)
# 	 	_, left_trees_dependency, left_algo_labels_dependency = pickle.load(fh)


# 	with open("./data/java_algorithms_tree_def_use.pkl", 'rb') as fh:
# 		# right_trees, _, right_algo_labels = pickle.load(fh)
# 		_, right_trees_dependency, right_algo_labels_dependency = pickle.load(fh)


# 	with open("./data/cpp_algorithms_tree.pkl", 'rb') as fh:
# 	 	# left_trees, _, left_algo_labels = pickle.load(fh)
# 	 	_, left_trees, left_algo_labels = pickle.load(fh)


# 	with open("./data/java_algorithms_tree.pkl", 'rb') as fh:
# 		# right_trees, _, right_algo_labels = pickle.load(fh)
# 		_, right_trees, right_algo_labels = pickle.load(fh)
		
# 	print "Finish loading data......"

# 	all_1_pairs, all_0_pairs = get_all_pairs_for_testing(left_trees,right_trees)
# 	all_1_pairs_dependency, all_0_pairs_dependency = get_all_pairs_for_testing(left_trees_dependency,right_trees_dependency)
# 	print "1 pairs:" + str(len(all_1_pairs)) + " 0 pairs:" + str(len(all_0_pairs))
# 	print "1 pairs dependency:" + str(len(all_1_pairs_dependency)) + " 0 pairs dependency:" + str(len(all_0_pairs_dependency))

# 	# random.shuffle(all_1_pairs)
# 	# random.shuffle(all_0_pairs)
# 	c = list(zip(all_1_pairs,all_1_pairs_dependency))
# 	d = list(zip(all_0_pairs,all_0_pairs_dependency))
	
# 	random.shuffle(c)
# 	random.shuffle(c)
# 	random.shuffle(d)
# 	random.shuffle(d)

# 	random_1_pairs = random.sample(c,2000)
# 	random_0_pairs = random.sample(d,2000)

# 	sample_all_1_pairs, sample_all_1_pairs_dependency = zip(*random_1_pairs)
# 	sample_all_0_pairs, sample_all_0_pairs_dependency = zip(*random_0_pairs)


# 	all_testing_random_pairs = sample_all_1_pairs + sample_all_0_pairs
# 	all_testing_random_pairs_dependency = sample_all_1_pairs_dependency + sample_all_0_pairs_dependency

# 	with open("./data/testing_pairs_no_dependency.pkl", 'wb') as file_handler:
# 		pickle.dump(all_testing_random_pairs, file_handler)
# 		file_handler.close()

# 	with open("./data/testing_pairs_def_use.pkl", 'wb') as file_handler:
# 		pickle.dump(all_testing_random_pairs_dependency, file_handler)
# 		file_handler.close()


def generate_testing_pairs(left_url, right_url, outfile):

	with open(left_url, 'rb') as fh:
	 	# left_trees, _, left_algo_labels = pickle.load(fh)
	 	_, left_trees, left_algo_labels = pickle.load(fh)


	with open(right_url, 'rb') as fh:
		# right_trees, _, right_algo_labels = pickle.load(fh)
		_, right_trees, right_algo_labels = pickle.load(fh)

	all_1_pairs, all_0_pairs = get_all_pairs_for_testing(left_trees,right_trees)
	print "1 pairs:" + str(len(all_1_pairs)) + " 0 pairs:" + str(len(all_0_pairs))

	# random.shuffle(all_1_pairs)
	# random.shuffle(all_0_pairs)

	
	random_1_pairs = random.sample(all_1_pairs,2000)
	random_0_pairs = random.sample(all_0_pairs,2000)


	all_testing_random_pairs = random_1_pairs + random_0_pairs
	random.shuffle(all_testing_random_pairs)

	with open(outfile, 'wb') as file_handler:
		pickle.dump(all_testing_random_pairs, file_handler)
		file_handler.close()


if __name__ == "__main__": 
   # example : generate_training_pairs("./data/cpp_algorithms_trees.pkl","./data/java_algorithms_trees.pkl","./data/4000_testing_pairs.pkl")
   generate_testing_pairs(sys.argv[1], sys.argv[2], sys.argv[3])
   # generate_testing_pairs()