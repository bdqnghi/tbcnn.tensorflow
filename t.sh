if [ ! -f embedding/fast_pretrained_vectors.pkl ]; then
	pip3 install --upgrade pip
	pip3 install -r requirements.txt
	tar xvfz embedding/fast_pretrained_vectors.pkl.tar.gz
	mv fast_pretrained_vectors.pkl embedding/
fi
file=${1:-live_test/github_cpp/26/10.cpp}
python3 live_test.py --model_path model/github_50_cpp_new --n_classes=50 --test_file $file
