import os
from shutil import copyfile



directory = "./github_java_sort_pkl_train_test_val/test/2"

target_directory = "live_test/github_java/sort/2"

if not os.path.exists(target_directory):
    os.mkdir(target_directory)

ROOT = "./github_java_sort/2"
files = os.listdir(directory)

for file in files:
    print(file)
    file_name = file.split(".")[0]
    file_path = os.path.join(ROOT,file_name + ".java")
    print(file_path)

    target_path = os.path.join(target_directory,file_name + ".java")

    copyfile(file_path, target_path)