package DPBegins;

import java.util.Scanner;

public class RodCutting {
    public static void main(String[] args) {
//        int[] cutcost={0,2,6,7,10,8,9,12,11};
//        maxcostcut(cutcost);

        Scanner scanner = new Scanner(System.in);
        int length = scanner.nextInt();
        int[] arr = new int[length];
        for (int l = 0 ; l < length ; l++){
            arr[l] = scanner.nextInt();
        }
        int val = rcm(arr, length - 1, new int[length]);
        System.out.println(val);
    }


    public static int rcm(int[] arr, int rl, int[] qb) {

        if (rl == 0){
            return 0;
        }

        if (qb[rl] != 0)
            return qb[rl];

        int msp = arr[rl];
        int left = 1;
        int right = rl - 1;
        while (left <= right){
            int mspl = rcm(arr, left, qb);
            int mspr = rcm(arr, right, qb);
            if (msp < mspl + mspr){
                msp = mspl + mspr;
            }

            left++;
            right--;
        }
        qb[rl] = msp;
        return msp;
    }

    private static void maxcostcut(int[] cutcost) {
        int[] maxcost=new int[cutcost.length];
        String[] maxpath=new String[cutcost.length];
        maxcost[0]=cutcost[0];
        maxcost[1]=cutcost[1];
        maxpath[0]="";
        maxpath[1]="1";

        for(int i=2;i<cutcost.length;i++) {
            maxcost[i]=cutcost[i];
            maxpath[i]=i+"";

            for (int left = 1, right = i-1; left <= right; left++, right--) {
                if (maxcost[i]<maxcost[left]+maxcost[right]){
                    maxcost[i]=maxcost[left]+maxcost[right];
                    maxpath[i]=maxpath[left]+maxpath[right];
                }
            }
        }

        System.out.println(maxcost[maxcost.length-1]);
        System.out.println(maxpath[maxpath.length-1]);
    }


}
