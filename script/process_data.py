import sys
from pathlib import Path
# To import upper level modules
sys.path.append(str(Path('.').absolute().parent))

from util.data.data_processor.pycparser_data_processor import PycParserDataProcessor
from util.data.data_processor.treesitter_c_data_processor import TreeSitterCDataProcessor
from util.data.data_processor.srcml_data_processor import SrcmlDataProcessor

import argparse

def parse_arguments(): 
    parser = argparse.ArgumentParser()
    parser.add_argument('--data_path', default="../OJ104_pycparser_train_test_val/val")
    parser.add_argument('--node_type_vocab_path',default="../vocab/pycparser/node_type/type.txt")
    parser.add_argument('--node_token_vocab_path', default="../vocab/pycparser/node_token/token.txt")
    parser.add_argument('--parser', type=str, default="pycparser", help="pycparser, treesitterc, srcml")
    opt = parser.parse_args(),
    return opt

def main(opt):
    data_path = opt.data_path
    node_type_vocab_path = opt.node_type_vocab_path
    node_token_vocab_path = opt.node_token_vocab_path
    parser = opt.parser
    
    if parser == "pycparser":
        processor = PycParserDataProcessor(node_type_vocab_path, node_token_vocab_path, data_path, parser)
    if parser == "treesitterc":
        processor = TreeSitterCDataProcessor(node_type_vocab_path, node_token_vocab_path, data_path, parser)
    if parser == "srcml":
        processor = SrcmlDataProcessor(node_type_vocab_path, node_token_vocab_path, data_path, parser)

if __name__ == "__main__":
    opt = parse_arguments()
    main(opt[0])
   