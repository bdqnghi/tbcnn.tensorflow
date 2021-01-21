import os
import xml.etree.ElementTree as ET
from dpu_utils.codeutils import identifiersplitting
import re

excluded_tokens = [",","{",";","}",")","(",'"',"'","`",""," ","[]","[","]","/",":",".","''","'.'","b", "\\", "'['", "']","''","_","__"]

def process_token(token):
    for t in excluded_tokens:
        token = token.replace(t, "")
        token = re.sub(r'[^\w]', ' ', token)
    return token

def remove_noisy_tokens(tokens):
    temp_tokens = []
    for t in tokens:
        if t not in excluded_tokens:
            t = process_token(t)
            if t:
                temp_tokens.append(t)
    return temp_tokens


directory = "../OJ_ctxl_train_test_val/train"
all_tags = []
all_texts = []
count = 0
for subdir , dirs, files in os.walk(directory): 
    for file in files:
      
        if file.endswith(".xml"):
            txl_file_path = os.path.join(subdir,file)
            print(txl_file_path)
            try:
                xml_representation = ET.parse(txl_file_path)

                txl_file_path_splits = txl_file_path.split("/")
                label = int(txl_file_path_splits[len(txl_file_path_splits)-2]) - 1

                with open(txl_file_path) as f:
                    line_count = sum(1 for _ in f)

                if line_count < 10000:

                    for element in xml_representation.getroot().iter():
                        all_tags.append(str(element.tag).upper())
                        token = process_token(str(element.text))
                        tokens = identifiersplitting.split_identifier_into_parts(token)
                        all_texts.extend(tokens)
            except Exception as e:
                print(e)
        count += 1


all_tags = list(set(all_tags))
all_texts = list(set(all_texts))

with open("c_txl_used_tags.txt", "w") as f:
    for tag in all_tags:
        f.write(tag)
        f.write("\n")

with open("c_txl_used_texts.txt", "w") as f1:
    for text in all_texts:
        f1.write(text)
        f1.write("\n")