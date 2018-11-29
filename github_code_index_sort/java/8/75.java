import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class QuickSortJava implements JClass{
    private ArrayList<Comparable> data;

    public QuickSortJava() {
        this.data = new ArrayList<>();
    }

    public void run() {
        sortq(0, data.size() - 1);
    }

    public void setup(int size){
        data.clear();
        Random rand = new Random();
        for(int i = 0; i<size; ++i){
            data.add(i,rand.nextInt());
        }
    }

   private void sortq(int l, int r) {
        Comparable pivot = data.get((l + r) / 2);
        int i = l;
        int j = r;
        while (i <= j) {
            while (data.get(i).compareTo(pivot) < 0) i++;
            while (data.get(j).compareTo(pivot) > 0) j--;
            if (i <= j) {
                Collections.swap(data, i, j);
                i++;
                j--;
            }
        }
        if (l < j) sortq(l, j);
        if (i < r) sortq(i, r);
   }
}
