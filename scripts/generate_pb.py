import subprocess
import os
import random
from shutil import copyfile
from concurrent.futures import ProcessPoolExecutor
import concurrent.futures
# ROOT = "/home/nghibui/codes/bi-tbcnn/"
# src_dir = "code_index"
# tgt_dir = "pb_code_index"

src_dir = "github_java"
tgt_dir = "github_java_pb"

langs = ["cpp","java"]
max_workers = 10
def execute_command(src_path,tgt_path):
    # -S into -p for pb only
    cmd = "docker run --rm -v $(pwd):/e -it yijun/fast:built -p " + src_path + " " + tgt_path
    print(cmd)
    # os.system(cmd)
    p = subprocess.Popen(cmd, shell=True)
    try:
        p.wait(5)
    except subprocess.TimeoutExpired:
        p.kill()

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
            pb_path = os.path.join(tgt_dir, file_path.split("/")[1], file_path.split("/")[2] + ".pb")

            if not os.path.exists(pb_path):
                future = executor.submit(execute_command, file_path, pb_path)
                # cmd = "docker run --rm -v $(pwd):/e -it yijun/fast:built -p " + file_path + " " + pb_path
                # print(cmd)
            
                # p = subprocess.Popen(cmd, shell=True)
                # try:
                #     p.wait(1)
                # except subprocess.TimeoutExpired:
                #     p.kill()
                # p = subprocess.Popen(["docker","run","--rm","-v","$(pwd):/e","-it","yijun/fast:built","-p","file_path","pb_path"])
                # try:
                #     p.wait(10)
                # except subp.TimeoutExpired:
                #     p.kill()
                
                # try:
                #     for future in concurrent.futures.as_completed(executor.map(execute_command, file_path, pb_path, timeout=5), timeout=5):
                #         print(future.result(timeout=1))
                # except concurrent.futures._base.TimeoutError:
                #     print("This took to long...")
                #     stop_process_pool(executor)