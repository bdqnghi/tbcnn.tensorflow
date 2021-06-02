## An implementation of Tree-based Convolutional Neural Network (TBCNN) in Tensorflow

This is a Tensorflow implementation of the Tree-based Convolutional Neural Network (TBCNN) as described in the paper [Convolutional Neural Networks over Tree Structures for Programming Language Processingks, AAAI 2015] (Mou et al. - https://arxiv.org/abs/1409.5718).

Our reproduced results are much better than the results reported in the original paper. Concretely, we could get up to 97% in F1 score (compared to 94% reported in the original paper)


## Data Preparation

1. Install the required dependencies ```pip install -r requirements.txt```.

2. Download and extract the dataset and the pretrained models;

    - ```cd script```

    - Download dataset: ```python3 download_data.py  --url=https://ai4code.s3-ap-southeast-1.amazonaws.com/OJ104_pycparser_train_test_val.zip --output_path=../OJ104_pycparser_train_test_val.zip```
    
    - Download pretrained models: ```python3 download_data.py  --url=https://ai4code.s3-ap-southeast-1.amazonaws.com/OJ104_model_pycparser.zip --output_path=../OJ104_model_pycparser.zip```
    

After these steps, you can see data folder (OJ_pycparser_train_test_val) and the pretrained models (model). The data folder has been splitted into 3 subfolders train\test\val. 
Noted that the dataset is taken from the website of the original paper (https://sites.google.com/site/treebasedcnn/).

3. Preprocess the data

    - ```cd script```
    
    - ```source process_data.sh```

This step will process the AST trees, which comprises of 2 steps. First, it will convert the pycparser format into our simple tree format in the form of Python dictionary. Second, it will put the trees with similar sizes into the same bucket.



## Running the model

1. To train the model:
    - ```source tbcnn_training_script.sh```
    
2. To test the model:
    - ```source tbcnn_testing_script.sh```
  

## Tips on tuning the model
Looking at the "tbcnn_training_script.sh", there are a few parameters to consider to tune the network.

-NODE_INIT: to use node type, node token or both to initialize for the node embedding.

-NUM_CONV: the number of convolutional steps. Our experiments show that 4 usually perform the best.

-NODE_TYPE_DIM: dimension size of node type embedding. 

-NODE_TOKEN_DIM: dimension size of node token embedding.




