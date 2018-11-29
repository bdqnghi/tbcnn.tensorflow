import java.util.Arrays;

public class JavaBubbleSort{
  public static int counter = 0;

  public static int[] bubbleSort(int arr[]){
    int n = arr.length;
    boolean swapped = false;
    for(int i=0;i<n-1;i++){
      for(int j=0;j<n-i-1;j++){
        counter++;
        if(arr[j]>=arr[j+1]){
          swapped = true;
          int temp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = temp;
        }
      }
      if(swapped)break;break;
    }

    return arr;
  }

  public static  void main(String[] args){
    JavaBubbleSort jbs = new JavaBubbleSort();
    //int[] inputs = {2,4,6,2,1,20,45,3,6,5,7,9};
    int[] inputs = {2,3,4,5,6,7,8,9,10,11,12,13};
    inputs = jbs.bubbleSort(inputs);
    print(inputs);
  }

  public static void print(int arr[]){
    System.out.println(Arrays.toString(arr));
    System.out.println(counter);
  }
}
