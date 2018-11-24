#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <Eigen/Dense> 
#define SAMPLE "./sample_submission.csv"
#define TRAIN "./save_train.csv"
#define TEST "./save_test.csv"

using namespace std;
using namespace Eigen; 


 struct Data {
    vector<float> features;
    int id;
};
void randomScale(float * s, int len) {
    for (int i = 0; i < len; i++) {
    	int temp = rand()%1000;
    	float j = (float)temp/1000;
        s[i] = j;
    }
}

void loadDataSet(vector<Data> &,const char *);
int main() {
    float _CONSTANT = 0.003;
    float temp[384];
    int iterTime = 10;
    float scale[385];
    MatrixXf Mscale(1,385);
    randomScale(scale, 385);
	//load the data and initial
	//will get the two-dimension array for the training set and one array for ref
	//two-dimension array for test
    vector<Data> trainData;
    std::vector<MatrixXf> xset;
	loadDataSet(trainData, TRAIN); 
    int trainNum = trainData.size();
    
    for (int i = 0; i < trainNum; i++)
    {
        MatrixXf x(385,1);
        x(0,0) = 0;
        for (int j = 0; j < 384; j++)
        {
            x(j+1, 0) = trainData[i].features[j];
        }
        xset.push_back(x);
    }
    while (iterTime--)
    {
    	int e;
    	cin >> e;
        float result[trainNum];
        //cout << trainNum << endl;
        for (int j = 0; j < 385; j++)
        {
            Mscale(0, j) = scale[j];
        }
        
        for (int i = 0; i < trainNum; i++)
        {
            MatrixXf mul = Mscale*xset[i];
            result[i] = (float)mul(0,0)-trainData[i].features[384];
        }
        for (int i = 0; i < 385; i++) {
            float add = 0;
            for (int j = 0; j < trainNum; j++)
            {
                MatrixXf xtemp = xset[j];
                if (i == 0) add += result[j];
                else 
                    add += result[j]*xtemp(i, 0);
            }
            scale[i] = scale[i] - add*_CONSTANT/trainNum;
        }
    }
    //
    return 0;
}

void loadDataSet(vector<Data> & ds,const char * dataFile) {
    int id;
    vector<float> fea;
    float temp;
    Data d;
    string line;
    ifstream fin(dataFile);
    if (!fin){
        cout << "文件打开失败" << endl;
        exit(0);
    }
    getline(fin, line);
    getline(fin, line);
    while (!fin.eof()){
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') line[i] = ' ';
        }
        stringstream sin(line);
        sin >> id;
        sin >> temp;
        while (sin){
            fea.push_back(temp);
            sin >> temp;
        }
        d.features = fea;
        d.id = id;
        ds.push_back(d);
        sin.str("");
        sin.clear();
        getline(fin, line);
        fea.clear();
    }
    fin.close();
}
