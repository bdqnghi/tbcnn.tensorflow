import subprocess
import os
import random
from shutil import copyfile
import re

src_dir = "github_cpp"


langs = ["cpp","java"]
# RE = re.compile(ur'[\u4e00-\u9fff]+', re.UNICODE)
def getChinese(context):
    context = context.decode("utf-8") # convert context from str to unicode
    filtrate = re.compile(u'[^\u4e00-\u9fff]') # non-Chinese unicode range
    context = filtrate.sub(r'', context) # remove all non-Chinese characters
    context = context.encode("utf-8") # convert unicode back to str
    return context


for root, subdirs, files in os.walk(src_dir):
    for file in files:
        file_path = os.path.join(root,file)
        # print(path)
        print(file_path)
        try:
            with open(file_path, "r") as f:
                data  = f.read()
                # re.findall(ur'[\u4e00-\u9fff]+',data)
                data = getChinese(data.encode("utf-8"))
                print(data)
                # with open(file_path, "w") as f:
                #     f.write(data)
        except Exception as e:
            print(e)