echo "Extracting pretrained embedding......"

python3 prepare_data.py

echo "Downloading docker image of f-ast tool......."

docker pull yijun/fast:built
