from sklearn.preprocessing import RobustScaler
import numpy as np
from sklearn import preprocessing

def scale_attention_score(attention_array, top_node):

    attention_array = np.array(attention_array)
  
    top_n_idx = np.argsort(attention_array)[-top_node:][::-1]
    top_n_values = [attention_array[i] for i in top_n_idx]

    # top_n_idx = top_n_idx[2:]
    # top_n_values = top_n_values[2:]

    max_point = max(top_n_values)
    min_point = min(top_n_values)

    norm_data = []
    for i, point in enumerate(attention_array):
        if i in top_n_idx:
            point_norm = float((point - min_point)/(max_point - min_point))

            # Min to scale from 0 to 1
            point_scaled = point_norm * (1.0 - 0.0) + 0.0
            norm_data.append(point_scaled)
        else:
            norm_data.append(0.0)

    return norm_data

def robust_scale(attention_score):
    attention_score = attention_score.reshape(attention_score.shape[1],1)
    attention_score = preprocessing.scale(attention_score)
    transformer = RobustScaler(quantile_range=(0.0, 1.0)).fit(attention_score)
    return transformer.transform(attention_score).reshape(attention_score.shape[0],)
