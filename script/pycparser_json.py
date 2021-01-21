#------------------------------------------------------------------------------
# pycparser: c_json.py
#
# by Michael White (@mypalmike)
#
# This example includes functions to serialize and deserialize an ast
# to and from json format. Serializing involves walking the ast and converting
# each node from a python Node object into a python dict. Deserializing
# involves the opposite conversion, walking the tree formed by the
# dict and converting each dict into the specific Node object it represents.
# The dict itself is serialized and deserialized using the python json module.
#
# The dict representation is a fairly direct transformation of the object
# attributes. Each node in the dict gets one metadata field referring to the
# specific node class name, _nodetype. Each local attribute (i.e. not linking
# to child nodes) has a string value or array of string values. Each child
# attribute is either another dict or an array of dicts, exactly as in the
# Node object representation. The "coord" attribute, representing the
# node's location within the source code, is serialized/deserialized from
# a Coord object into a string of the format "filename:line[:column]".
#
# Example TypeDecl node, with IdentifierType child node, represented as a dict:
#     "type": {
#         "_nodetype": "TypeDecl",
#         "coord": "c_files/funky.c:8",
#         "declname": "o",
#         "quals": [],
#         "type": {
#             "_nodetype": "IdentifierType",
#             "coord": "c_files/funky.c:8",
#             "names": [
#                 "char"
#             ]
#         }
#     }
#------------------------------------------------------------------------------
from __future__ import print_function

import json
import sys
import re

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
#
sys.path.extend(['.', '..'])

from pycparser import parse_file, c_ast
from pycparser.plyparser import Coord


RE_CHILD_ARRAY = re.compile(r'(.*)\[(.*)\]')
RE_INTERNAL_ATTR = re.compile('__.*__')


class CJsonError(Exception):
    pass


def memodict(fn):
    """ Fast memoization decorator for a function taking a single argument """
    class memodict(dict):
        def __missing__(self, key):
            ret = self[key] = fn(key)
            return ret
    return memodict().__getitem__


@memodict
def child_attrs_of(klass):
    """
    Given a Node class, get a set of child attrs.
    Memoized to avoid highly repetitive string manipulation
    """
    non_child_attrs = set(klass.attr_names)
    all_attrs = set([i for i in klass.__slots__ if not RE_INTERNAL_ATTR.match(i)])
    return all_attrs - non_child_attrs


def to_dict(node):
    """ Recursively convert an ast into dict representation. """
    klass = node.__class__

    result = {}

    # Metadata
    result['_nodetype'] = klass.__name__

    # Local node attributes
    for attr in klass.attr_names:
        print("$$$$")
        print(attr)
        print(getattr(node, attr))
        result[attr] = getattr(node, attr)

    # Child attributes
    for child_name, child in node.children():
        # Child strings are either simple (e.g. 'value') or arrays (e.g. 'block_items[1]')
        match = RE_CHILD_ARRAY.match(child_name)
        print("*********")
        print("Child name : " + str(child_name))
        print(child.__class__.__name__)
        if match:
            print("--------")
            array_name, array_index = match.groups()
            array_index = int(array_index)
            print("Array name : " + str(array_name))
            print("Array index : " + str(array_index))
            # arrays come in order, so we verify and append.
            result[array_name] = result.get(array_name, [])
            if array_index != len(result[array_name]):
                raise CJsonError('Internal ast error. Array {} out of order. '
                    'Expected index {}, got {}'.format(
                    array_name, len(result[array_name]), array_index))
            
            print(to_dict(child))
            result[array_name].append(to_dict(child))
        else:
            print("HERE")
            print(match)
            result[child_name] = to_dict(child)

    # Any child attributes that were missing need "None" values in the json.
    for child_attr in child_attrs_of(klass):
        if child_attr not in result:
            result[child_attr] = None

    return result

def to_dict_3(node):
    """ Recursively convert an ast into dict representation. """
    klass = node.__class__

    result = {}

    result["node_type"] = klass.__name__
    result["node_token"] = ""
    for attr in klass.attr_names:
        if attr == "name":
            result["node_token"] = getattr(node, attr)
        if attr == "op":
            result["node_token"] = getattr(node, attr)
    result["children"] = []
    
    for child_name, child in node.children():       
        result["children"].append(to_dict_3(child))
    return result


def to_dict_2(root):
    """ Recursively convert an ast into dict representation. """

    num_nodes = 0
    klass = root.__class__
    queue = [root]

    root_json = {
        "node_type": klass.__name__,
        "node_token": "",
        "children": []
    } 

    for attr in klass.attr_names:
        attribute = getattr(root, attr)
        if attr == "name" or attr == "op" or attr == "declname":
            root_json["node_token"] = attribute
        if attr == "names":
            root_json["node_token"] = attribute[0]
    

    queue_json = [root_json]
    while queue:
        current_node = queue.pop(0)
        current_node_json = queue_json.pop(0)
        num_nodes += 1

        # children = [child for child_name, child in root.children()]
        # queue.extend(children)

        # Child attributes
        for child_name, child in current_node.children():
            # Child strings are either simple (e.g. 'value') or arrays (e.g. 'block_items[1]')
            child_json = {
                "node_type": child.__class__.__name__,
                "node_token": "",
                "children": []
            }

            for attr in child.__class__.attr_names:
                attribute = getattr(child, attr)
                if attr == "name" or attr == "op" or attr == "declname":
                    child_json["node_token"] = attribute
                if attr == "names":
                    child_json["node_token"] = attribute[0]

            current_node_json['children'].append(child_json)
            queue_json.append(child_json)
            queue.append(child)
     
    return root_json


def to_json(node, **kwargs):
    """ Convert ast node to json string """
    return json.dumps(to_dict(node), **kwargs)


def file_to_dict(filename):
    """ Load C file into dict representation of ast """
    ast = parse_file(filename, use_cpp=True)
    print(ast.show())
    dict_rep = to_dict_2(ast)
    return dict_rep

def file_to_json(filename, **kwargs):
    """ Load C file into json string representation of ast """
    ast = parse_file(filename, use_cpp=True)
    return to_json(ast, **kwargs)


def _parse_coord(coord_str):
    """ Parse coord string (file:line[:column]) into Coord object. """
    if coord_str is None:
        return None

    vals = coord_str.split(':')
    vals.extend([None] * 3)
    filename, line, column = vals[:3]
    return Coord(filename, line, column)


def _convert_to_obj(value):
    """
    Convert an object in the dict representation into an object.
    Note: Mutually recursive with from_dict.
    """
    value_type = type(value)
    if value_type == dict:
        return from_dict(value)
    elif value_type == list:
        return [_convert_to_obj(item) for item in value]
    else:
        # String
        return value


def from_dict(node_dict):
    """ Recursively build an ast from dict representation """
    class_name = node_dict.pop('_nodetype')

    klass = getattr(c_ast, class_name)

    # Create a new dict containing the key-value pairs which we can pass
    # to node constructors.
    objs = {}
    for key, value in node_dict.items():
        if key == 'coord':
            objs[key] = _parse_coord(value)
        else:
            objs[key] = _convert_to_obj(value)

    # Use keyword parameters, which works thanks to beautifully consistent
    # ast Node initializers.
    return klass(**objs)


def from_json(ast_json):
    """ Build an ast from json string representation """
    return from_dict(json.loads(ast_json))


#------------------------------------------------------------------------------
if __name__ == "__main__":
    file_name = "../OJ_raw_train_test_val/train/1/14.c"
    ast_dict = file_to_dict(file_name)
    print(ast_dict)

    # ast = parse_file(file_name, use_cpp=True)
    # print(ast.show())
    # ast = from_dict(ast_dict)
    # print(to_json(ast, sort_keys=True, indent=4))
    