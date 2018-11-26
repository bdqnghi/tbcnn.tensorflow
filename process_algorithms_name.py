with open("algorithms.txt","r") as f:
    data = f.readlines()

    for line in data:
        line = line.replace("\n","")
        ver_1 = line.replace("-"," ")
        ver_2 = line.replace("-","")
        new_line = line + "," + ver_1 + "," + ver_2
        with open("algorithms_2.txt","a") as f1:
            f1.write(new_line)
            f1.write("\n")