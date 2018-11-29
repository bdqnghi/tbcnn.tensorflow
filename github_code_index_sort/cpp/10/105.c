/*
<REQUIRE>
    <1>

<USAGE>
    <1>

*/
#ifndef ___BucketSort_cpp__
#define ___BucketSort_cpp__
#include <string.h>
#include <stdlib.h>
//=========================================================================
//  BucketSort
//=========================================================================
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
        /*
        int existence[256],length = 1;
        memset(existence, 0, sizeof(existence));
        for(char *read_input = (char *) input; *read_input != '\0'; ++read_input){
            existence[*read_input] += 1;
            length += 1;
        }
        existence['\0'] = 1;

        Bucket *buckets[256];
        char output
        for(int i = 0; i < 256; ++i){
            buckets
        }*/
    }
};







#endif
