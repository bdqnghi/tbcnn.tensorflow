import java.util.Arrays;

public class JavaSelectionSort{

  public int[] selectionSort(int[] arr){
    int n = arr.length;
    for(int i=0;i<n-1;i++){
      int index=i;
      for(int j=i+1;j<n;j++){
        if(arr[j] < arr[index]){
          index=j;
        }
        int temp = arr[i];
        arr[i] = arr[index];
        arr[index] = temp;
      }
    }
    return arr;
  }

  public static void main(String args[]){
    JavaSelectionSort jss = new JavaSelectionSort();
    int[] arr = {6,5,7,9,2,0,4,20,15};
    print(arr);
    arr = jss.selectionSort(arr);
    print(arr);
  }
  public static void print(int[] arr){
    System.out.println(Arrays.toString(arr));
  }
}
