# To analyze the classification result
import seaborn as sns, numpy as np
import matplotlib.pyplot as plt
import csv
import numpy as np
import scipy.stats as stats


correct = list()
wrong = list()
with open("analysis_single/sum_softmax.csv","r") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for i, row in enumerate(csv_reader):

        if i > 0:
            url = row[0]
            oracle_cosine = float(row[1])
            reverse_oracle_cosine = float(row[2])
            ratio = float(row[6])
            actual = int(row[7])
            predicted = int(row[8])
            
            if ratio > 0.2:
                if actual == predicted:
                    correct.append(url)
                else:
                    wrong.append(url)

print(len(correct))
print(len(wrong))
percentage = len(correct)/(len(correct) + len(wrong))
print("Percent correct prediction: " + str(percentage))

