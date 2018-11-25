



#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;



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



int main(int argc, char** argv)
{
    int n;
    int data;
    vector<int> elements;

    
    scanf("%d", &n) != 1 && (exit(-1), 0);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data) != 1 && (exit(-1), 0);
        elements.push_back(data);
    }

    
    ShellSorter<int>::sort(elements);

    
    for(int i = 0; i < n; i++)
        printf("%d\n", elements.at(i));;

    return 0;
}


