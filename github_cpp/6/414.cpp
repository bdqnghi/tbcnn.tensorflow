


#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include<time.h>



using namespace std;

void BellmanFord(vector<int>& dist, vector<int>& pred, vector<vector<int> > weights)
{
   int N = dist.size();
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         for (int k = 0; k < N; ++k)
         {         
            if (dist.at(k) > dist.at(j) + weights.at(j).at(k))
            {
               dist.at(k) = dist.at(j) + weights.at(j).at(k);
               pred.at(k) = j;
            }
         }
      }
   }
   
   // check for negative cycles
   for (int j = 0; j < N; ++j)
   {
      for (int k = 0; k < N; ++k)
      {  
         if (dist.at(k) > dist.at(j) + weights.at(j).at(k))
         {
            cout << "Graph contains a negative-weight cycle at index " << k << endl;
         }
      }
   }

} 





int main()
{
   srand (time(NULL));

   int N = 6;
   vector<vector<int> > weights;
   for (int i = 0; i < N; ++i)
   {
      vector<int> thisrow;
      for (int j = 0; j < N; ++j)
      {
         thisrow.push_back(9 - rand()%11);
      }
      weights.push_back(thisrow);
   }
   for (int i = 0; i < N; ++i)
   {
      weights.at(i).at(i) = 0;    // vertex to itself has edge = 0
   }


   cout << "Weights matrix: " << endl;
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         cout << weights.at(i).at(j) << "  ";
      }
      cout << endl;
   }
   cout << endl;


   vector<int> distances;
   distances.push_back(0);
   for (int i = 1; i < N; ++i)
   {
      distances.push_back(10000);  // de facto infinity
   }

   vector<int> predecessors;
   for (int i = 0; i < N; ++i)
   {
      predecessors.push_back(i);   // each vertex starts out as its own pred  
   }
   BellmanFord(distances, predecessors, weights);

   cout << "Shortest distances from 0 vertex:" << endl;
   for (int i = 0; i < N; ++i)
   {
      cout << distances.at(i) << " ";
   }
   cout << endl;

   cout << "Predecessors:" << endl;
    for (int i = 0; i < N; ++i)
   {
      cout << predecessors.at(i) << " ";
   }
    cout << endl;
    cout << endl;
   

////////////////
// Now use this to find solution to linear difference equations
// This problem is equivalent to finding values for the unknowns x1; x2; x3; x4; x5,
 // satisfying the following 8 difference constraints:
// x1 - x2  0 , (24.3)
// x1 - x5  -1 , (24.4)
// x2 - x5  1 , (24.5)
// x3 - x1  5 , (24.6)
// x4 - x1  4 , (24.7)
// x4 - x3  -1 , (24.8)
// x5 - x3  -3 , (24.9)
// x5 - x4  -3 . (
   int M = 5;
   vector<vector<int> > dweights;
   for (int i = 0; i < M; ++i)
   {
      vector<int> thisrow;
      for (int j = 0; j < N; ++j)
      {
         thisrow.push_back(10000);
      }
      dweights.push_back(thisrow);
   }
   dweights.at(0).at(2) = 5;
   dweights.at(0).at(3) = 4;
   dweights.at(1).at(0) = 0;
   dweights.at(2).at(3) = -1;
   dweights.at(2).at(4) = -3;
   dweights.at(3).at(4) = -3;
   dweights.at(4).at(0) = -1;
   dweights.at(4).at(1) = 1;


   vector<int> ddistances;
   ddistances.push_back(0);
   for (int i = 1; i < M; ++i)
   {
      ddistances.push_back(10000);  // de facto infinity
   }

   vector<int> dpredecessors;
   for (int i = 0; i < M; ++i)
   {
      dpredecessors.push_back(i);   // each vertex starts out as its own pred  
   }
   BellmanFord(ddistances, dpredecessors, dweights);

   cout << "Solutions to difference equations:" << endl;
   for (int i = 0; i < M; ++i)
   {
      cout << ddistances.at(i) << " ";
   }
   cout << endl;


   return 0;

}
