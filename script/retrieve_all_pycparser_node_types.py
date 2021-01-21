import sys
from pathlib import Path
# To import upper level modules
sys.path.append(str(Path('.').absolute().parent))
import os
import re
from pycparser import parse_file, c_ast
from util import identifier_splitting
import re


excluded_tokens = [",","{",";","}",")","(",'"',"'","`",""," ","[]","[","]","/",":",".","''","'.'","b", "\\", "'['", "']","''","_","__"]

def process_token(token):
    for t in excluded_tokens:
        token = token.replace(t, "")
        # token = re.sub(r'[^\w]', ' ', token)
    return token

def remove_noisy_tokens(tokens):
    temp_tokens = []
    for t in tokens:
        t = process_token(t)
        if t:
            temp_tokens.append(t)
    return temp_tokens



def parse_tree(root):
    """ Recursively convert an ast into dict representation. """

    num_nodes = 0
    klass = root.__class__
    queue = [root]

    types = []
    tokens = []
    root_json = {
        "node_type": klass.__name__,
        "children": []
    }

    root_token = ""
    for attr in klass.attr_names:
        attribute = getattr(root, attr)
        if attr == "name" or attr == "op" or attr == "declname":
            root_token = attribute
        if attr == "names":
            root_token = attribute[0]

    root_token = process_token(root_token)
    root_sub_tokens = identifier_splitting.split_identifier_into_parts(root_token)
    root_sub_tokens = remove_noisy_tokens(root_sub_tokens)

    tokens.extend(root_sub_tokens)
    types.extend(klass.__name__)

    queue_json = [root_json]
    while queue:
        current_node = queue.pop(0)
        current_node_json = queue_json.pop(0)
        num_nodes += 1

        for child_name, child in current_node.children():
            # Child strings are either simple (e.g. 'value') or arrays (e.g. 'block_items[1]')
            child_json = {
                "node_type": child.__class__.__name__,
                "children": []
            }

            child_token = ""
            for attr in child.__class__.attr_names:
                attribute = getattr(child, attr)
                if attr == "name" or attr == "op" or attr == "declname":
                    child_token = attribute
                if attr == "names":
                    child_token = attribute[0]


            child_sub_tokens = identifier_splitting.split_identifier_into_parts(str(child_token))
            child_sub_tokens = remove_noisy_tokens(child_sub_tokens)
            # print("Sub tokens : " + str(child_sub_tokens))

            current_node_json["children"].append(child_json)
            queue_json.append(child_json)
            queue.append(child)

            types.extend(child.__class__.__name__)
            tokens.extend(child_sub_tokens)
     
    return root_json, types, tokens


directory = "../OJ_raw_train_test_val"
all_types = []
all_tokens = []
count = 0
for subdir , dirs, files in os.walk(directory): 
    for file in files:
        if file.endswith(".c"): 
            file_path = os.path.join(subdir,file)
            print(file_path)
            ast = parse_file(file_path, use_cpp=True)
            ast_dict, types, tokens = parse_tree(ast)
            # print(all_types)
            # print(ast_dict)
            print(tokens)
            all_types.extend(types)
            all_tokens.extend(tokens)

# all_types = list(set(all_types))
# with open("pycparser_types.txt", "w") as f:
#     for t in all_types:
#         f.write(t)
#         f.write("\n")      


all_tokens = list(set(all_tokens))
with open("pycparser_tokens.txt", "w") as f:
    for t in all_tokens:
        f.write(t)
        f.write("\n")     

