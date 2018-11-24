//http://community.topcoder.com/stat?c=problem_statement&pm=2356&rd=4740

// You are arranging a weird game for a team building exercise. In this game there are certain locations that people can stand at, and from each location there are paths that lead to other locations, but there are not necessarily paths that lead directly back. You have everything set up, but you need to know two important numbers. There might be some locations from which every other location can be reached. There might also be locations that can be reached from every other location. You need to know how many of each of these there are.

// Create a class TeamBuilder with a method specialLocations that takes a String[] paths that describes the way the locations have been connected, and returns a int[] with exactly two elements, the first one is the number of locations that can reach all other locations, and the second one is the number of locations that are reachable by all other locations. Each element of paths will be a String containing as many characters as there are elements in paths. The i-th element of paths (beginning with the 0-th element) will contain a '1' (all quotes are for clarity only) in position j if there is a path that leads directly from i to j, and a '0' if there is not a path that leads directly from i to j.



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <set>

using namespace std;


void Floyd(vector<vector<int> >& dist)
{
   int max = dist.size();

   for (int k = 0; k < max; ++k)
   {
      for (int i = 0; i < max; ++i)
      {
         for (int j = 0; j < max; ++j)
         {
            (dist.at(i)).at(j) = min((dist.at(i)).at(j) , 
                                (dist.at(i)).at(k) + (dist.at(k)).at(j) );
         }
      }
   }
}



int main() 
{
   // define adjacency matrix
 
   // ifstream matrixfile("matrix1.txt");
   // int Z = 100;

   ifstream matrixfile("matrix2.txt");
   int Z = 1000;

   vector<vector<int> > adj;
   string thisline;
   while(matrixfile.good())
   {
      getline(matrixfile, thisline);
      stringstream ss(thisline);
      vector<int> thisrow;
      while(ss.good())
      {
         string curr;
         ss >> curr;
         if (curr != "")
         {
            thisrow.push_back((atoi)(curr.c_str()));
         }
      }
      if (thisrow.size() > 0) {adj.push_back(thisrow);}      
   }


  
   for (vector<vector<int> >::iterator it = adj.begin(); it != adj.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }

   // apply Floyd-Warshall algorithm

    Floyd(adj);

    cout << endl;

   for (vector<vector<int> >::iterator it = adj.begin(); it != adj.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }

   // let Z be a large number (much larger than the matrix entries, say 1000)
   // for row i, count the number of entries Z or more not in the ith column: if none, then vertex i can reach all other vertices
   // for column j, count the number of entries Z or more not in the ith row: if none, then vertex j can be reached by all other vertices.
   int max = adj.size();
   set<int> cannot_reach;
   set<int> cannot_be_reached;
   for (int i = 0; i < max; ++i)
   {
      for (int j = 0; j < max; ++j)
      {
         if ( (adj.at(i)).at(j) >= Z && i != j)
         {
            cannot_reach.insert(i);
            cannot_be_reached.insert(j);
         }
      }
   }


   cout << "Vertices that can reach all others: ";
   for (int i = 0; i < max; ++i)
   {
      if (cannot_reach.find(i) == cannot_reach.end())
      {
         cout << i << " ";
      }
   }
   cout << endl;


   cout << "Vertices that can be reached by all others: ";
   for (int i = 0; i < max; ++i)
   {
      if (cannot_be_reached.find(i) == cannot_be_reached.end())
      {
         cout << i << " ";
      }
   }
   cout << endl;



}
