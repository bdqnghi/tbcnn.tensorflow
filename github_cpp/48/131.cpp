#include<iostream>
#include<string>

using std::string;

bool palindrome(string s){
    int i = 0;
    int j = s.size()-1;
    while(true){
        if(s[i]==s[j]){
            if(i<j){
                i++;
                j--;
            }else{
                return true;
            }
        }else{
            return false;        
        }
    }
}

int main(){
    string s;
    std::cin>>s;
    std::cout<<"echo:"<<s<<std::endl;
    bool ret = palindrome(s);
    std::cout<<"ret:"<<ret<<std::endl;
}
