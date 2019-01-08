public void sort(Integer[] array, int from, int end) {   
        quickSort(array, from, end);   
    }   
  
      
    private void quickSort(Integer[] array, int low, int high) {   
          
        if (low < high) {   
            
            
            
            int pivot = partition2(array, low, high);   
            
            
              
            quickSort(array, low, pivot - 1);   
            quickSort(array, pivot + 1, high);   
        }   
  
    }   
  
      
    