




#include <iostream>
#include <string>
#include <inttypes.h>
using namespace std;

bool
isUnique(string str)
{
  
  if(str.size() >= 256) return false;

  
  bool bucket[256] = {}; 

  for(size_t i=0; i<str.size(); ++i)
  {
    
    
    if(bucket[str[i]]) 
    
    
      return false;
    
    bucket[str[i]] = true;
  }

  return true;
}

bool
isUniqueV2(string str)
{
  
  if(str.size() >= 256) return false;

  
  uint64_t bucket[4] = {};

  for(size_t i=0; i<str.size(); ++i)
  {
    int index = str[i] / 64; 
    int bit   = str[i] % 64; 

    
    
    if( (bucket[index] & (1 << bit)) != 0)
    {
      cout << " Duplicate character: " << str[i] << endl;
      return false;
    }
    bucket[index] |= (1 << bit);
  }

  return true;
}

int
main()
{
  string input;
  cout << " Please input : ";
  getline (cin, input); 

  if(isUniqueV2(input))
    cout << " this string has all unique characters." << endl; 
  else
    cout << " this is not a unique string." << endl;

  return 0;
}
