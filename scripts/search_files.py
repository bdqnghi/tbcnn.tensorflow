import subprocess
import os
import random
from shutil import copyfile
import re

src_dir = "github_cpp"


for root, subdirs, files in os.walk(src_dir):
    for file in files:
        file_path = os.path.join(root,file)
        # print(path)
        try:
            with open(file_path, "r") as f:
                data  = str(f.read())

                if "knapsack" in data:
                    # print(data)
                    print(file_path)
        except Exception as e:
            print(e)