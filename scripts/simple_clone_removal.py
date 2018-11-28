import shutil
import os
import random
from random import shuffle
from shutil import copyfile
from concurrent.futures import ThreadPoolExecutor


src_dir = "github_cpp"

algo_directories = os.listdir(src_dir)


total_after_removed = 0
total_before_removed = 0
for i, algo in enumerate(algo_directories):
    print("Algo : " + str(algo))

    algo_directory = os.path.join(src_dir,algo)
   
    algo_directory_splits = algo_directory.split("/")
   
    
    files = os.listdir(algo_directory)
    
    file_map = {}
    for file in files:
        file_path = os.path.join(algo_directory, file)

        try:
            with open(file_path, "r") as f:
                data = f.read()
                file_map[file_path] = str(data)
        except Exception as e:
            print(e)

    filtered_map = {}
    for key,value in file_map.items():
        if value not in filtered_map.values():
            filtered_map[key] = value

    print(len(file_map.keys()))
    print(len(filtered_map.keys()))
    total_before_removed = total_before_removed + len(file_map.keys())
    total_after_removed = total_after_removed + len(filtered_map.keys())
    # print(filtered_map)

    # Assume there is 500 files totally for the PKU data
    # train = 
print(total_after_removed)
print(total_before_removed)