#include<iostream> 
using namespace std;
#include<vector>
#include<algorithm>
#define Notfound -1
template<typename T>
int binarysearch(const vector<T> &t, const T &x)
{
    int beg=0,end=t.size()-1;
    while(beg<=end)
    {
        int mid=(beg+end)/2;
        if(x>t[mid])
        {
            beg=mid+1;
        }   
        else if(x<t[mid])
        {
            end=mid-1;
        }
        else 
        return mid;
    }
    return Notfound;
}

int main()
{
    vector<int> veci={12,-4,8,-45,1};
    vector<int>::iterator it=veci.begin(),it2=veci.end();
    vector<string> vecs={"my","his","her","thier"};
    vector<string>::iterator it3=vecs.begin(),it4=vecs.end();
    sort(it,it2);
    sort(it3,it4);
    int i=-45;
    string s="his";
   
    cout<<"the -45 is found in"<<binarysearch(veci,i)<<endl;
    cout<<"the his is found in"<<binarysearch(vecs,s)<<endl;
    return 0;
}
