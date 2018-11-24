#include "bayes/naive_bayes.hpp"
#include <cmath>
#include <algorithm>
#include <sstream>

#include "log/log.hpp"

#include "util/op.hpp"
#include "util/io.hpp"
#include "util/optimize.hpp"


using namespace std;
using wzp::Matrix;

namespace aiolos
{

//regis
ReflectionRegister(Classify, NaiveBayes) regis_naive_bayes("naive_bayes");

void NaiveBayes::init(wzp::ConfigParser* config_parser) {
    m_config_parser = config_parser;
}

void NaiveBayes::train(wzp::Matrix<Type>& input_matrix, wzp::Matrix<int>& input_label) {
    m_input_matrix = &input_matrix;
    m_input_label = &input_label;
    //train
    train_naive_bayes();
}

void NaiveBayes::train(wzp::Matrix<Type>& input_matrix,
     wzp::Matrix<int>& input_label, wzp::Matrix<Type>& validate_matrix,
     wzp::Matrix<int>& validate_label) {
    //null now
    m_input_matrix = &input_matrix;
    m_input_label = &input_label;
    m_validate_matrix = &validate_matrix;
    m_validate_label = &validate_label;
    //init the m_weights
    train_naive_bayes();
    auto wrong_rate = eval::eval([this]{return predict(*m_validate_matrix);},
        *m_validate_label, LossTypes::Error01);
    wzp::log::info("Validate Error Rate", wrong_rate);
}

wzp::Matrix<int> NaiveBayes::predict(wzp::Matrix<Type>& predict_matrix) {
    Matrix<int> res(predict_matrix.rows(), 1);
    for(size_t i = 0; i < predict_matrix.rows(); ++i) {
        res(i, 0) = classify(predict_matrix, i);
    }
    return res;
}

void NaiveBayes::dump_model(const char* filename) {
    //dump model
    //use s ostringstream to store string buffers
    ostringstream ostream; //use '\n' to split datas
    //m_pClass
    ostream << io::unordered_map_to_string(m_pClass);
    //m_class_index
    ostream << io::unordered_map_to_string(m_class_index);
    //write the m_fea_index length
    string cache;
    size_t len = m_fea_index.size();
    wzp::serialize(&cache, len);
    ostream << cache;
    //write m_fea_index
    for(size_t j = 0; j < m_fea_index.size(); ++j) {
        ostream << io::unordered_map_to_string(m_fea_index[j]);
    }
    string buffer;
    m_pW.matrix_to_string(&buffer);
    ostream << buffer;
    cache = ostream.str();
    //write to file
    std::ofstream ofile(filename, std::ios::binary);
    ofile.write(cache.c_str(), sizeof(char) * cache.size());
    ofile.close();
}

void NaiveBayes::restore_model(const char* filename) {
    //first read data from file
    ifstream ifile;
    ifile.open(filename);
    std::string buffer((std::istreambuf_iterator<char>(ifile)),
        std::istreambuf_iterator<char>());
    if(buffer.empty()) {
        wzp::log::fatal("Model File Illegal", filename);
    }
    ifile.close();
    m_pClass = std::move(io::string_to_unordered_map<int, Type>(buffer));
    m_class_index = std::move(io::string_to_unordered_map<int, size_t>(buffer));
    //the length of m_fea_index
    size_t length;
    wzp::deserialize(buffer, length);
    buffer = std::move(buffer.substr(sizeof(size_t)));
    m_fea_index.resize(length);
    for(size_t j = 0; j < length; ++j) {
        m_fea_index[j] = std::move(io::string_to_unordered_map<Type, size_t>(buffer));
    }
    m_pW.string_to_matrix(buffer);
}

//private function
void NaiveBayes::train_naive_bayes() {
    //compute class numbers and set index
    auto col_length = compute_class_numbers();
    //compute each feature in each class
    Matrix<Type> p_num(m_class_index.size(), col_length, 1.0);
    vector<size_t> aixses;
    for(size_t i = 0; i < m_input_matrix->rows(); ++i) {
        //for each class
        aixses = std::move(op::generate<vector<size_t>>(m_input_matrix->cols()));
        auto class_row_index = m_class_index[m_input_label->at(i, 0)];
        std::for_each(begin(aixses), end(aixses),
         [this, &p_num, class_row_index, i](size_t axis) {
            //to get the class row index
            auto col_index = m_fea_index[axis][m_input_matrix->at(i, axis)];
            p_num(class_row_index, col_index) += 1.0;
        });
    }
    //compute all feature sum
    // aixses = std::move(op::generate<vector<size_t>>(p_num.rows()));
    wzp::ParallelRange(p_num.rows(),
     [this, &p_num](size_t class_index) {
        //compute all numbers of features
        auto all_features_num = op::row_sum(p_num, class_index) + 1.0;
        for(size_t j = 0; j < p_num.cols(); ++j) {
            m_pW(class_index, j) = log(p_num(class_index, j) / all_features_num);
        }
    });
}

size_t NaiveBayes::compute_class_numbers() {
    //compute class
    auto label_cnt = std::move(op::count_label(*m_input_label));
    size_t row_index= 0;
    for(auto& p : label_cnt) {
        //set index and compute porb of p(ci)
        m_pClass.emplace(p.first, (Type)p.second / (Type)(m_input_label->rows()));
        m_class_index.emplace(p.first, row_index++);
    }
    //reshape the m_pW, col is feature number
    row_index = 0;
    m_fea_index.resize(m_input_matrix->cols());
    for(size_t j = 0; j < m_input_matrix->cols(); ++j) {
        //for each row
        for(size_t i = 0; i < m_input_matrix->rows(); ++i) {
            if(m_fea_index[j].find(m_input_matrix->at(i, j)) == m_fea_index[j].end()) {
                m_fea_index[j].emplace(m_input_matrix->at(i, j), row_index++);
            }
        }
    }
    m_pW.reshape(m_class_index.size(), row_index);
    return row_index;
}

int NaiveBayes::classify(const wzp::Matrix<Type>& predict_matrix, size_t row_index) {
    int max_class = -1;
    Type max_prob;
    bool is_first = true;
    for(auto& p : m_class_index) {
        //compute class prob
        Type p_class = log(m_pClass[p.first]);
        //compute each prob
        for(size_t j = 0; j < predict_matrix.cols(); ++j) {
            auto fea_index = m_fea_index[j][predict_matrix(row_index, j)];
            p_class += m_pW(p.second, fea_index);
        }
        if(is_first) {
            is_first = false;
            max_prob = p_class;
            max_class = p.first;
            continue;
        }
        if(p_class > max_prob) {
            max_class = p.first;
            max_prob = p_class;
        }
    }
    return max_class;
}

} //aiolos