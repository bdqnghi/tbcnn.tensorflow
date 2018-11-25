



#include "BucketSort.h"


#include <algorithm>
#include <iostream>
#include<cmath>
































bool aLessB(const unsigned int& x, const unsigned int& y) {
    if (x == y) return false; 
    
    std::string a = std::to_string(x);
    std::string b = std::to_string(y);
    unsigned long lenA = a.length();
    unsigned long lenB = b.length();


    for (unsigned long i = 0; i < lenA; ++i) {

        if (a[i] < b[i]) return true;
        else if (a[i] > b[i]) return false;
        else { 
            if (i == lenB - 1) return false;
            else if (i == lenA - 1) return true;

        }

    }
    return false;
}



void BucketSort::sort(unsigned int numCores) {


    
    numCores =  ( numCores == 1)? 2 : numCores;

   
    NumOfSubThread = numCores - 1;

    
    std::vector<std::vector<unsigned int>> middle_vec_handled_by_each_thread{  9,std::vector<unsigned int> {}};
    answer_bucked = middle_vec_handled_by_each_thread;


    for (unsigned int i = 0; i < NumOfSubThread ; ++i) {
        Bucket_3D.push_back(middle_vec_handled_by_each_thread);
    }



    
    
    std::vector<std::thread> ThreadPool;
    for(int i = 0;i < NumOfSubThread - 1;++i)
    {
        ThreadPool.emplace_back(&BucketSort::DevideToSubParts,this,i);
    }


    
    DevideToSubParts(NumOfSubThread - 1);


    for(auto& thread:ThreadPool){
        thread.join();
    }

    ThreadPool.clear();
    numbersToSort.clear();

    
    

    std::vector<int> indicating_flag(9,1);


    
    


    for(int i = 0;i < NumOfSubThread - 1;++i)
    {

        ThreadPool.emplace_back(&BucketSort::SortSubBucket,this,indicating_flag);
    }


    SortSubBucket(indicating_flag);


    for(auto& thread:ThreadPool){
        thread.join();
    }

    ThreadPool.clear();





    for(int numberIndex= 0;numberIndex< 9;numberIndex++)
    {
        numbersToSort.insert(numbersToSort.end(),
                             answer_bucked[numberIndex].begin(),
                             answer_bucked[numberIndex].end());
    }

    answer_bucked.clear();
    Bucket_3D.clear();
}














































void BucketSort::SortSubBucket(std::vector<int> & indicate){

    while(true)
    {
        int index = -1;

        
        
        

        if(NineBuckekMutex.try_lock()){
            for(int i = 0;i < 9;++i)
            {
                if(indicate[i])
                {
                    index = i;
                    indicate[i] = 0;
                    break;
                }
            }

            NineBuckekMutex.unlock();
        }



        
        if(index > -1)
        {
            for(int SubPartId = 0;SubPartId < NumOfSubThread;++SubPartId)
            {
                answer_bucked[index].insert(answer_bucked[index].end(),
                                                    Bucket_3D[SubPartId][index].begin(),
                                                    Bucket_3D[SubPartId][index].end());
            }
            std::sort(answer_bucked[index].begin(),answer_bucked[index].end(),
                      [](const unsigned int&x ,const unsigned int&y){
                          return aLessB(x,y);
                      });
        }
        else
            return;
    }
}

void BucketSort::DevideToSubParts(int index){

    unsigned long NumOfEachPart = numbersToSort.size() / NumOfSubThread;
    unsigned long Begining = index * NumOfEachPart;


    unsigned long Ending = (index + 1 == NumOfSubThread)? numbersToSort.size() - 1: (index + 1) * NumOfEachPart - 1;

    for(unsigned long i = Begining;i <= Ending;++i)
    {
        unsigned int value = numbersToSort[i];
        unsigned int GetMSB = numbersToSort[i];
        while(GetMSB/10 > 0){
            GetMSB /= 10;
        }

        --GetMSB;

        Bucket_3D[index][GetMSB].push_back(value);
    }
}

