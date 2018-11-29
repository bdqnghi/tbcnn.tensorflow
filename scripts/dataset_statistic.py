import shutil
import os
import random
from random import shuffle
from shutil import copyfile
from concurrent.futures import ThreadPoolExecutor


src_dir = "github_java_sort"

algo_directories = os.listdir(src_dir)

total_by_condition = 0
for i, algo in enumerate(algo_directories):
    print("Algo : " + str(algo))

    algo_directory = os.path.join(src_dir,algo)
    # print(algo_directory)
    # algo_directory_splits = algo_directory.split("/")
   
    
    files = os.listdir(algo_directory)
    print(len(files))

 