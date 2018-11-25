

const int KEY_NOT_FOUND = -1;
int binary_search(int data[], int key, int min, int max)
{
  
  while (max >= min) {
    int mid = (min + max) / 2; 
    if(data[mid] == key) 
      return mid; 
    
    else if (data[mid] < key)
      min = mid + 1; 
    else         
      max = mid - 1; 
  }
  return KEY_NOT_FOUND; 
}





int binarySearch(int data[], int value, int low, int high) 
{
  while (low <= high) {
    int middle = (low + high) / 2;
    if (data[middle] == value)
      return middle;
    else if (data[middle] > value)
      high = middle - 1;
    else
      low = middle + 1;
    }
  return KEY_NOT_FOUND;
}

int main()
{
}
