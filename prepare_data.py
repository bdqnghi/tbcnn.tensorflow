import tarfile
tar = tarfile.open("embedding/fast_pretrained_vectors.pkl.tar.gz")
tar.extractall("embedding/")
tar.close()