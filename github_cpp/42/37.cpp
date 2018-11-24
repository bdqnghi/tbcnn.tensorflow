#include<iostream>
using namespace std;
void swap(int &a, int &b) {
    int tmp = b;
    b = a;
    a = tmp;
}
int main() {
    int n;
    //input
    cout<<"Enter the no. of numbers you want to sort:";
    cin>>n;
    cout<<"Enter "<<n<<" numbers to be sorted:"<<endl;
    int *numbers = new int[n];
    for(int i = 0; i < n; ++i) {
        cin>>numbers[i];
    }    
    
    //selection sort
    int min = 2147483647;	//min element
    int min_pos = -1;		//position of min element
    for(int i = 0; i < n; ++i) {
        min = 2147483647;	//min element
        for(int j = i; j < n; ++j) {
            if(numbers[j] < min) {
                min = numbers[j];
                min_pos = j;
            }
        }
        swap(numbers[i], numbers[min_pos]);
    }
    
    //output
    cout<<"The numbers in sorted order are:"<<endl;
    for(int i = 0; i < n; ++i) {
        cout<<numbers[i]<<endl;
    }
    
    system("pause");
    return 0;	//no errors
}
