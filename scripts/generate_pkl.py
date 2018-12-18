import subprocess
import os
import random
from shutil import copyfile
from concurrent.futures import ProcessPoolExecutor
import concurrent.futures
# ROOT = "/home/nghibui/codes/bi-tbcnn/"
# src_dir = "code_index"
# tgt_dir = "pb_code_index"

src_dir = "github_java_pb"
tgt_dir = "github_java_pkl"

langs = ["cpp","java"]
max_workers = 20
def execute_command(src_path,tgt_path):
    # -S into -p for pb only
    cmd = "docker run --rm -v $(pwd):/e -it yijun/fast " + src_path + " " + tgt_path
    print(cmd)
    os.system(cmd)
    # p = subprocess.Popen(cmd, shell=True)
    # try:
    #     p.wait(5)
    # except subprocess.TimeoutExpired:
    #     p.kill()

def stop_process_pool(executor):
    for pid, process in executor._processes.items():
        process.terminate()
    executor.shutdown()

with ProcessPoolExecutor(max_workers=max_workers) as executor:        
    for root, subdirs, files in os.walk(src_dir):
        for file in files:
            file_path = os.path.join(root,file)
            # print(path)
            print(file_path)
            pb_directory = os.path.join(tgt_dir, file_path.split("/")[1])
           
            # pb_directory = os.path.join(tgt_dir, )
            if not os.path.exists(pb_directory):
                os.makedirs(pb_directory)

            # Change to .pb from .csv for pb only, .csv is for slicing information
            pb_path = os.path.join(tgt_dir, file_path.split("/")[1], file_path.split("/")[2] + ".pkl")

            if not os.path.exists(pb_path):
                future = executor.submit(execute_command, file_path, pb_path)