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

def get_all_tree_with_label(trees,label):
	temp_trees = []
	for tree in trees:
		if tree["label"] == label:
			temp_trees.append(tree)
	return temp_trees

def generate_clusters(trees):
	bubblesort_clusters = list()
	bfs_clusters = list()
	dfs_clusters = list()
	heap_clusters = list()
	knapsack_clusters = list()
	linkedlist_clusters = list()
	mergesort_clusters = list()
	queue_clusters = list()
	quicksort_clusters = list()
	stack_clusters = list()

	for tree in trees:
		if tree["label"] == "bubblesort":
			bubblesort_clusters.append(tree)
		if tree["label"] == "bfs":
			bfs_clusters.append(tree)
		if tree["label"] == "dfs":
			dfs_clusters.append(tree)
		if tree["label"] == "heap":
			heap_clusters.append(tree)
		if tree["label"] == "knapsack":
			knapsack_clusters.append(tree)
		if tree["label"] == "linkedlist":
			linkedlist_clusters.append(tree)		
		if tree["label"] == "mergesort":
			mergesort_clusters.append(tree)
		if tree["label"] == "queue":
			queue_clusters.append(tree)
		if tree["label"] == "quicksort":
			quicksort_clusters.append(tree)
		if tree["label"] == "stack":
			stack_clusters.append(tree)



def generate_testing_pairs():

	with open("./data/cpp_algorithms_tree_def_use.pkl", 'rb') as fh:
	 	# left_trees, _, left_algo_labels = pickle.load(fh)
	 	_, left_trees_dependency, left_algo_labels_dependency = pickle.load(fh)


	with open("./data/java_algorithms_tree_def_use.pkl", 'rb') as fh:
		# right_trees, _, right_algo_labels = pickle.load(fh)
		_, right_trees_dependency, right_algo_labels_dependency = pickle.load(fh)


	# with open("./data/cpp_algorithms_tree.pkl", 'rb') as fh:
	#  	# left_trees, _, left_algo_labels = pickle.load(fh)
	#  	_, left_trees, left_algo_labels = pickle.load(fh)


	# with open("./data/java_algorithms_tree.pkl", 'rb') as fh:
	# 	# right_trees, _, right_algo_labels = pickle.load(fh)
	# 	_, right_trees, right_algo_labels = pickle.load(fh)
		
	print "Finish loading data......"

	target = "queue"
	cpp_bubble_sort_trees = get_all_tree_with_label(left_trees_dependency,target)
	print len(cpp_bubble_sort_trees)

	random_cpp_trees = random.sample(cpp_bubble_sort_trees,10)


	# bubblesort_clusters = list()
	# bfs_clusters = list()
	# dfs_clusters = list()
	# heap_clusters = list()
	# knapsack_clusters = list()
	# linkedlist_clusters = list()
	# mergesort_clusters = list()
	# queue_clusters = list()
	# quicksort_clusters = list()
	# stack_clusters = list()

	# for tree in right_trees_dependency:
	# 	if tree["label"] == "bubblesort":
	# 		bubblesort_clusters.append(tree)
	# 	if tree["label"] == "bfs":
	# 		bfs_clusters.append(tree)
	# 	if tree["label"] == "dfs":
	# 		dfs_clusters.append(tree)
	# 	if tree["label"] == "heap":
	# 		heap_clusters.append(tree)
	# 	if tree["label"] == "knapsack":
	# 		knapsack_clusters.append(tree)
	# 	if tree["label"] == "linkedlist":
	# 		linkedlist_clusters.append(tree)		
	# 	if tree["label"] == "mergesort":
	# 		mergesort_clusters.append(tree)
	# 	if tree["label"] == "queue":
	# 		queue_clusters.append(tree)
	# 	if tree["label"] == "quicksort":
	# 		quicksort_clusters.append(tree)
	# 	if tree["label"] == "stack":
	# 		stack_clusters.append(tree)

	# number_of_samples = 10

	# bubblesort_clusters = random.sample(bubblesort_clusters,number_of_samples)
	# bfs_clusters = random.sample(bfs_clusters,number_of_samples)
	# dfs_clusters = random.sample(dfs_clusters,number_of_samples)
	# heap_clusters =random.sample(heap_clusters,number_of_samples)
	# knapsack_clusters = random.sample(knapsack_clusters,number_of_samples)
	# linkedlist_clusters = random.sample(linkedlist_clusters,number_of_samples)
	# mergesort_clusters = random.sample(mergesort_clusters, number_of_samples)
	# queue_clusters = random.sample(queue_clusters, number_of_samples)
	# quicksort_clusters = random.sample(quicksort_clusters,number_of_samples)
	# stack_clusters = random.sample(stack_clusters,number_of_samples)
	# java_clusters = (bubblesort_clusters, bfs_clusters, dfs_clusters, heap_clusters, knapsack_clusters, linkedlist_clusters, mergesort_clusters, queue_clusters, quicksort_clusters, stack_clusters)


	# with open("./data/clusters_test.pkl", 'wb') as file_handler:
	# 	pickle.dump(java_clusters, file_handler)
	# 	file_handler.close()

	with open("./data/cpp_" + target + "_trees.pkl", 'wb') as file_handler:
		pickle.dump(random_cpp_trees, file_handler)
		file_handler.close()

# def generate_testing_pairs(left_url, right_url, outfile):

# 	with open(left_url, 'rb') as fh:
# 	 	# left_trees, _, left_algo_labels = pickle.load(fh)
# 	 	_, left_trees, left_algo_labels = pickle.load(fh)


# 	with open(right_url, 'rb') as fh:
# 		# right_trees, _, right_algo_labels = pickle.load(fh)
# 		_, right_trees, right_algo_labels = pickle.load(fh)

# 	all_1_pairs, all_0_pairs = get_all_pairs_for_testing(left_trees,right_trees)
# 	print "1 pairs:" + str(len(all_1_pairs)) + " 0 pairs:" + str(len(all_0_pairs))

# 	# random.shuffle(all_1_pairs)
# 	# random.shuffle(all_0_pairs)

	
# 	random_1_pairs = random.sample(all_1_pairs,2000)
# 	random_0_pairs = random.sample(all_0_pairs,2000)


# 	all_testing_random_pairs = random_1_pairs + random_0_pairs
# 	random.shuffle(all_testing_random_pairs)

# 	with open(outfile, 'wb') as file_handler:
# 		pickle.dump(all_testing_random_pairs, file_handler)
# 		file_handler.close()


if __name__ == "__main__": 
   # example : generate_training_pairs("./data/cpp_algorithms_trees.pkl","./data/java_algorithms_trees.pkl","./data/4000_testing_pairs.pkl")
   # generate_testing_pairs(sys.argv[1], sys.argv[2], sys.argv[3])
   generate_testing_pairs()