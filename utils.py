
def scale_attention_score(attention_array):
    max_point = max(attention_array)
    min_point = min(attention_array)

    norm_data = []
    for point in attention_array:
        point_norm = float((point - min_point)/(max_point - min_point))
        norm_data.append(point_norm)

    return norm_data