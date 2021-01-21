import math
import tensorflow as tf

from .tbcnn import TBCNN
import numpy as np


class TreeCaps(TBCNN):
    def __init__(self, opt):
        super().__init__(opt)
        self.top_a = opt.top_a

        self.static_caps_num_caps = int((self.num_conv*self.node_dim/opt.static_caps_output_dimension)*self.top_a)
        self.static_caps_output_dimension = opt.static_caps_output_dimension
        self.code_caps_num_caps = opt.label_size
        self.code_caps_output_dimension = opt.code_caps_output_dimension
        
        self.iter_routing = 3
        self.init_treecaps_params()
    
    def init_treecaps_params(self):

        with tf.compat.v1.name_scope('treecaps_params'):

            shape_of_weight_dynamic_routing = [1, self.static_caps_num_caps, self.code_caps_output_dimension * self.code_caps_num_caps, self.static_caps_output_dimension, 1]
            shape_of_bias_dynamic_routing = [1, 1, self.code_caps_num_caps, self.code_caps_output_dimension, 1]

            self.weights["w_dynamic_routing_code_caps"] = tf.Variable(tf.compat.v1.keras.initializers.VarianceScaling(scale=1.0, mode="fan_avg", distribution="uniform")(shape_of_weight_dynamic_routing), name="w_dynamic_routing_code_caps")
            self.weights["b_dynamic_routing_code_caps"] = tf.Variable(tf.zeros(shape_of_bias_dynamic_routing), name='b_dynamic_routing_code_caps')

    def feed_forward(self):
        with tf.compat.v1.name_scope('treecaps_network'):  
            self.all_tbcnn_conv_slices, self.last_conv_output = self.convolve_tree_based_cnn()
            """The Primary Variable Capsule Layer."""
            # shape = (1, batch_size x max_tree_size, num_output, num_conv)
            # Example with batch size = 12: shape = (12, 48, 128, 8)
            # Example with batch size = 1: shape = (1, 48, 128, 8)
            self.primary_variable_caps = self.primary_variable_capsule_layer(self.all_tbcnn_conv_slices)

            num_nodes = tf.shape(self.primary_variable_caps)[1]
            self.static_caps = self.vts_routing(self.primary_variable_caps, 
                                                self.batch_size, 
                                                self.static_caps_num_caps, self.top_a, 
                                                self.node_dim, 
                                                self.num_conv,
                                                self.static_caps_output_dimension)
            # self.test3 = self.static_caps
            self.static_caps = tf.reshape(self.static_caps, shape=(self.batch_size, -1, 1, self.static_caps_output_dimension, 1))
            self.code_caps = self.dynamic_routing(self.weights["w_dynamic_routing_code_caps"], 
                                                self.weights["b_dynamic_routing_code_caps"], self.static_caps,
                                                self.static_caps_num_caps, 
                                                output_num_caps=self.code_caps_num_caps,
                                                output_dimension=self.code_caps_output_dimension)
          
            # batch size = 12: (12, num_class_cap, 50, 1)

            self.code_caps = tf.squeeze(self.code_caps, axis=1)
            
            # # (12, 10, 1, 1)
            # # """Obtaining the classification output."""
            self.v_length = tf.sqrt(tf.compat.v1.reduce_sum(tf.square(self.code_caps),axis=2, keepdims=True) + 1e-9)
            self.code_caps_prob = tf.reshape(self.v_length,(-1,self.label_size))
            self.softmax = tf.nn.softmax(self.code_caps_prob)
            self.loss = self.margin_loss(self.code_caps_prob, self.placeholders["labels"])

    def dynamic_routing(self, w_dynamic_routing, b_dynamic_routing, primary_static_caps, static_caps_num_caps, output_num_caps=10, output_dimension=8):
        """The Dynamic Routing Algorithm proposed by Sabour et al."""
        
        delta_IJ = tf.zeros([self.batch_size, self.static_caps_num_caps, output_num_caps, 1, 1], dtype=tf.dtypes.float32)

        primary_static_caps = tf.tile(primary_static_caps, [1, 1, output_dimension * output_num_caps, 1, 1])
        
        u_hat = tf.reduce_sum(w_dynamic_routing * primary_static_caps, axis=3, keepdims=True)

        u_hat = tf.reshape(u_hat, shape=[-1, self.static_caps_num_caps, output_num_caps, output_dimension, 1])
        
        u_hat_stopped = tf.stop_gradient(u_hat, name='stop_gradient')

        for r_iter in range(self.iter_routing):
            with tf.compat.v1.variable_scope('iter_' + str(r_iter)):
                gamma_IJ = tf.nn.softmax(delta_IJ, axis=2)

                if r_iter == self.iter_routing - 1:
                    s_J = tf.multiply(gamma_IJ, u_hat)
                    s_J = tf.reduce_sum(s_J, axis=1, keepdims=True) + b_dynamic_routing
                    v_J = self.squash(s_J)
                elif r_iter < self.iter_routing - 1:  # Inner iterations, do not apply backpropagation
                    s_J = tf.multiply(gamma_IJ, u_hat_stopped)
                    s_J = tf.reduce_sum(s_J, axis=1, keepdims=True) + b_dynamic_routing
                    v_J = self.squash(s_J)
                    v_J_tiled = tf.tile(v_J, [1,self.static_caps_num_caps, 1, 1, 1])
                    u_produce_v = tf.reduce_sum(u_hat_stopped * v_J_tiled, axis=3, keepdims=True)
                    delta_IJ += u_produce_v
        return(v_J)

    def primary_variable_capsule_layer(self, conv_output):
        primary_variable_caps= tf.concat(conv_output, axis=-1)
        return primary_variable_caps


    def squash(self, vector):
        vec_squared_norm = tf.compat.v1.reduce_sum(tf.square(vector), -2, keepdims=True)
        scalar_factor = vec_squared_norm / (1 + vec_squared_norm) / tf.sqrt(vec_squared_norm + 1e-9)
        vec_squashed = scalar_factor * vector  # element-wise
        return(vec_squashed)


   
    def vts_routing(self, primary_variable_caps, batch_size, static_caps_num_caps, top_a, node_dim, input_dimension=4, output_dimension=4):
        """The proposed Variable-to-Static Routing Algorithm."""
        # primary_variable_caps = (batch_size, max_tree_size, node_dim, input_dimension)
        max_tree_size = tf.shape(input=primary_variable_caps)[1]

      
        alpha_IJ_shape = (int(static_caps_num_caps/top_a)*max_tree_size, static_caps_num_caps)
        alpha_IJ = tf.zeros(alpha_IJ_shape, dtype=tf.float32)
        # shape = (batch size, input_dimension, node_dim, tree_size) 
        primary_variable_caps_transposed = tf.transpose(primary_variable_caps,perm=[0,2,3,1])

        primary_static_caps, _ = tf.nn.top_k(primary_variable_caps_transposed,k=top_a)
        

        primary_static_caps = tf.reshape(primary_static_caps,shape=(1,-1, node_dim, input_dimension))
        
        # shape = (1, batch_size x top_a, node_dim, num_conv)
        primary_static_caps = tf.transpose(primary_static_caps,perm=[0,3,1,2])
        
        v_J = primary_static_caps
        # shape = (batch_size, top_a x node_dim, num_conv)
        v_J = tf.reshape(v_J, (self.batch_size, -1, output_dimension))

        # shape = (batch_size, max_tree_size x node_dim, output_dimension)
        u_i = tf.reshape(primary_variable_caps, (self.batch_size, -1, output_dimension))
        
        u_i = tf.stop_gradient(u_i)
        for rout in range(1):
            # shape = (batch_size, max_tree_size x node_dim, top_a x node_dim)
            u_produce_v = tf.matmul(u_i, v_J,transpose_b=True)
            alpha_IJ += u_produce_v

            beta_IJ = tf.nn.softmax(alpha_IJ,axis=-1)
            v_J = tf.matmul(beta_IJ,u_i,transpose_a=True)

        v_J = tf.reshape(v_J,(self.batch_size, static_caps_num_caps, output_dimension, 1))
        return self.squash(v_J)


    def margin_loss(self, logits_node, labels):
        """Create a loss layer for training."""

        with tf.name_scope('treecaps_margin_loss'):
            max_l = tf.square(tf.maximum(0., 0.9 - logits_node))
            max_r = tf.square(tf.maximum(0., logits_node - 0.1))
            T_c = labels
            L_c = T_c * max_l + 0.5 * (1 - T_c) * max_r
            
            loss = tf.reduce_mean(tf.reduce_sum(L_c, axis=1))

            return loss
