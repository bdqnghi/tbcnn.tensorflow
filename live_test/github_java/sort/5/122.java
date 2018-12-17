package practicalseven.sort;



public class BubbleSort extends Sorter {

  
  private static int ARRAY_START = 0;

  
  public BubbleSort() {
    name = "BubbleSort";
  }

  
  public char[] sort(char[] source) {
    int length = source.length;
    char[] sorted = new char[source.length];
    
    return sorted;
  }

  
  public int[] sort(int[] source) {
    int length = source.length;
    int[] sorted = new int[source.length];
    
    return sorted;
  }

  
  public static void main(String[] args) {
    char[] letters = {'C', 'E', 'B', 'D', 'A', 'I', 'J', 'L', 'K', 'H', 'G', 'F'};
    System.out.println("Before: " + java.util.Arrays.toString(letters));
    char[] sortedLetters = (new BubbleSort()).sort(letters);
    System.out.println("After : " + java.util.Arrays.toString(sortedLetters));
    int[] numbers = {1, 2, 4, 4, 9, 10, -10, 3, 8, 7, 20, 0};
    System.out.println("Before: " + java.util.Arrays.toString(numbers));
    int[] sortedNumbers = (new BubbleSort()).sort(numbers);
    System.out.println("After : " + java.util.Arrays.toString(sortedNumbers));
  }
}
