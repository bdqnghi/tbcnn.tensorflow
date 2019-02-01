import pandas as pd
# matrix = pd.read_csv("test.csv")
matrix = pd.read_csv("test.csv", index_col=False)
print(matrix.shape)
# matrix.reindex(axis=1)
# matrix = matrix.reindex(axis=1)
# print(matrix)
# matrix.columns = [i for i in range(1,245)]
# matrix.index = range(1,245)
# print(matrix)
# matrix.to_csv("test.csv", sep=",")
matrix_id_max = matrix.idxmax(axis=1)
matrix_max = matrix.max(axis=1)
# matrix_row_max = matrix.ix[matrix_id_max].idxmax(axis=1)
# matrix_max = matrix.apply(lambda matrix: matrix.argmax(), axis=1)
print(matrix_max)
matrix_max.to_csv("test_row_max.csv", sep=",")
matrix_id_max.to_csv("test_row_id_max.csv", sep=",")
# matrix_row_max.to_csv("test_row_max.csv", sep=",")