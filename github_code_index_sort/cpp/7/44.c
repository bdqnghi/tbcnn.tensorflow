// #############################################################################
// # FileName:  Shell.cpp
// # Author:    Lonely, CS0901, HUST
// #############################################################################
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

// # sorting algorithm begin
// #############################################################################
template<typename DataType> class ShellSorter
{
public:
    static void sort(vector<DataType>& elements)
    {
        int insertPos, scanPos, delta = elements.size();

        while(delta > 0)
        {
            for(int i = 0; i < delta; i++)
            {
                scanPos = i + delta;
                while(scanPos < elements.size())
                {
                    DataType temp = elements.at(scanPos);
                    for(insertPos = scanPos; insertPos > i && temp < elements.at(insertPos - delta); insertPos -= delta)
                        elements.at(insertPos) = elements.at(insertPos - delta);
                    elements.at(insertPos) = temp;
                    scanPos += delta;
                }
            }
            delta = (delta + 1) / 2.2;
        }
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
    ShellSorter<int>::sort(elements);

    // write sorted data to output stream
    for(int i = 0; i < n; i++)
        printf("%d\n", elements.at(i));;

    return 0;
}
// #############################################################################
// # EOF
