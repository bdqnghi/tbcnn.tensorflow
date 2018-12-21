import java.util.ArrayList;

public class SelectionSort_java{
  static final int N = 100000;
  
  private static void printlist(ArrayList<Integer> list){
    for(Integer i:list)
      System.out.println(list.get(i));
  }
  
  private static void reclist(ArrayList<Integer> list){
    int i = 0, num;
    do{
      num=(int)(Math.random() * N);
      list.add(num);
      i++;
    }while(i < N);
  }
  
  private static void sortlist(ArrayList<Integer> list){
    int ind = 0;
    for(int i = 0; i < list.size() - 1; i++){
      int min = list.get(i);
      for(int j = i + 1; j < list.size(); j++){
        if(list.get(j) < min){
          min = list.get(j);
          ind = j;
        }
      }
      if(min != list.get(i)){
        list.set(ind, list.get(i));
        list.set(i, min);
      }
    }
  }
  
  public static void main(String[] args) {
    ArrayList<Integer> list = new ArrayList<Integer>();
    reclist(list);
    printlist(list);
    sortlist(list);
    printlist(list);
    return;
  }
}
