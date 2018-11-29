# To make the cpp and java data to be balanced

import os
import random
from shutil import copyfile

ROOT = "/home/nghibui/codes/tbcnn-attention/"
walk_dir = "/home/nghibui/codes/tbcnn-attention/github_code"

algo_directories = os.listdir(walk_dir)

algo_index = 1

def create_folders(code_index_directory, lang, files, algo_index):



 
    if not os.path.exists(code_index_directory):
        os.mkdir(code_index_directory)

    if not os.path.exists(os.path.join(code_index_directory,lang)):
        os.mkdir(os.path.join(code_index_directory,lang))

    if not os.path.exists(os.path.join(code_index_directory,lang,str(algo_index))):
      
        os.mkdir(os.path.join(code_index_directory,lang,str(algo_index)))

  


    for file in files:
        old_path = os.path.join(walk_dir,ele,lang,file)
        new_path = os.path.join(code_index_directory,lang,str(algo_index),file)

        # print(old_path)
        # print(new_path)

        copyfile(old_path, new_path)

    
algorithm_name = "algorithms_name.txt"
try:
    os.remove(algorithm_name)
except Exception as e:
    print(e)

for i, ele in enumerate(algo_directories):
   

    algo_directory = os.path.join(walk_dir,ele)
    
    print(algo_directory)
    lang = "java"
   
    algo_directory_lang = os.path.join(algo_directory,lang)

    # if "sort" in ele:
    files = os.listdir(algo_directory_lang)

   
    if len(files) >= 60:

   
        code_index_directory = os.path.join(ROOT,"github_code_index")
        create_folders(code_index_directory, lang, files, algo_index)
      

        with open(algorithm_name,"a") as f:
            print(str(algo_index) + "," + ele)
            f.write(str(algo_index) + "," + ele)
            f.write("\n")

        algo_index += 1