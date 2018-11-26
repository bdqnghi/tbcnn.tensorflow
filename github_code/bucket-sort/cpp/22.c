#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <utility>
#include <random>

using namespace std;

class RandDouble{
    public:
        RandDouble(double low, double high): ge(chrono::system_clock::now().time_since_epoch().count()),dist(low, high){}
        ~RandDouble(){};
        double operator()(){ return dist(ge); }
    private:
        default_random_engine ge;
        uniform_real_distribution<> dist;
};

class BucketSort{
    public:
        BucketSort(int n);
        ~BucketSort(){};
        void printData();
        void sort();
    private:
        int size;
        vector<double> sortData;
        void mergeSort(vector<double> &A);
};

BucketSort::BucketSort(int n):size(n),sortData(vector<double>(n)){
    RandDouble rnd(0.0, 1.0);
    for(auto &ele : sortData){
        ele = rnd();
    }
}

void BucketSort::printData(){
    for(auto ele : sortData){
        cout << ele << " ";
    }
    cout << endl;
}

void BucketSort::sort(){
    vector<vector<double>> buckets(size);
    for(auto ele : sortData){
        int index = ele * size;
        buckets[index].push_back(ele);
    }

    for(auto &bucket : buckets){
        mergeSort(bucket);
    }

    int index = 0;
    for(auto bucket : buckets){
        for(auto ele : bucket){
            sortData[index++] = ele;
        }
    }
}

void BucketSort::mergeSort(vector<double> &A){  // use non recursive to implete the merge sort
    int size = A.size();
    for(int step=1; step < size; step<<=1){
        for(int left=0; left < size; left+=2*step){
            vector<double> tmpA(2*step);
            int l(left);
            int r = min(left+step, size);
            int e = min(left+2*step, size);
            
            int i(l),j(r),k(0);
            while(i<r && j<e){
                if(A[i] <= A[j]){
                    tmpA[k++] = A[i++];
                } else {
                    tmpA[k++] = A[j++];
                }
            }

            while(i<r){
                tmpA[k++] = A[i++];
            }
            while(j<e){
                tmpA[k++] = A[j++];
            }
            
            for(int m=l, n=0; m<e; ++m){
                A[m] = tmpA[n++];
            }
        }

    }
}


int main(){
    BucketSort rs(5);
    rs.printData();
    rs.sort();
    rs.printData();
}

