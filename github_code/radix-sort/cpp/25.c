// #############################################################################
// # FileName:  Radix.cpp
// # Author:    Lonely, CS0901, HUST
// #############################################################################
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

// #sorting algorithm begin
// #############################################################################
template<typename DataType> class RadixSorter
{
public:
    static void sort(vector<DataType>& elements)
    {
        int nLen = elements.size();
        vector<DataType> nDataRadix(nLen, 0);

        int n = 10;

        while(n > 0)
        {
            for(int i = 0; i < nLen; i++)
            {
                nDataRadix[i] = elements.at(i) / (int)pow(10, 10 - n);
                nDataRadix[i] %= 10;
            }

            RadixCountSort(nDataRadix, 10, elements, nLen);

            n--;
        }

        return;
    }
private:
    static void RadixCountSort(vector<DataType>& npIndex, int nMax, vector<DataType>& npData, int nLen)
    {
        vector<DataType> pnCount(nMax, 0);
        for(int i = 0; i < nMax; i++)
            pnCount[i] = 0;
        for(int i = 0; i < nLen; i++)
            ++pnCount[npIndex[i]];
        for(int i = 1; i < nMax; i++)
            pnCount[i] += pnCount[i - 1];

        vector<DataType> pnSort(nLen, 0);

        for(int i = nLen - 1; i >= 0; --i)
        {
            --pnCount[npIndex[i]];
            pnSort[pnCount[npIndex[i]]] = npData[i];
        }

        for(int i = 0; i < nLen; i++)
            npData[i] = pnSort[i];

        return;
    }
};

// #############################################################################
// # sorting algorithm end
int main(int argc, char** argv)
{
    int n;
    int data;
    vector<int> elements;

    // read data from input stream
    scanf("%d", &n) != 1 && (exit(-1), 0);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data) != 1 && (exit(-1), 0);
        elements.push_back(data);
    }

    // sort elements
    RadixSorter<int>::sort(elements);

    // write sorted data to output stream
    for(int i = 0; i < n; i++)
        printf("%d\n", elements.at(i));;

    return 0;
}
//
