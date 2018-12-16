import shutil
import os
import random
from random import shuffle
from shutil import copyfile
from concurrent.futures import ThreadPoolExecutor
import re
import itertools



src_dir = "github_java_sort_pkl_train_test_val"
train_test_val_directories = os.listdir(src_dir)

for i, task in enumerate(train_test_val_directories):
    print("------Task : " + task)
    algo_directory = os.path.join(src_dir,task)
    
    all_pair_1 = list()
    all_pair_0 = list()
    for j, algo in enumerate(os.listdir(algo_directory)):
        print("Algo : " + str(algo))
        files = os.listdir(os.path.join(algo_directory,algo))

        file_paths = list()
        pair_1 = list()
        pair_0 = list()
        for file in files:
            file_path = os.path.join(algo_directory, algo, file)
            file_paths.append(file_path)

        for pair in itertools.product(file_paths, repeat=2):
            pair_1.append(pair)

        candidates_pair_0 = list()
        for j, other_algo in enumerate(os.listdir(algo_directory)):
            if other_algo != algo:
                print("Other algo : " + other_algo)
                other_files = os.listdir(os.path.join(algo_directory,other_algo))

                other_file_paths = list()
                for other_file in other_files:
                    other_file_path = os.path.join(algo_directory, other_algo, other_file)
                    other_file_paths.append(other_file_path)

                cart_prod = [(a,b) for a in file_paths for b in other_file_paths]
                candidates_pair_0.extend(cart_prod)

        pair_0.extend(random.sample(candidates_pair_0, len(pair_1)))

        all_pair_1.extend(pair_1)
        all_pair_0.extend(pair_0)


    all_pair_1 = list(set(all_pair_1))
    all_pair_0 = list(set(all_pair_0))

    # all_pairs = all_pair_1 + all_pair_0
    all_pairs = []
    for pair in all_pair_1:
        all_pairs.append(pair[0] + "," + pair[1] + "," + "1")
    for pair in all_pair_0:
        all_pairs.append(pair[0] + "," + pair[1] + "," + "0")
    random.shuffle(all_pairs)

    with open("pairwise/" + src_dir + "__" + task + ".txt","w") as f:
        for pair in all_pairs:
            f.write(pair)
            f.write("\n")

        # for pair in all_pair_0:
        #     f.write(pair[0] + "," + pair[1] + "," + "0")
        #     f.write("\n")



