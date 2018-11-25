#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
class my_reverse{
  public:
    my_reverse();
    ~my_reverse();
    void input();
    void input_reverse();
    bool string_the_same();
    void pluss();
    void sum_plus();
    void print_answer();
    void clean();
  private:
    unsigned long times,b_reverse,a_reverse,sum,int_sum_reverse;
    char *_input,*after_reverse,*sum_string,*sum_reverse;
};
my_reverse::my_reverse()
{
  _input = new char[100];
  after_reverse = new char [100];
  sum_string = new char[100];
  sum_reverse = new char[100];
  times = 0;
  sum = 0;
  int_sum_reverse = 0;
}
my_reverse::~my_reverse()
{
  delete _input;
  delete after_reverse;
  delete sum_string;
  delete sum_reverse;
}
void my_reverse::input()
{
  cin>>_input;
}
void my_reverse::input_reverse()
{
  int j = 0;
  for(int i = strlen(_input)-1;i >= 0;i--)
  {
    after_reverse[j] = _input[i];
    j++;
  }
}
void my_reverse::pluss()
{
  b_reverse = atoi(_input);
  a_reverse = atoi(after_reverse);
  sum = b_reverse + a_reverse;
  times++;
}
void my_reverse::sum_plus()
{
  sum = atoi(sum_string);
  int_sum_reverse = atoi(sum_reverse);
  sum = sum + int_sum_reverse;
  times++;
}
bool my_reverse::string_the_same()
{
  int j = 0;
  sprintf(sum_string,"%lu",sum);
  for(int i = strlen(sum_string)-1;i >= 0;i--)
  {
    sum_reverse[j] = sum_string[i];
    j++;
  }
  int cmp = strcmp(sum_string,sum_reverse);
  if(cmp == 0)
    return true;
  else if(cmp != 0)
    return false;
}
void my_reverse::print_answer()
{
  cout<<times<<" "<<sum<<endl;
}
void my_reverse::clean()
{
  times = 0;
  sum = 0;
  int_sum_reverse = 0;
  a_reverse = 0;
  b_reverse = 0;
  for(int i = 0;i < 100;i++)
  {
    _input[i] = 0;
    after_reverse[i] = 0;
    sum_string[i] = 0;
    sum_reverse[i] = 0;
  }
}
int main()
{
  my_reverse result;
  int times;
  cin>>times;
  for(int i = 0;i < times;i++)
  {
    result.input();
    result.input_reverse();
    result.pluss();
    while(!result.string_the_same())
      result.sum_plus();
    result.print_answer();
    result.clean();
  }
  return 0;
}
