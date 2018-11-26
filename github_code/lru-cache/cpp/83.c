/*
  lru.cpp
  LRU Caching, MCPC 2012 Problem F
  C++ solution by Gabriel Foust
*/

#include <fstream>
#include <iostream>
#include <map>
using namespace std;

ifstream fin( "lru.in" );

int main()
{
  int cache_size;
  int count= 0;
  while (fin >> cache_size && cache_size > 0)
  {
    string cache;
    string command;
    cout << "Simulation " << ++count << endl;
    fin >> command;
    for (int i= 0; i < command.size(); ++i)
    {
      if (command[i] == '!')
        cout << (cache.empty() ? "empty" : cache) << endl;
      else
      {
        size_t pos= cache.find_first_of( command[i] );
        if (pos != string::npos)
          cache.erase( pos, 1 );
        else if (cache.size() == cache_size)
          cache.erase( 0, 1 );
        cache+= command[i];
      }
    }
  }

  return 0;
}
