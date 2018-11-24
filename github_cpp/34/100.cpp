#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class NaiveBayes {
public:
    void load_data(string path);
    void train_model();
    int predict(const vector<int> &item);
private:
    vector<vector<int>> data;
    map<pair<int, int>, double> c_p; //conditional prob
    map<int, double> p_p; // prior prob
};

void NaiveBayes::load_data(string path) {
    ifstream fin(path.c_str());
    if (!fin) {
        cerr << "open file error" << endl;
        exit(1);
    }

    string line;
    while (getline(fin, line)) {
        if (line.size() > 1) {
            stringstream sin(line);
            int elem;
            vector<int> tmp;
            while (sin >> elem) {
                tmp.push_back(elem);
            }
            data.push_back(tmp);
        }
    }
    fin.close();
}

void NaiveBayes::train_model() {
    for (auto &d : data) {
        int len = d.size();
        p_p[d[len - 1]] += (1.0 / data.size());
    }

    for (auto &p : p_p) {
        int label = p.first;
        double prior = p.second;
        for (auto &d : data) {
            for (int i = 0; i < d.size(); ++i) {
                c_p[make_pair(d[i], label)] += (1.0 / (prior * data.size()));
            }
        }
    }
}

int NaiveBayes::predict(const vector<int> &item) { 
    int result;
    double max_prob = 0.0;
    for (auto &p : p_p) {
        int label = p.first;
        double prior = p.second;
        double prob = prior;
        for (int i = 0; i < item.size() - 1; ++i) {
            prob *= c_p[make_pair(item[i], label)];
        }

        if (prob > max_prob) {
            max_prob = prob;
            result = label;
        }
    }

    return result;
}

int main() {
    NaiveBayes naive_bayes;
    naive_bayes.load_data(string("result.txt"));
    naive_bayes.train_model();

    vector<int> item{2, 4};
    cout << naive_bayes.predict(item);
    return 0;
}
