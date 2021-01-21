import math
import tensorflow as tf
import numpy as np
from keras_radam.training import RAdamOptimizer
import sys
from pathlib import Path
# To import upper level modules
sys.path.append(str(Path('.').absolute().parent))
from util.data.data_processor.base_data_processor import DataProcessor
from tensorflow import keras

class BaseLayer(keras.Model):
    def __init__(self, opt):
        data_processor = DataProcessor()
        self.node_type_lookup = data_processor.load_node_type_vocab(opt.node_type_vocabulary_path)
        self.node_token_lookup = data_processor.load_node_type_vocab(opt.token_vocabulary_path)

    def minimize_loss(loss, lr):
        loss_node = loss
        optimizer = RAdamOptimizer(lr)

        update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS)
        with tf.control_dependencies(update_ops):
            training_point = optimizer.minimize(loss_node)

        return optimizer