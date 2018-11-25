#include <string>
#include <vector>
#include <iostream>

using namespace std;

void quickSort(vector<int>& arr, int left, int right) {
      int i = left, j = right; 
      int tmp;
      int pivot = arr[(left + right)/2]; 
      
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };


 
  
      
   
      if (left < j)
            quickSort(arr, left, j);
   
      if (i < right)
            quickSort(arr, i, right);
     
     
     
     
}

int main(){
      int n;
      cin >> n;
      vector<int> a(n);
      for(int a_i = 0;a_i < n;a_i++){
            cin >> a[a_i];
      }
      quickSort(a, 0, n-1);
      cout << "DONE" << endl;
      for (int k=0; k<a.size();k++) {
            cout << a[k] << " ";
      }
      cout << endl;
      return 0;
}