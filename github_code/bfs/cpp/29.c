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


    //push_back and pop_front

    for(int i=0; i< matrix.at(start-1).size(); i++)
    {
            visited[matrix.at(start-1).at(i)-1] = 1;
            //cout << matrix.at(start-1).at(i);
            q.push_back(matrix.at(start-1).at(i));
           // cout << q.front() << endl;
    }

    //while queue isn't empty, keep going
    //all in queue right now branded as 1
    int counter = 2;
    int scounter = 0;
    int s = q.size();

    while (!q.empty())
    {
        //dequeue
        int de = q.front() -1;
        //cout << de + 1 << endl;
        //cout << q.front() << endl;
        q.pop_front();
        scounter++;
            //if statement to check if tier/level is completed
        if (scounter == s)
            {
                //reached end of level
                counter++;
                scounter = 0;
                s = q.size();
            }

        for(int i=0; i<matrix.at(de).size(); i++) //adj list
        {
            if (visited[matrix.at(de).at(i)-1] == 0) //unvisited
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
        /*
        cout << endl;
        //print out the edges
        for(int j=0; j<n; j++)
        {
            for(int k = 0; k <matrix.at(j).size(); k++)
            {
                cout << j+1 << " " << matrix.at(j).at(k);
            }
        cout << endl;

        }*/

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



        //edges now in


    }
}


/*
Seriously reconsider the indexing: either use the 0 standard and stay with it or go with
the 1 standard. Don't try to change every index and reference to it.
*/
