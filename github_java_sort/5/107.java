import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class BubbleSortJava implements JClass {
    private ArrayList<Comparable> array;

    public BubbleSortJava(){
        this.array = new ArrayList<>();
    }

    public void setup(int size){
        array.clear();
        Random rand = new Random();
        for(int i = 0; i<size; ++i){
            array.add(i,rand.nextInt());
        }
    }

    public void run(){
        int len = array.size();
        while(len > 1) {
            for (int i = 0; i < len - 1; ++i) {
                if (array.get(i).compareTo(array.get(i + 1)) > 0) {
                    Collections.swap(array,i,i+1);
                }
            }
            --len;
        }
    }
}
