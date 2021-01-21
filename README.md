## An implementation of Tree-based Convolutional Neural Network (TBCNN) in Tensorflow

This is a Tensorflow implementation of the Tree-based Convolutional Neural Network (TBCNN) as described in the paper [Convolutional Neural Networks over Tree Structures for Programming Language Processingks, AAAI 2015](https://arxiv.org/abs/1409.5718).

Our reproduced results are much better than the results reported in the original paper. Concretely, we could get up to 97.5% in F1 score (compared to 94% reported in the original paper)


## Usage

1. Install the required dependencies ```pip install -r requirements.txt```.

2. Download and extract the dataset ```python3 download_data.py```. 

  -```cd script```

  -```python3 download_data.py```. 

After this step, you can see OJ_data folder, noted that this data has been parsed into SRCML-based AST (https://www.srcml.org/) as protobuf format.

3. To train the model:
  - Run ```python3 mains.py --training```
