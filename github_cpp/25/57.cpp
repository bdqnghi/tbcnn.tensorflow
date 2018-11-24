#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

inline void exchange(char *s1, char *s2)
{
    char temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void Permutation(char*, char*);

int Permutation(char *pStr)
{
    if(pStr == NULL)
        return -1;

    Permutation(pStr, pStr);
}

void Permutation(char *pStr, char *pOriginal)
{
    static int count = 0;
    if(*pStr == '\0') {
        count++;
        cout << count << ':' << pOriginal << endl;
    }
    else {
        char *pTemp;
        for(pTemp = pStr; *pTemp != '\0'; pTemp++)
        {
            exchange(pTemp, pStr);
            Permutation(pStr + 1, pOriginal);
            exchange(pTemp, pStr);
        }
    }
}

int a[5] = {1, 2, 3, 4, 5};
vector<int> temp;
void Combination(int m, int n, int depth)
{
    if(n == 0)
	{
		for(int i = 0;i< temp.size(); i++)
			cout<<a[temp[i]]<<" ";
		cout<<endl;
		return;
	}
	for(int j = depth; j < m; j++)
	{
	   temp.push_back(j);
	   Combination(m, n - 1, j + 1);
	   temp.pop_back();
	}
}

int main()
{
    char str[64];
    cout<<"Input:"<<endl;
    cin>>str;
    Permutation(str);
    
    char re[64];
    cout<<"C(n, m): "<<"n="<<5<<" m=";
	int m;
    cin>>m;
    Combination(5, m, 0);

    return 0;
}
