/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
//-------------------------------------------------
// check if a string has all unique characters
// i.e. "helo" -> true, "hello" -> false
//-------------------------------------------------
#include <iostream>
#include <string>
#include <inttypes.h>
using namespace std;

bool
isUnique(string str)
{
  // if length bigger than 256, it must have duplicate character
  if(str.size() >= 256) return false;

  // use idea of Bucket-sort to find the duplicate character
  bool bucket[256] = {}; // remember every ASCII character

  for(size_t i=0; i<str.size(); ++i)
  {
    // mark the appeared character to true
    // if already set true, report the duplicated character
    if(bucket[str[i]]) 
    //{
    //  cout << " Duplicate character: " << str[i] << endl;
      return false;
    //}
    bucket[str[i]] = true;
  }

  return true;
}

bool
isUniqueV2(string str)
{
  // if length bigger than 256, it must have duplicate character
  if(str.size() >= 256) return false;

  // use idea of Bucket-sort to find the duplicate character
  uint64_t bucket[4] = {};

  for(size_t i=0; i<str.size(); ++i)
  {
    int index = str[i] / 64; // which bucket should be check
    int bit   = str[i] % 64; // which bit in the bucket should be check

    // mark the appeared character to true
    // if already set true, report the duplicated character
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
