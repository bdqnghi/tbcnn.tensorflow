file=${1:-live_test/github_cpp/26/10.cpp}
if [ ! -f embedding/fast_pretrained_vectors.pkl ]; then
	pip3 install --upgrade pip
	pip3 install tensorflow
	pip3 install sklearn
	pip3 install tqdm
	pip3 install msgpack
	tar xvfz embedding/fast_pretrained_vectors.pkl.tar.gz
	mv fast_pretrained_vectors.pkl embedding/
fi
if [ ! -f ${file/.cpp/.pb} ]; then
	fast -p $file ${file/.cpp/.pb}
fi
python3 live_test.py --model_path model/github_50_cpp_new --n_classes=50 --test_file $file
