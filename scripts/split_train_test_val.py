import shutil
import os
import random
from random import shuffle
from shutil import copyfile
from concurrent.futures import ThreadPoolExecutor

# ROOT = "/home/nghibui/codes/bi-tbcnn/"
src_dir = "github_java_pkl"
tgt_dir = "github_java_pkl_train_test_val"

algo_directories = os.listdir(src_dir)


# names = ["train","test","val"]
# for name in names:
   
def copy_parts(purpose, files, algo_name):
 for file in files:
    old_file_path = os.path.join(src_dir, algo_name, file)
    new_file_path = os.path.join(tgt_dir, purpose, algo_name, file)

    new_dir_path = os.path.join(tgt_dir, purpose, algo)
    if not os.path.exists(new_dir_path):
        os.makedirs(new_dir_path)
    copyfile(old_file_path, new_file_path)

for i, algo in enumerate(algo_directories):
       

    algo_directory = os.path.join(src_dir,algo)
   
    algo_directory_splits = algo_directory.split("/")
   
    
    files = os.listdir(algo_directory)
    shuffle(files)
    shuffle(files)
    shuffle(files)

    # Assume there is 500 files totally for the PKU data
    # train = 
    train_count = int((len(files)*75)/100)
    test_count = int((len(files)*20)/100)
    valid_count = int((len(files)*5)/100)

    print("Num train instances : " + str(train_count))
    print("Num test instances : " + str(test_count))
    print("Num validation instances : " + str(valid_count))

    train_start_index = 0
    train_end_index = train_count

    valid_start_index = train_end_index 
    valid_end_index = valid_start_index + valid_count

    test_start_index = valid_end_index
    test_end_index = len(files) - 1

    print(train_start_index, train_end_index)
    print(valid_start_index, valid_end_index)
    print(test_start_index, test_end_index)

    train = files[train_start_index:train_end_index]
    test = files[test_start_index:test_end_index]
    val = files[valid_start_index:valid_end_index]
    
    copy_parts("train",train,algo)
    copy_parts("test",test,algo)
    copy_parts("val",val,algo)