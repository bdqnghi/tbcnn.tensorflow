// Author: Jiangtong Li
// Date: 2017.5.28 01:50
#include<iostream>
using namespace std ;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return 0 ;
        int lengthMax = 1 ;
        while(x/lengthMax >= 10)
            lengthMax *= 10 ;
        while(lengthMax > 0){
            if((x%10) != (x/lengthMax))
                return 0 ;
            x = ((x % lengthMax)/10) ;
            lengthMax /= 100 ;
        }
        return 1 ;
    }
};

int main(){
    int a = 1000030001 ;
    bool b ;
    Solution A ;
    b = A.isPalindrome(a) ;
    cout << b ;
    return 0 ;
}
