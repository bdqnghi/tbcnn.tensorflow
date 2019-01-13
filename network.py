"""Build a CNN network that learns a convolution over a tree structure as
described in Lili Mou et al. (2015) https://arxiv.org/pdf/1409.5718.pdf"""

import math
import tensorflow as tf


def init_net(feature_size, label_size, output_size, weights, biases, aggregation_type, distributed_function):
    """Initialize an empty network."""

    with tf.name_scope('inputs'):
        nodes = tf.placeholder(tf.float32, shape=(None, None, feature_size), name='tree')
        children = tf.placeholder(tf.int32, shape=(None, None, None), name='children')

    with tf.name_scope('network'):
        conv1 = conv_layer(1, nodes, children, feature_size, weights["w_t"], weights["w_l"], weights["w_r"], biases["b_conv"])
        #conv2 = conv_layer(1, 10, conv1, children, 100)

        if aggregation_type == 0:
            print("Using max pooling...........")
            aggregation = pooling_layer(conv1)
            attention_score = None
        else:
            aggregation, attention_score = aggregation_layer(conv1, weights["w_attention"], output_size, aggregation_type, distributed_function)
        hidden = hidden_layer(aggregation, 100, label_size)

    return nodes, children, hidden, attention_score

def init_net_for_siamese(feature_size, output_size, weights, biases, aggregation_type, distributed_function):
    """Initialize an empty network."""

    with tf.name_scope("left_inputs"):
        left_nodes = tf.placeholder(tf.float32, shape=(None, None, feature_size), name='left_tree')
        left_children = tf.placeholder(tf.int32, shape=(None, None, None), name='left_children')

    with tf.name_scope("right_inputs"):
        right_nodes = tf.placeholder(tf.float32, shape=(None, None, feature_size), name='right_tree')
        right_children = tf.placeholder(tf.int32, shape=(None, None, None), name='right_children')


    left_aggregation_node, left_attention_score = extract_features(left_nodes, left_children, weights, biases, output_size, feature_size, aggregation_type, distributed_function)
    right_aggregation_node, right_attention_score = extract_features(right_nodes, right_children, weights, biases, output_size, feature_size, aggregation_type, distributed_function)

    merge_node = tf.concat([left_aggregation_node, right_aggregation_node], -1)
    hidden_node = hidden_layer(merge_node, 200, 2)

    return left_nodes, left_children, right_nodes, right_children, hidden_node, left_attention_score, right_attention_score


def init_net_for_siamese_2(feature_size, output_size, weights, biases):
    """Initialize an empty network."""

    with tf.name_scope("left_inputs"):
        left_nodes = tf.placeholder(tf.float32, shape=(None, None, feature_size), name='left_tree')
        left_children = tf.placeholder(tf.int32, shape=(None, None, None), name='left_children')

    with tf.name_scope("right_inputs"):
        right_nodes = tf.placeholder(tf.float32, shape=(None, None, feature_size), name='right_tree')
        right_children = tf.placeholder(tf.int32, shape=(None, None, None), name='right_children')

    left_mask = tf.placeholder(tf.float32, [None, None], "left_mask")
    right_mask = tf.placeholder(tf.float32, [None, None], "right_mask")

    left_conv = conv_layer(1, left_nodes, left_children, feature_size, weights["w_t"], weights["w_l"], weights["w_r"], biases["b_conv"])
    right_conv = conv_layer(1, right_nodes, right_children, feature_size, weights["w_t"], weights["w_l"], weights["w_r"], biases["b_conv"])

    logits, e = logits_op(left_conv, right_conv, left_mask, right_mask, 100)

    return left_nodes, left_children, right_nodes, right_children, logits, left_mask, right_mask, e

def extract_features(nodes, children, weights, biases, output_size, feature_size, aggregation_type, distributed_function):
    with tf.name_scope('network'):
        conv = conv_layer(1, nodes, children, feature_size, weights["w_t"], weights["w_l"], weights["w_r"], biases["b_conv"])

    if aggregation_type == 0:
        print("Using max pooling as the aggregation...........")
        aggregation = pooling_layer(conv1)
        attention_score = None
    else:
        print("Using attention with pooling as the aggregation...........")
        aggregation, attention_score = aggregation_layer(conv, weights["w_attention"], output_size, aggregation_type, distributed_function)

    return aggregation, attention_score


# build graph
def logits_op(left_conv, right_conv, left_mask, right_mask, hidden_size):
    alpha, beta, e = attend_block(left_conv, right_conv, left_mask, right_mask, hidden_size)
    v_1, v_2 = compare_block(left_conv, right_conv, alpha, beta, hidden_size)
    logits = aggregate_block(v_1, v_2, hidden_size)
    return logits, e

# feed forward unit
def feed_forward_block(inputs, scope, hidden_size):
    """
    :param inputs: tensor with shape (batch_size, seq_length, embedding_size)
    :param num_units: dimensions of each feed forward layer
    :param scope: scope name
    :return: output: tensor with shape (batch_size, hidden_size)
    """
    with tf.name_scope(scope):
       
        initializer = tf.contrib.layers.xavier_initializer()

        # inputs = tf.nn.dropout(inputs, self.dropout_keep_prob)
        outputs = tf.layers.dense(inputs, hidden_size, tf.nn.relu, kernel_initializer = initializer)
   
        # outputs = tf.nn.dropout(outputs, self.dropout_keep_prob)
        resluts = tf.layers.dense(outputs, hidden_size, tf.nn.relu, kernel_initializer = initializer)
        return resluts


# decomposable attend block ("3.1 Attend" in paper)
def attend_block(left_conv, right_conv, left_mask, right_mask, hidden_size):
    

    # Example of tensor transformation

    # left_conv = 10 x 900 x 100
    # right_conv = 10 x 1000 x 100
    
    # attetion_soft_b = 10 x 900 x 1000
    # attention_soft_a = 10 x 1000 x 900

    # beta = (10 x 900 x 1000) x (10 x 900 x 100)
    # beta = (10 x 900 x 900) x (10 x 900 x 100)

    # alpha = (10 x 1000 x 1000) x (10 x 1000 x 100)
    # alpha = (10 x 1000 x 900) x (10 x 1000 x 100)

    with tf.name_scope("attend_block"):
        F_a_bar  = feed_forward_block(left_conv, "F", hidden_size)
        F_b_bar = feed_forward_block(right_conv, "F", hidden_size)
        
        e_raw = tf.matmul(F_a_bar, tf.transpose(F_b_bar, [0, 2, 1]))

        mask = tf.multiply(tf.expand_dims(left_mask, 2), tf.expand_dims(right_mask, 1))
        
        e = tf.multiply(e_raw, mask)
        attentionSoft_a = tf.exp(e - tf.reduce_max(e_raw, axis=2, keepdims=True))
        attentionSoft_b = tf.exp(e - tf.reduce_max(e_raw, axis=1, keepdims=True))
        
        attentionSoft_a = tf.multiply(attentionSoft_a, tf.expand_dims(left_mask, 1))
        attentionSoft_b = tf.multiply(attentionSoft_b, tf.expand_dims(right_mask, 2))

        attentionSoft_a = tf.divide(attentionSoft_a, tf.reduce_sum(attentionSoft_a, axis=2, keepdims=True))
        attentionSoft_b = tf.divide(attentionSoft_b, tf.reduce_sum(attentionSoft_b, axis=1, keepdims=True))
        attentionSoft_a = tf.multiply(attentionSoft_a, mask)
        attentionSoft_b = tf.transpose(tf.multiply(attentionSoft_b, mask), [0, 2, 1])

        alpha = tf.matmul(attentionSoft_a, right_conv)
        beta = tf.matmul(attentionSoft_b, left_conv)
        
        return alpha, beta, e


 # compare block ("3.2 Compare" in paper)
def compare_block(left_conv, right_conv, alpha, beta, hidden_size):
    """
    :param alpha: context vectors, tensor with shape (batch_size, seq_length, embedding_size)
    :param beta: context vectors, tensor with shape (batch_size, seq_length, embedding_size)
    :param scope: scope name
    a_beta, b_alpha: concat of [embeded_premise, beta], [embeded_hypothesis, alpha], tensor with shape (batch_size, seq_length, 2 * embedding_size)
    :return: v_1: compare the aligned phrases, output of feed forward layer (G), tensor with shape (batch_size, seq_length, hidden_size)
             v_2: compare the aligned phrases, output of feed forward layer (G), tensor with shape (batch_size, seq_length, hidden_size)
    """
    with tf.name_scope("compare_block"):
        a_beta = tf.concat([left_conv, beta], axis=2)
        b_alpha = tf.concat([right_conv, alpha], axis=2)

        v_1 = feed_forward_block(a_beta, "G" ,hidden_size)
        v_2 = feed_forward_block(b_alpha, "G" ,hidden_size)
     
        return v_1, v_2

# composition block ("3.3 Aggregate" in paper)
def aggregate_block(v_1, v_2, hidden_size):
    """
    :param v_1: compare the aligned phrases, output of feed forward layer (G), tensor with shape (batch_size, seq_length, hidden_size)
    :param v_2: compare the aligned phrases, output of feed forward layer (G), tensor with shape (batch_size, seq_length, hidden_size)
    :param scope: scope name
    v1_sum, v2_sum: sum of the compared phrases (axis = seq_length), tensor with shape (batch_size, hidden_size)
    v: concat of v1_sum, v2_sum, tensor with shape (batch_size, 2 * hidden_size)
    ff_outputs: output of feed forward layer (H), tensor with shape (batch_size, hidden_size)
    :return: y_hat: output of a linear layer, tensor with shape (batch_size, n_classes)
    """
    with tf.name_scope("aggregate_block"):
        # v1 = \sum_{i=1}^l_a v_{1,i}
        # v2 = \sum_{j=1}^l_b v_{2,j} (4)
        v1_sum = tf.reduce_sum(v_1, axis=1)
        v2_sum = tf.reduce_sum(v_2, axis=1)
    
        v = tf.concat([v1_sum, v2_sum], axis=1)

        ff_outputs = feed_forward_block(v, "H", hidden_size)
        
        y_hat = tf.layers.dense(ff_outputs, 2)
            
        return y_hat


def conv_layer(num_conv, nodes, children, feature_size, w_t, w_r, w_l, b_conv):
    """Creates a convolution layer with num_conv convolutions merged together at
    the output. Final output will be a tensor with shape
    [batch_size, num_nodes, output_size * num_conv]"""

    with tf.name_scope('conv_layer'):
        nodes = [           
            conv_step(nodes, children, feature_size, w_t, w_r, w_l, b_conv)
            for _ in range(num_conv)
        ]
        return tf.concat(nodes, axis=2)

def conv_step(nodes, children, feature_size, w_t, w_r, w_l, b_conv):
    """Convolve a batch of nodes and children.

    Lots of high dimensional tensors in this function. Intuitively it makes
    more sense if we did this work with while loops, but computationally this
    is more efficient. Don't try to wrap your head around all the tensor dot
    products, just follow the trail of dimensions.
    """
    with tf.name_scope('conv_step'):
        # nodes is shape (batch_size x max_tree_size x feature_size)
        # children is shape (batch_size x max_tree_size x max_children)

        with tf.name_scope('trees'):
            # children_vectors will have shape
            # (batch_size x max_tree_size x max_children x feature_size)
            children_vectors = children_tensor(nodes, children, feature_size)

            # add a 4th dimension to the nodes tensor
            nodes = tf.expand_dims(nodes, axis=2)
            # tree_tensor is shape
            # (batch_size x max_tree_size x max_children + 1 x feature_size)
            tree_tensor = tf.concat([nodes, children_vectors], axis=2, name='trees')

        with tf.name_scope('coefficients'):
            # coefficient tensors are shape (batch_size x max_tree_size x max_children + 1)
            c_t = eta_t(children)
            c_r = eta_r(children, c_t)
            c_l = eta_l(children, c_t, c_r)

            # concatenate the position coefficients into a tensor
            # (batch_size x max_tree_size x max_children + 1 x 3)
            coef = tf.stack([c_t, c_r, c_l], axis=3, name='coef')

        with tf.name_scope('weights'):
            # stack weight matrices on top to make a weight tensor
            # (3, feature_size, output_size)
            weights = tf.stack([w_t, w_r, w_l], axis=0)

        with tf.name_scope('combine'):
            batch_size = tf.shape(children)[0]
            max_tree_size = tf.shape(children)[1]
            max_children = tf.shape(children)[2]

            # reshape for matrix multiplication
            x = batch_size * max_tree_size
            y = max_children + 1
            result = tf.reshape(tree_tensor, (x, y, feature_size))
            coef = tf.reshape(coef, (x, y, 3))
            result = tf.matmul(result, coef, transpose_a=True)
            result = tf.reshape(result, (batch_size, max_tree_size, 3, feature_size))

            # output is (batch_size, max_tree_size, output_size)
            result = tf.tensordot(result, weights, [[2, 3], [0, 1]])

            # output is (batch_size, max_tree_size, output_size)
            return tf.nn.tanh(result + b_conv, name='conv')


def children_tensor(nodes, children, feature_size):
    """Build the children tensor from the input nodes and child lookup."""
    with tf.name_scope('children_tensor'):
        max_children = tf.shape(children)[2]
        batch_size = tf.shape(nodes)[0]
        num_nodes = tf.shape(nodes)[1]

        # replace the root node with the zero vector so lookups for the 0th
        # vector return 0 instead of the root vector
        # zero_vecs is (batch_size, num_nodes, 1)
        zero_vecs = tf.zeros((batch_size, 1, feature_size))
        # vector_lookup is (batch_size x num_nodes x feature_size)
        vector_lookup = tf.concat([zero_vecs, nodes[:, 1:, :]], axis=1)
        # children is (batch_size x num_nodes x num_children x 1)
        children = tf.expand_dims(children, axis=3)
        # prepend the batch indices to the 4th dimension of children
        # batch_indices is (batch_size x 1 x 1 x 1)
        batch_indices = tf.reshape(tf.range(0, batch_size), (batch_size, 1, 1, 1))
        # batch_indices is (batch_size x num_nodes x num_children x 1)
        batch_indices = tf.tile(batch_indices, [1, num_nodes, max_children, 1])
        # children is (batch_size x num_nodes x num_children x 2)
        children = tf.concat([batch_indices, children], axis=3)
        # output will have shape (batch_size x num_nodes x num_children x feature_size)
        # NOTE: tf < 1.1 contains a bug that makes backprop not work for this!
        return tf.gather_nd(vector_lookup, children, name='children')

def eta_t(children):
    """Compute weight matrix for how much each vector belongs to the 'top'"""
    with tf.name_scope('coef_t'):
        # children is shape (batch_size x max_tree_size x max_children)
        batch_size = tf.shape(children)[0]
        max_tree_size = tf.shape(children)[1]
        max_children = tf.shape(children)[2]
        # eta_t is shape (batch_size x max_tree_size x max_children + 1)
        return tf.tile(tf.expand_dims(tf.concat(
            [tf.ones((max_tree_size, 1)), tf.zeros((max_tree_size, max_children))],
            axis=1), axis=0,
        ), [batch_size, 1, 1], name='coef_t')

def eta_r(children, t_coef):
    """Compute weight matrix for how much each vector belogs to the 'right'"""
    with tf.name_scope('coef_r'):
        # children is shape (batch_size x max_tree_size x max_children)
        children = tf.cast(children, tf.float32)
        batch_size = tf.shape(children)[0]
        max_tree_size = tf.shape(children)[1]
        max_children = tf.shape(children)[2]

        # num_siblings is shape (batch_size x max_tree_size x 1)
        num_siblings = tf.cast(
            tf.count_nonzero(children, axis=2, keep_dims=True),
            dtype=tf.float32
        )
        # num_siblings is shape (batch_size x max_tree_size x max_children + 1)
        num_siblings = tf.tile(
            num_siblings, [1, 1, max_children + 1], name='num_siblings'
        )
        # creates a mask of 1's and 0's where 1 means there is a child there
        # has shape (batch_size x max_tree_size x max_children + 1)
        mask = tf.concat(
            [tf.zeros((batch_size, max_tree_size, 1)),
             tf.minimum(children, tf.ones(tf.shape(children)))],
            axis=2, name='mask'
        )

        # child indices for every tree (batch_size x max_tree_size x max_children + 1)
        child_indices = tf.multiply(tf.tile(
            tf.expand_dims(
                tf.expand_dims(
                    tf.range(-1.0, tf.cast(max_children, tf.float32), 1.0, dtype=tf.float32),
                    axis=0
                ),
                axis=0
            ),
            [batch_size, max_tree_size, 1]
        ), mask, name='child_indices')

        # weights for every tree node in the case that num_siblings = 0
        # shape is (batch_size x max_tree_size x max_children + 1)
        singles = tf.concat(
            [tf.zeros((batch_size, max_tree_size, 1)),
             tf.fill((batch_size, max_tree_size, 1), 0.5),
             tf.zeros((batch_size, max_tree_size, max_children - 1))],
            axis=2, name='singles')

        # eta_r is shape (batch_size x max_tree_size x max_children + 1)
        return tf.where(
            tf.equal(num_siblings, 1.0),
            # avoid division by 0 when num_siblings == 1
            singles,
            # the normal case where num_siblings != 1
            tf.multiply((1.0 - t_coef), tf.divide(child_indices, num_siblings - 1.0)),
            name='coef_r'
        )

def eta_l(children, coef_t, coef_r):
    """Compute weight matrix for how much each vector belongs to the 'left'"""
    with tf.name_scope('coef_l'):
        children = tf.cast(children, tf.float32)
        batch_size = tf.shape(children)[0]
        max_tree_size = tf.shape(children)[1]
        # creates a mask of 1's and 0's where 1 means there is a child there
        # has shape (batch_size x max_tree_size x max_children + 1)
        mask = tf.concat(
            [tf.zeros((batch_size, max_tree_size, 1)),
                tf.minimum(children, tf.ones(tf.shape(children)))],
            axis=2,
            name='mask'
        )

        # eta_l is shape (batch_size x max_tree_size x max_children + 1)
        return tf.multiply(
            tf.multiply((1.0 - coef_t), (1.0 - coef_r)), mask, name='coef_l'
        )

def aggregation_layer(conv, w_attention, output_size, aggregation_type, distributed_function):
    # conv is (batch_size, max_tree_size, output_size)
    with tf.name_scope("global_attention"):
        batch_size = tf.shape(conv)[0]
        max_tree_size = tf.shape(conv)[1]

        # (batch_size * max_tree_size, output_size)
        flat_conv = tf.reshape(conv, [-1, output_size])
        aggregated_vector = tf.matmul(flat_conv, w_attention)

        attention_score = tf.reshape(aggregated_vector, [-1, max_tree_size, 1])

        """A note here: softmax will distributed the weights to all of the nodes (sum of node weghts = 1),
        an interesting finding is that for some nodes, the attention score will be very very small, i.e e-12, 
        thus making parts of aggregated vector becomes near zero and affect on the learning (very slow convergence
        - Better to use sigmoid"""

        if distributed_function == 0:
            attention_weights = tf.nn.softmax(attention_score, dim=1)
        if distributed_function == 1:
            attention_weights = tf.nn.sigmoid(attention_score)

        # TODO: reduce_max vs reduce_sum vs reduce_mean
        if aggregation_type == 1:
            print("Using tf.reduce_sum...........")
            weighted_average_nodes = tf.reduce_sum(tf.multiply(conv, attention_weights), axis=1)
        if aggregation_type == 2:
            print("Using tf.reduce_max...........")
            weighted_average_nodes = tf.reduce_max(tf.multiply(conv, attention_weights), axis=1)
        if aggregation_type == 3:
            print("Using tf.reduce_mean...........")
            weighted_average_nodes = tf.reduce_mean(tf.multiply(conv, attention_weights), axis=1)

        return weighted_average_nodes, attention_weights

def pooling_layer(nodes):
    """Creates a max dynamic pooling layer from the nodes."""
    with tf.name_scope("pooling"):
        pooled = tf.reduce_max(nodes, axis=1)
        return pooled

def hidden_layer(pooled, input_size, output_size):
    """Create a hidden feedforward layer."""
    with tf.name_scope("hidden"):
        initializer = tf.contrib.layers.xavier_initializer()
        weights = tf.Variable(initializer([input_size, output_size]), name='weights')
        biases = tf.Variable(initializer([output_size,]), name='biases')
        return tf.nn.leaky_relu(tf.matmul(pooled, weights) + biases)

def loss_layer(logits_node, label_size):
    """Create a loss layer for training."""

    labels = tf.placeholder(tf.int32, (None, label_size,))

    with tf.name_scope('loss_layer'):
        cross_entropy = tf.nn.softmax_cross_entropy_with_logits(
            labels=labels, logits=logits_node, name='cross_entropy'
        )

        loss = tf.reduce_mean(cross_entropy, name='cross_entropy_mean')

        return labels, loss

def out_layer(logits_node):
    """Apply softmax to the output layer."""
    with tf.name_scope('output'):
        return tf.nn.softmax(logits_node)