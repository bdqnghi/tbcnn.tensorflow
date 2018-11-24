# Tree-based Convolutional Neural Network with Attention Unit 
A modified version of Tree-based convolutional neural network using Global Attention vector in the Aggregation Layer instead of the Dynamic Pooling

## How to run

First, run:
```
bash script.sh
```
to extract the pretrained embedding and download the docker image of f-ast tool.

For general training and testing:
```
python3 main.py --model_path "model/github_50_cpp_new" --n_classes 50 --training
```

For single file testing:
```
python3 live_test.py --model_path "model/github_50_cpp_new" --n_classes 50 --test_file "live_test/github_cpp/26/10.cpp"
```
There is a pretrained model in "model/github_50_cpp_new" for the Github C++ dataset. "The live_test" directory contains the  raw programming files for testing. Once running the above command, there will be 8 files generated in the same directory of the test file, e.g in this case, they are: 
- 10.pb: protobuf format of the AST
- 10.pkl: pickle format of the protobuf
- 10_ast.txt: string format of the AST, one can view the actual AST in this file
- 10_raw_attention_without_node_type.csv: a csv file contains the attention score for each node from the softmax layer (node_id, attention, score)
- 10_raw_attention_with_node_type.csv: a csv file contains the attention score for each node from the softmax layer with the node type (node_id, node_type, score)
- 10_scaled_attention_without_node_type.csv:  a csv file contains the attention score after scaled with Min-Max scaling to 0-1 (node_id, attention, score)
- 10_scaled_attention_with_node_type.csv: a csv file contains the attention score after scaled with Min-Max scaling to 0-1, with node type (node_id, attention, score)
- 10_normal.html: the visual reprentation of the important nodes by just taking the raw attention to visualize
- 10_accumulation.html: the visual reprentation of the important nodes, by spreading the score of a parent node to its children
and visualize on the accumulated score

### Note

- If you run any of the above scripts for the first time, it may take a while since the code needs to load the data and do the caching. From the second time, it will be much faster, since the data will be loaded from the cache.
- One can check the node type in the file src_node_map.tsv
