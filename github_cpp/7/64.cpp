#include "MergeSort.h"

MergeSort::MergeSort()
{

}

MergeSort::~MergeSort()
{

}

void MergeSort::Sort(vector<int> &pList)
{
    mergeSort(pList);
}

void MergeSort::mergeSort(vector<int> &v)
{
    if(v.size() <= 1)
    {
        return;
    }

    size_t mid = (v.size()) / 2;

    std::vector<int> left(v.begin(), v.begin() + mid);
    std::vector<int> right(v.begin() + mid, v.end());

    mergeSort(left);
    mergeSort(right);
    v = merge(left, right);
}

std::vector<int> MergeSort::merge(vector<int> &left, vector<int> &right)
{
    vector<int> result;

    if(left.empty())
    {
        return right;
    }

    if(right.empty())
    {
        return left;
    }

    size_t i = 0;
    size_t j = 0;

    for(size_t k = i; k < left.size(); ++k)
    {
        for(size_t z = j; z < right.size(); ++z)
        {
            if(right[z] <= left[k])
            {
                ++j;
                result.push_back(right[z]);
            }
            else
            {
                break;
            }
        }
        ++i;
        result.push_back(left[k]);
    }

    if(left.size() > i)
    {
        for(size_t x = i; x < left.size(); ++x)
        {
            result.push_back(left[x]);
        }
    }
    else if(right.size() > j)
    {
        for(size_t x = j; x < right.size(); ++x)
        {
            result.push_back(right[x]);
        }
    }

    return result;
}

