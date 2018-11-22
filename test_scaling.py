
data = [0.001,0.002,0.00003,0.000000052323]

max_point = max(data)
min_point = min(data)


norm_data = []
for point in data:
    point_norm = float((point - min_point)/(max_point - min_point))
    norm_data.append(point_norm)

print(norm_data)