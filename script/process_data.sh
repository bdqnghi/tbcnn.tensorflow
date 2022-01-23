PARSER=pycparser
TRAIN_DATA_PATH=../OJ104_${PARSER}_train_test_val/train
TEST_DATA_PATH=../OJ104_${PARSER}_train_test_val/test
VAL_DATA_PATH=../OJ104_${PARSER}_train_test_val/val
NODE_TYPE_VOCAB_PATH=../vocab/${PARSER}/node_type/type.txt
NODE_TOKEN_VOCAB_PATH=../vocab/${PARSER}/node_token/token.txt
PYTHON=python3
${PYTHON} process_data.py \
--data_path ${TRAIN_DATA_PATH} --node_type_vocab_path ${NODE_TYPE_VOCAB_PATH} --node_token_vocab_path ${NODE_TOKEN_VOCAB_PATH} \
--parser ${PARSER}
${PYTHON} process_data.py \
--data_path ${TEST_DATA_PATH} --node_type_vocab_path ${NODE_TYPE_VOCAB_PATH} --node_token_vocab_path ${NODE_TOKEN_VOCAB_PATH} \
--parser ${PARSER}
${PYTHON} process_data.py \
--data_path ${VAL_DATA_PATH} --node_type_vocab_path ${NODE_TYPE_VOCAB_PATH} --node_token_vocab_path ${NODE_TOKEN_VOCAB_PATH} \
--parser ${PARSER}