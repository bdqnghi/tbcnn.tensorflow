/**
 * Created by tecso on 3/9/16.
 */
public class RodCutting {
    public static int[][] getMaxValue(int price[], int n) {
        int tmp[][] = new int[price.length + 1][n + 1]; //row - length, col - price

        for (int i = 0; i < price.length + 1; i++) {
            tmp[i][0] = 0;
        }
        for (int i = 0; i < n + 1; i++) {
            tmp[1][i] = price[0] * i;
            tmp[0][i] = 0;
        }

        for (int i = 1; i < price.length + 1; i++) {
            for (int j = 1; j < n + 1; j++) {
                if (j < i)
                    tmp[i][j] = tmp[i - 1][j];
                else
                    tmp[i][j] = Math.max(price[i - 1] + tmp[i][j - i], tmp[i - 1][j]);
                //price[i-1] bcoz treating i=1 as 1st index but still price array starts from index 0
            }
        }
        for (int i = 0; i < price.length + 1; i++) {
            for (int j = 0; j < n + 1; j++) {
                System.out.print(tmp[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println(tmp[price.length - 1][n]);

        return tmp;
    }

    public static void printCuts(int tmp[][], int price[]) {
        int i = tmp.length - 1;
        int j = tmp[0].length - 1;
        while(true){
            if(i==0 ||j==0)
                break;
            if(tmp[i-1][j]==tmp[i][j])
                i--;
            else if(tmp[i][j-1]==tmp[i][j])
                j--;
            else{
                System.out.print(i+" ");
                System.out.println(tmp[i][j]);
                j = j-i;
            }
        }

    }

    public static void main(String[] args) {
        int price[] = {2, 5, 7, 8};
        int tmp[][] = getMaxValue(price, 5);
        printCuts(tmp, price);
    }
}
