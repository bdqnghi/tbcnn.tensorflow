#ifndef STACKUTIL
#define STACKUTIL


template <class Stack>
void insert(const typename Stack::value_type& x, Stack& s) 
{
  if (s.empty() || x > s.top()) {
    s.push(x);
  } else {
    auto t = s.top();
    s.pop();
    insert(x, s);
    s.push(t);
  }
}


template <class Stack>
void stacksort(Stack& s) 
{
  if (!s.empty()) {
    auto t = s.top();
    s.pop();
    sort(s);
    insert(t, s);
  }
}


template <class Stack>
Stack stacksort_iterative(Stack& s) 
{
  Stack result;
  while (!s.empty()) {
    auto t = s.top();
    s.pop();
    while (!result.empty() && t < result.top()) {
      s.push(result.top());
      result.pop();
    }
    result.push(t);
  }
  return result;
}

#endif
