package some;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;


public class BucketSort {

    public static double[] sort(double[] array){
        List<Double>[] lists = new List[array.length];
        int N = array.length;
        for(int i = 0; i < N; i++){
            lists[i] = new ArrayList<>();
        }
        for(int i = 0; i < N; i++){
            lists[(int)(N * array[i])].add(array[i]);
        }
        for(int i = 0; i < N; i++)
            Collections.sort(lists[i]);

        double[] sortResult = new double[array.length];
        int k = 0;
        for(int i = 0; i < N; i++)
            for(double v : lists[i])
                sortResult[k++] = v;
        return sortResult;
    }

    public static void main(String[] args){
        double[] array = {0.72,0.12,0.24,0.09,0.36,0.01};
        double[] result = BucketSort.sort(array);
        System.out.println(Arrays.toString(result));
        String test ="";
        test.toCharArray();
        Arrays.toString(args);
        StringBuilder builder = new StringBuilder();
    }
}
