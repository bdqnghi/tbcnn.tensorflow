#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <unordered_map>

using namespace std;


void bfs(vector<vector<int> > & matrix, vector<int> & visited , int start)
{

    deque<int> q;
    visited[start-1] = -1;


    

    for(int i=0; i< matrix.at(start-1).size(); i++)
    {
            visited[matrix.at(start-1).at(i)-1] = 1;
            
            q.push_back(matrix.at(start-1).at(i));
           
    }

    
    
    int counter = 2;
    int scounter = 0;
    int s = q.size();

    while (!q.empty())
    {
        
        int de = q.front() -1;
        
        
        q.pop_front();
        scounter++;
            
        if (scounter == s)
            {
                
                counter++;
                scounter = 0;
                s = q.size();
            }

        for(int i=0; i<matrix.at(de).size(); i++) 
        {
            if (visited[matrix.at(de).at(i)-1] == 0) 
            {
                q.push_back(matrix.at(de).at(i));
                visited[matrix.at(de).at(i)-1] = counter;


            }





        }
    }




}

int main()
{
    int tests, n;
    cin >> tests;
    for(int i=0; i<tests; i++)
    {
        int edges;
        cin >> n >> edges;
        vector <vector<int> > matrix(n);
        vector<int> visited(n);


        for(int j=0; j<edges; j++)
        {
            int a, b;
            cin >> a >> b;
            matrix.at(a-1).push_back(b);
        }
        

        int start;
        cin >> start;

        bfs(matrix, visited, start);
        for(int i=0; i<visited.size(); i++)
        {
            if (visited[i] == -1)
            {

            }
            else if (visited[i] == 0)
            {
                cout << "-1" << " ";
            }
            else
            {
                cout << visited[i] * 6 << " ";
            }
        }



        


    }
}



