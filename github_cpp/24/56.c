#include <iostream.h>

char compare (int x, int y)
{
  if (x > y) return '>';
  else if (x < y) return '<';
       else return '=';
}

int BinarySearch (int *a, int x, const int left, const int right)

{
  if (left <= right) {
     int middle = (left + right)/2;
     switch (compare (x, a[middle])){
	 case '>': return BinarySearch(a, x, middle+1, right); 
	 case '<': return BinarySearch(a, x, left, middle-1);  
	 case '=': return middle; 
     } 
  } 
  return -1;
}


void main()
{
   int b[10];
   b[0] = 2; b[1] = 4; b[2] = 5; b[3] = 7; b[4] = 10;
   b[5] = 12; b[6] = 14; b[7] = 15; b[8] = 17; b[9] = 25;

   cout << BinarySearch(b,2,0,9) << " in position 0\n";
   cout << BinarySearch(b,4,0,9) << " in position 1\n";
   cout << BinarySearch(b,5,0,9) << " in position 2\n";
   cout << BinarySearch(b,7,0,9) << " in position 3\n";
   cout << BinarySearch(b,10,0,9) << " in position 4\n";
   cout << BinarySearch(b,12,0,9) << " in position 5\n";
   cout << BinarySearch(b,14,0,9) << " in position 6\n";
   cout << BinarySearch(b,15,0,9) << " in position 7\n";
   cout << BinarySearch(b,17,0,9) << " in position 8\n";
   cout << BinarySearch(b,25,0,9) << " in position 9\n";
   cout << BinarySearch(b,-1,0,9) << " in position -1\n";
   cout << BinarySearch(b,9,0,9) << " in position -1\n";
   cout << BinarySearch(b,27,0,9) << " in position -1\n";
}
