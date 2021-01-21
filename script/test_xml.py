import os
import codecs
import numpy as np
# from xml_util import parse_tree
# from xml_util import get_parent_map
# from xml_util import iterate_recursive
# from xml_util import get_package_name_of_node
# from util import process_srcml_source_code
# from xml_util import transform_source_code
import xml.etree.ElementTree as ET
path = "test/test.Rust.xml"

tree = ET.parse(path)

root = tree.getroot()

# print(root.tag)
# print(root)
# num_nodes = 0
# for child in tree.iter():
#     print(child.text)
#     num_nodes = num_nodes + 1

# print(num_nodes)

def _traverse_tree(root):
    num_nodes = 0

    queue = [root]

    root_token = str(root.text)
  
   
    root_json = {
        "node_type": str(root.tag),
        "node_token": str(root.text),
        "children": []
    }
    queue_json = [root_json]
    while queue:
    
        current_node = queue.pop(0)
        current_node_json = queue_json.pop(0)
        num_nodes += 1

        children = [x for x in current_node]
        queue.extend(children)

        for child in children:

            child_json = {
                "node_type": str(child.tag),
                "node_token": str(child.text),
                "children": []
            }

        current_node_json['children'].append(child_json)
        queue_json.append(child_json)

    print(num_nodes)
    # print(str(root_json))


_traverse_tree(root)  