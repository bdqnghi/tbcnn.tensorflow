package some;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * Created by sghipr on 2/05/16.
 * 桶排序.
 * 假设所有数据的取值是平均分布在[0,1)区间中.
 * 将n个输入值平均放入到n个桶中.然后分别对每个桶中的数据进行排序.最终再将所有的数据连接起来.
 *
 * 主要在于理解这种桶排序的思想.
 * 在实际生产环境中并不一定是将值局限在[0,1)的范围内.
 * 不过,这种算法的思想是相同的.
 */
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
