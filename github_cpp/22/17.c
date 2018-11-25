#include "bucketsort.h"

BucketSort::BucketSort()
{

}

void BucketSort::doinsertionsortforbucket(int* input, int len)
{
    while( len-- > 0)
    {
        if(input[len] > input[len+1])
        {
            int temp = input[len];
            input[len] = input[len +1 ];
            input[len+1]= temp;
        }
        else    return;
    }
}
void BucketSort::Bucket_Sort(int* input, int arr_size)
{
    queue<int> *buckets[10];
    for(int i=0; i< 10;i++)
        buckets[i] = new queue<int>;

    
    for (int i=0;i<arr_size;i++)
    {
        int hashValue = hash(input[i]);
        if (hashValue >= 10)
            hashValue = 10-1;

        buckets[hashValue]->push(input[i]);
    }

    
    int outputidx = 0;
    for ( int i = 0; i < 10; i++ )
    {
        if (buckets[i]->size() == 1) {
            input[outputidx++] = buckets[i]->front();
            cout << buckets[i]->front() << " | ";
            buckets[i]->pop();
        }
        if (buckets[i]->size() > 1)
        {
            while (!buckets[i]->empty())
            {
                input[outputidx] = buckets[i]->front();
                doinsertionsortforbucket(input, outputidx);

                buckets[i]->pop();
                outputidx++;
            }

        }
    }

     for ( int i = 0; i < 10; i++ )
        delete buckets[i];

}
int BucketSort::hash(int n)
{
    return n/5;
}
