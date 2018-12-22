import seaborn as sns, numpy as np
import matplotlib.pyplot as plt
import csv

oracle = list()
reverse_oracle = list()
with open("analysis_single/sum_softmax.csv","r") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        if row[1] != "nan" and row[2] != "nan":
            oracle.append(float(row[1]))
            reverse_oracle.append(float(row[2]))


ax = sns.distplot(oracle, label="oracle")
ay = sns.distplot(reverse_oracle, label="reverse oracle")

plt.legend()
plt.show()