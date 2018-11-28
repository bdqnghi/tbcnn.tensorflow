import shutil
import os
import random
from random import shuffle
from shutil import copyfile
from concurrent.futures import ThreadPoolExecutor
import re

src_dir = "github_cpp"

algo_directories = os.listdir(src_dir)


def remove_comments(string):
    pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*$)"
    # first group captures quoted strings (double or single)
    # second group captures comments (//single-line or /* multi-line */)
    regex = re.compile(pattern, re.MULTILINE|re.DOTALL)
    def _replacer(match):
        # if the 2nd group (capturing comments) is not None,
        # it means we have captured a non-quoted (real) comment string.
        if match.group(2) is not None:
            return "" # so we will return empty to remove the comment
        else: # otherwise, we will return the 1st group
            return match.group(1) # captured quoted-string
    return regex.sub(_replacer, string)


for i, algo in enumerate(algo_directories):
    print("Algo : " + str(algo))

    algo_directory = os.path.join(src_dir,algo)
   
    algo_directory_splits = algo_directory.split("/")
   
    
    files = os.listdir(algo_directory)
    
 
    for file in files:
        file_path = os.path.join(algo_directory, file)

        try:
            with open(file_path, "r") as f:
                data = str(f.read())

                data = remove_comments(data)

                count = len(data.split(" "))
                if count > 50:
                    with open(file_path, "w") as f2:
                        f2.write(data)
          
        except Exception as e:
            os.remove(file_path)

