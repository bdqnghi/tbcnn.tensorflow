public class SelectionSort{
  private void printArray(int[] array){
    for(int i = 0 ; i < array.length; i++){
      System.out.print(array[i]+"  ");
    }
    System.out.println();
  }

  private void swapArrayElements(int[] array, int indexa, int indexb){
    int tmp = array[indexa];
    array[indexa] = array[indexb];
    array[indexb] = tmp;
  }

  public void selectionSort(int[] arrayToSort){
    int indexMinJ;
    for(int i = 0; i < arrayToSort.length - 1; i++){
      indexMinJ = i;
      for(int j = i+1; j< arrayToSort.length; j++){
        if(arrayToSort[j] < arrayToSort[indexMinJ]){
          indexMinJ = j;
        }
      }
      if(indexMinJ!= i) {
        swapArrayElements(arrayToSort,i,indexMinJ);
      }
      
      System.out.println("Sorting : Pass "+i);
      printArray(arrayToSort);
    }
  }
}
