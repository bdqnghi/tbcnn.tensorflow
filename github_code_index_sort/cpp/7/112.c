#pragma once
#include "basesort.hpp"

class shellsort : private basesort
{
public:
    shellsort();
    ~shellsort();

    // ͨ�� basesort �̳�
    virtual void sort(int arr[], int num) override;

};

shellsort::shellsort()
{
}

shellsort::~shellsort()
{
}

void shellsort::sort(int arr[], int num)
{
    print(arr, num);
    int ntemp = 0;
    int j = 0;
    for (int nincrement = (num / 2); nincrement > 0; nincrement /= 2) {
        for (int i = nincrement; i < num; ++i) {
            ntemp = arr[i];
            for (j = i; j >= nincrement; j -= nincrement) {
                if (arr[j - nincrement] > ntemp) {
                    arr[j] = arr[j - nincrement];
                    print(arr, num, true);
                } else {
                    break;
                }
            }
            arr[j] = ntemp;
            print(arr, num);
        }
    }
}
