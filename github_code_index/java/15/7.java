package dp;
import java.util.Arrays;
public class RodCutting {
    public static int maxRodCut(int val[]) {
        int opt[] = new int[val.length];
        opt[0]=0;opt[1]=val[1];
        int curr=0,max=0;
        for(int i=2;i<val.length;i++) {
            for(int j=1;j<i;j++) {
                curr = opt[j] + opt[i-j];
                if (max < curr) {
                    max = curr;
                }
            }
            max = Math.max(val[i], max);
            opt[i] = max;
            System.out.println(Arrays.toString(opt));
        }
        return opt[val.length-1];
    }
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        int val[] = {0, 1,5, 8, 9,10, 17, 17, 20};
        System.out.println(maxRodCut(val));
    }

}
