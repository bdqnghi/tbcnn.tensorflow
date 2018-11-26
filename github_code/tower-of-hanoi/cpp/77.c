#include <iostream>
#include <vector>
using namespace std;

int main(){

  vector<int> t[3];
  int n, candidate, to, from, move=0;
  
  cout << "Enter the number of rings: ";
  cin >> n;

  for(int i = n+1; i>0; i--) 
    t[0].push_back(i);
 
  t[1].push_back(n+1);
  t[2].push_back(n+1);
      
  
  from = 0;
 
  candidate = 1;
  if(n%2==0)
    to = 2;
  else
    to = 1;
  
  while( t[1].size() != n+1 ){
    
    cout << "move number " << ++move << ": Transfer ring " << candidate << " from tower " << char(from+65) << " to tower " << char(to+65) << endl;
  
    t[to].push_back(candidate);
    t[from].pop_back();
    
    if(n%2!=0)
     {
       if(t[(to+1)%3].back()>t[(to+2)%3].back())
	 from = (to+2)%3;
       else
	 from = (to+1)%3;
       
       
       if(t[from].back()>t[(from+1)%3].back())
	 to=(from+2)%3;
       else 
	 to=(from+1)%3;
     }  
    
    if(n%2==0)
      {
	if(t[(to+1)%3].back() < t[(to+2)%3].back())
          from = (to+1)%3;
        else
          from = (to+2)%3;
	

        if(t[from].back() < t[(from+2)%3].back())
          to=(from+2)%3;
        else
          to=(from+1)%3;
      }
   
      candidate = t[from].back();
  
  }
  return 0;
}
