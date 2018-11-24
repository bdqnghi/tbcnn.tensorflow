#include<bits/stdc++.h>
using namespace std;
#define infinity 99999999
/*
input:
5 8
0
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3
*/

int main()
{
    vector<int>edge[10000];
    int numofv,numofe;
    cout<<"Enter the number of vertices and edges "<<endl;
    cin>>numofv>>numofe;

    int distance[numofv+1];
    for(int i=0;i<numofv+5;i++)
    {
          edge[i].clear();
         distance[i]=infinity;
    }

    cout<<"Enter the source vertex "<<endl;
    int source;
    cin>>source;
    distance[source]=0;
    cout<<"Enter the edges and their corresponding weight"<<endl;
    int src,des,weight;
    for(int i=0;i<numofe;i++)
    {
        cin>>src>>des>>weight;
        edge[i].push_back(src);
        edge[i].push_back(des);
        edge[i].push_back(weight);

    }
    for(int i=1;i<=numofv-1;i++)
    {
        int j=0;
        while(edge[j].size()!=0)
        {
            if(distance[edge[j][0]]+edge[j][2]<distance[edge[j][1]])
            {
                distance[edge[j][1]]=distance[edge[j][0]]+edge[j][2];
            }
            j++;
        }
    }
    cout<<"     vertices\tdistance"<<endl;
    for(int i=0;i<numofv;i++)
        cout<<"\t"<<i<<"\t"<<distance[i]<<endl;
}

