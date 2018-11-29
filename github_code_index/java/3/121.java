package misc.algos;

import java.util.Arrays;

/**
 * Created by Anand_Rajneesh on 10/20/2016.
 */
public class TowerOfHanoi {

    public static void main(String[] args) {
        int[] src = {1,2,3,4};
        int[]dest = new int[4];
        int[]tmp = new int[4];
        play(src,tmp,dest,4);
        Arrays.stream(dest).forEach(System.out::println);
    }
    public static void play(int[]src, int[]tmp, int[]dest, int discs){
        if(discs==0)return;
        play(src,dest,tmp,discs-1);
        System.out.println("Move ");
        dest[discs-1] = src[discs-1];
        play(tmp,src,dest,discs-1);
    }


}
