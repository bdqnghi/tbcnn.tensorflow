#include<iostream>
using namespace std;
void swap(int &a, int &b) {
    int tmp = b;
    b = a;
    a = tmp;
}
int main() {
    int n;
    
    cout<<"Enter the no. of numbers you want to sort:";
    cin>>n;
    cout<<"Enter "<<n<<" numbers to be sorted:"<<endl;
    int *numbers = new int[n];
    for(int i = 0; i < n; ++i) {
        cin>>numbers[i];
    }    
    
    
    int min = 2147483647;	
    int min_pos = -1;		
    for(int i = 0; i < n; ++i) {
        min = 2147483647;	
        for(int j = i; j < n; ++j) {
            if(numbers[j] < min) {
                min = numbers[j];
                min_pos = j;
            }
        }
        swap(numbers[i], numbers[min_pos]);
    }
    
    
    cout<<"The numbers in sorted order are:"<<endl;
    for(int i = 0; i < n; ++i) {
        cout<<numbers[i]<<endl;
    }
    
    system("pause");
    return 0;	
}
