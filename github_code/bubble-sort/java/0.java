import java.util.Scanner;

public class Problems {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        System.out.println("Enter n, then values: ");

        int n = Integer.parseInt(stdin.nextLine());
        String input = stdin.nextLine();
        String[] splitIn = input.split(" ");

        int t;
        int swapCount = 0;
        int passCount = 1;

        int[] intValues = new int[n];

        for (int k = 0; k < n; k++) {
            intValues[k] = Integer.parseInt(splitIn[k]);
        }
        /////////////////////////////
        while (!sortCheck(intValues, n)) {
            for (int i = 0; i < n - 1; i++) {
                if (intValues[i] > intValues[i + 1]) {
                    swapCount++;
                    t = intValues[i];
                    intValues[i] = intValues[i + 1];
                    intValues[i + 1] = t;
                }
            }
        passCount++;
        }
        System.out.println(passCount + " " + swapCount);
    }
    private static boolean sortCheck(int[] intValues, int n) {
        boolean check = true;
        for(int j=0; j<n-1; j++) {
            if(intValues[j]>intValues[j+1]) {
                check = false;
            }
        }
        return check;
    }
}
