import java.util.ArrayList;
import java.util.List;

public class app {
    public static void main(String[] args) {
        List<Integer> list = new ArrayList<>();
        list.add(5);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(1);
        System.out.println(list.toString());
        mergeSort(list);
        System.out.println(list.toString());
    }

    public static List<Integer> mergeSort(List<Integer> list) {
        if (list.size() == 1) {
            return list;
        }
        mergeSort(list.subList(0, list.size() / 2));
        mergeSort(list.subList(list.size() / 2, list.size()));
        return list;
    }
//    MERGE-SORT(L: List with n elements) : Ordered list with n elements
//    IF (list L has one element)
//    RETURN L.
//    Divide the list into two halves A and B.
//            A ← MERGE-SORT(A).
//    B ← MERGE-SORT(B).
//    L ← MERGE(A, B).
//    RETURN L.
}
