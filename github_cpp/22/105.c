
#ifndef ___BucketSort_cpp__
#define ___BucketSort_cpp__
#include <string.h>
#include <stdlib.h>



class BucketSort{
public:
    class Bucket{
    private:
        int curSize,maxSize,*dataArr;
    public:
        inline int getMaxSize(){ return maxSize;}
        inline int getCurSize(){ return curSize;}
        inline void push(int val){
            dataArr[curSize++] = val;
        }
        inline int *retrieve(){
            curSize = 0;
            return dataArr;
        }
        Bucket(int _maxSize){
            curSize = 0;
            maxSize = _maxSize;
            dataArr = (int *) malloc(_maxSize * sizeof(int));
        }
        ~Bucket(){
            free(dataArr);
        }
    };
    static int sort(char *input){
        
    }
};







#endif
