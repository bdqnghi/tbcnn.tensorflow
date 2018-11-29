package dp;

import junit.framework.TestCase;
import org.junit.Test;

/**
 * Created by neha on 2/1/2017.
 */
public class RodCutting extends TestCase {

    @Test
    public static void test()
    {
        assertEquals(22,getMaxRodCutValDP(new int[]{1, 5, 8, 9, 10, 17, 17, 20},8));
        assertEquals(22,getMaxRodCutValRec(new int[]{1, 5, 8, 9, 10, 17, 17, 20},8));
    }

    public static int getMaxRodCutValRec(int price[],int n)
    {
        if(n<=0)
            return 0;
        int maxVal=Integer.MIN_VALUE,currentVal;

        for (int i = 0; i < n; i++) {

            currentVal=price[i]+getMaxRodCutValRec(price,n-i-1);
            if(currentVal>maxVal)
            {
                maxVal=currentVal;
            }
        }
        return maxVal;
    }

    public static int getMaxRodCutValDP(int price[],int n)
    {
        int val[]=new int[n+1];
        int cutLen[]=new int[n+1];

        val[0]=0;
        cutLen[0]=-1;
        int maxVal,currentVal,curCutLen;

        for (int i = 1; i < n + 1; i++) {
            maxVal=Integer.MIN_VALUE;
            curCutLen=-1;
            for (int j = 0; j < i; j++) {
                currentVal=price[j]+val[i-j-1];
                if(currentVal>maxVal)
                {
                    maxVal=currentVal;
                    curCutLen=j+1;
                }
            }
            val[i]=maxVal;
            cutLen[i]=curCutLen;
        }
        System.out.println("---------------------Cutting Length------------------------");

        for (int i = n; i > 0 ; i=i-cutLen[i]) {
            System.out.print(cutLen[i]+" ");
        }

        System.out.println("\n---------------------Cutting Length------------------------");
        return val[n];
    }
}
