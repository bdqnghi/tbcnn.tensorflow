//
// Created by Haoran Zhi on 16/10/21.
//

#include "BucketSort.h"


#include <algorithm>
#include <iostream>
#include<cmath>


//bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {
//
//    if (x == y) return false; // if the two numbers are the same then one is not less than the other
//
//    unsigned int a = x;
//    unsigned int b = y;
//
//    // work out the digit we are currently comparing on.
//    if (pow == 0) {
//        while (a / 10 > 0) {
//            a = a / 10;
//        }
//        while (b / 10 > 0) {
//            b = b / 10;
//        }
//    } else {
//        while (a / 10 >= (unsigned int) std::round(std::pow(10,pow))) {
//            a = a / 10;
//        }
//        while (b / 10 >= (unsigned int) std::round(std::pow(10,pow))) {
//            b = b / 10;
//        }
//    }
//
//    if (a == b)
//        return aLessB(x,y,pow + 1);  // recurse if this digit is the same
//    else
//        return a < b;
//};

bool aLessB(const unsigned int& x, const unsigned int& y) {
    if (x == y) return false; // if the two numbers are the same then one is not less than the other
    //convert unsighed int to string
    std::string a = std::to_string(x);
    std::string b = std::to_string(y);
    unsigned long lenA = a.length();
    unsigned long lenB = b.length();


    for (unsigned long i = 0; i < lenA; ++i) {

        if (a[i] < b[i]) return true;
        else if (a[i] > b[i]) return false;
        else { //a[i] == b[i]
            if (i == lenB - 1) return false;
            else if (i == lenA - 1) return true;

        }

    }
    return false;
}



void BucketSort::sort(unsigned int numCores) {


    // protecting single core
    numCores =  ( numCores == 1)? 2 : numCores;

   // main process
    NumOfSubThread = numCores - 1;

    //3D vectors will have NumofSubThread sub vectors , each have 9 sub vectors
    std::vector<std::vector<unsigned int>> middle_vec_handled_by_each_thread{  9,std::vector<unsigned int> {}};
    answer_bucked = middle_vec_handled_by_each_thread;


    for (unsigned int i = 0; i < NumOfSubThread ; ++i) {
        Bucket_3D.push_back(middle_vec_handled_by_each_thread);
    }



    //divide the whole vector to nMaxThd partition,every thread handle one part
    //the thread assign the number in to different vector depends on the index number
    std::vector<std::thread> ThreadPool;
    for(int i = 0;i < NumOfSubThread - 1;++i)
    {
        ThreadPool.emplace_back(&BucketSort::DevideToSubParts,this,i);
    }


    // the last parts is finished by the main thread
    DevideToSubParts(NumOfSubThread - 1);


    for(auto& thread:ThreadPool){
        thread.join();
    }

    ThreadPool.clear();
    numbersToSort.clear();

    //Merging the subPart of the Bucket_3D into the answer set , and sorting them at the same time .
    /* The vector indicating flag is a flag vector, every sub threading is going to pick a sub bucket to merge,
     * For example , sub thread is going to merge all the buckets begining with 1 into the answer bucket,
     *
     * But how to check whether the sub bucket of 1  solved or not,  so if corresponding position is 1, indicating that
     * sub bucket 1 is still not solved, and then a sub thread will change the indicating flag to 0, and begin to solve
     * it.
     *
     * So if checked that the indicating flag of a position is 0, then do not have to solve that .
     *
     */

    std::vector<int> indicating_flag(9,1);


    /*
     * Here I have some problem , and I send you an email,
     * This works if I pass an int array as parameters of function SortSubBucket,
     * But if I use the std::vector<int> &   it get errors   as follow
     * [ 33%] Building CXX object CMakeFiles/6771assign6.dir/BucketSort.cpp.o
In file included from /Users/haoranzhi/6771assign6/BucketSort.cpp:5:
In file included from /Users/haoranzhi/6771assign6/BucketSort.h:8:
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/thread:337:5: error: attempt to use a deleted function
    __invoke(_VSTD::move(_VSTD::get<0>(__t)), _VSTD::move(_VSTD::get<_Indices>(__t))...);
    ^
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/thread:347:5: note: in instantiation of function template specialization 'std::__1::__thread_execute<void (BucketSort::*)(std::__1::vector<int, std::__1::allocator<int> > &), BucketSort *, std::__1::vector<int, std::__1::allocator<int> > , 1, 2>' requested here
    __thread_execute(*__p, _Index());
     */
    //int indicating_flag[9] = {1,1,1,1,1,1,1,1,1};


    for(int i = 0;i < NumOfSubThread - 1;++i)
    {
//        ThreadPool.emplace_back(std::thread{&BucketSort::SortSubBucket,this,indicating_flag});
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

//void BucketSort::SortSubBucket(int* indicate){
//
//    while(true)
//    {
//        int index = -1;
//
//        //polling task
//        //value one means radix(i) is not handled by any threads
//        //value zero means radix(i) already have thread handled.
//
//        if(NineBuckekMutex.try_lock()){
//            for(int i = 0;i < 9;++i)
//            {
//                if(indicate[i])
//                {
//                    index = i;
//                    indicate[i] = 0;
//                    break;
//                }
//            }
//
//            NineBuckekMutex.unlock();
//        }
//
//
//
//        //merge and sort radix(i) or quit thread
//        if(index > -1)
//        {
//            for(int SubPartId = 0;SubPartId < NumOfSubThread;++SubPartId)
//            {
//                answer_bucked[index].insert(answer_bucked[index].end(),
//                                            Bucket_3D[SubPartId][index].begin(),
//                                            Bucket_3D[SubPartId][index].end());
//            }
//            std::sort(answer_bucked[index].begin(),answer_bucked[index].end(),
//                      [](const unsigned int&x ,const unsigned int&y){
//                          return aLessB(x,y);
//                      });
//        }
//        else
//            return;
//    }
//}

void BucketSort::SortSubBucket(std::vector<int> & indicate){

    while(true)
    {
        int index = -1;

        //polling task
        //value one means radix(i) is not handled by any threads
        //value zero means radix(i) already have thread handled.

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



        //merge and sort radix(i) or quit thread
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

