from sklearn.preprocessing import RobustScaler
import numpy as np
from sklearn import preprocessing
import os, itertools

def scale_attention_score(attention_array, top_node):

    attention_array = np.array(attention_array)
  
    top_n_idx = np.argsort(attention_array)[-top_node:][::-1]
    top_n_values = [attention_array[i] for i in top_n_idx]

    # top_n_idx = top_n_idx[4:]
    # top_n_values = top_n_values[4:]

    max_point = max(top_n_values)
    min_point = min(top_n_values)

    norm_data = []
    for i, point in enumerate(attention_array):
        if i in top_n_idx:
            point_norm = float((point - min_point)/(max_point - min_point))

            # Means to scale from 0 to 1
            point_scaled = point_norm * (1.0 - 0.0) + 0.0
            norm_data.append(point_scaled)
        else:
            norm_data.append(0.0)

    return norm_data


def scale_attention_score_by_group(attention_array):

    attention_array = np.array(attention_array)
  
    clusters = [list(g) for _, g in itertools.groupby(attention_array, lambda x: x)]
    average = float(1/len(clusters))
    # print(clusters)
    # print("Num clusters : " + str(len(clusters)))

    scaled_attention_array = []
    for score in attention_array:
        for i, cluster in enumerate(clusters):
            if score in cluster:
                temp_score = average * (len(clusters) - i)
                scaled_attention_array.append(round(temp_score,5))
    return scaled_attention_array


def robust_scale(attention_score):
    attention_score = attention_score.reshape(attention_score.shape[1],1)
    attention_score = preprocessing.scale(attention_score)
    transformer = RobustScaler(quantile_range=(0.0, 1.0)).fit(attention_score)
    return transformer.transform(attention_score).reshape(attention_score.shape[0],)
