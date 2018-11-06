import pickle
import sampling
import random
import sys
from tqdm import *

def get_all_pairs_for_training(left_inputs,right_inputs):
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

def chunkify(lst,n):
	return [lst[i::n] for i in xrange(n)]

def generate_training_pairs(left_url, right_url, outfile):

	with open(left_url, 'rb') as fh:
	 	# left_trees, _, left_algo_labels = pickle.load(fh)
	 	left_trees, _ , left_algo_labels = pickle.load(fh)


	with open(right_url, 'rb') as fh:
		# right_trees, _, right_algo_labels = pickle.load(fh)
		right_trees, _ , right_algo_labels = pickle.load(fh)

	all_1_pairs, all_0_pairs = get_all_pairs_for_training(left_trees,right_trees)
	

	random.shuffle(all_1_pairs)
	
	for i in range(0,1):
		random.shuffle(all_0_pairs)

	all_0_pairs = random.sample(all_0_pairs,len(all_1_pairs))
	print "1 pairs:" + str(len(all_1_pairs)) + " 0 pairs:" + str(len(all_0_pairs))
	# chunks_1_pairs = chunkify(all_1_pairs,100)
	# chunks_0_pairs = chunkify(all_0_pairs,100)
	
	with open(outfile, 'wb') as file_handler:
		pickle.dump((all_1_pairs,all_0_pairs), file_handler)
		file_handler.close()



	# with open("./data/all_training_pairs_part_" + str(i) + ".pkl", 'wb') as file_handler:
	# 	# pickle.dump((all_1_pairs,all_0_pairs), file_handler)
	# 	pickle.dump((chunks_1_pairs[i],chunks_0_pairs[i]), file_handler)
	# 	file_handler.close()	


if __name__ == "__main__": 
   # example : generate_training_pairs("./data/cpp_algorithms_trees.pkl","./data/java_algorithms_trees.pkl","./data/all_training_pairs.pkl")
   generate_training_pairs(sys.argv[1], sys.argv[2], sys.argv[3])
   # generate_training_pairs(sys.argv[1], sys.argv[2])