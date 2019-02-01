import numpy as np
from keras.preprocessing.sequence import pad_sequences

sequences = [
    [1, 2, 3, 4],
       [1, 2, 3],
             [1]
    ]
# pad sequence
padded = pad_sequences(sequences)
print(padded)

# pad = [1,2,4,0,1,2,0]

mask = (padded > 0).astype(np.int32)
print(mask)