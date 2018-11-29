public class ShellSort {

  public static void sort(int[] sortMe) {

    for(int i=sortMe.length/(3); i>=0; i--) {
      sort(sortMe, 3*i+1);
    }

    System.out.println(prettyPrint(sortMe));
  }

  private static int[] sort(int[] sortMe, int shellSize) {
    if(shellSize <= 0) return new int[0];


    int temp;
    // System.out.println("Shell Sort " + shellSize);
    for (int i=shellSize; i<sortMe.length; i+=shellSize) {

      for (int j=i-shellSize; j>=0; j-=shellSize) {
     
        // System.out.println(i + " " + j);
       
      
        if( sortMe[j] > sortMe[j+shellSize] ) {
          temp = sortMe[j];
          sortMe[j] = sortMe[j+shellSize];
          sortMe[j+shellSize] = temp;
        }
      }
    }
    return sortMe;
  }
  
  private static String prettyPrint(int[] printMe) {
    String retMe = "";

    for(int i=0; i<printMe.length; i++) {
      retMe += printMe[i] + " ";
    }

    return retMe;
  }

}
