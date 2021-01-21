from __future__ import print_function
import argparse
import sys

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_ast, parse_file


# def parse(sroot):
#     num_nodes = 0

#     queue = [root]

#     root_json = {
#         "node_type": str(root.tag),
#         "children": []
#     }
    
#     queue_json = [root_json]
#     while queue:
    
#         current_node = queue.pop(0)
#         current_node_json = queue_json.pop(0)
#         num_nodes += 1

#         children = [x for x in current_node]
#         queue.extend(children)

#         for child in children:

#             child_json = {
#                 "node_type": str(child.tag),
#                 "children": []
#             }

#             tree_tokens.extend(child_sub_tokens)

#             current_node_json['children'].append(child_json)
#             queue_json.append(child_json)

#     return root_json, tree_tokens, num_nodes


if __name__ == "__main__":
    # argparser = argparse.ArgumentParser('Dump AST')
    # argparser.add_argument('filename', help='name of file to parse')
    # argparser.add_argument('--coord', help='show coordinates in the dump',
    #                        action='store_true')
    # args = argparser.parse_args()

    # ast = parse_file(args.filename, use_cpp=False)

    ast = parse_file("../OJ_raw_train_test_val/test/1/1001.c")

    # ast.show()

    function_body = ast.ext[2].body.block_items[0]

    print(function_body.__name__)