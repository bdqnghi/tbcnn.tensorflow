package Sort;

import org.omg.Messaging.SyncScopeHelper;

//堆排序
public class Sort_heapSort {

    public static <AnyType extends Comparable<? super AnyType>>
    void heapSort(AnyType[] a){

        //第一次调整堆
        for(int i = a.length/2-1; i>=0; i--){
            percDown(a,i,a.length);
        }
        //第一次调整结束后，将根节点(即最大值)换回数组最后，
        //再比较数组剩余部分
        for(int i = a.length-1; i>0; i--){
            swapReferencec(a,0,i);
            //此时堆的根节点是最小的
            //直接往下比较就可以了
            percDown(a,0,i);
        }
    }

    //用于调整堆后，获取最大值
    private static <AnyType extends Comparable<? super AnyType>>
    void percDown(AnyType[] a, int i, int n) {

        int child;
        AnyType tmp;

        for(tmp = a[i]; leftChild(i)<n; i=child){
            child = leftChild(i);
            //第一次调整时跳过，因为child==n-1
            //比较左右儿子，选出大的跟父节点比较
            if(child != n-1 && a[child].compareTo(a[child+1])<0){
                child++;
            }
            if(tmp.compareTo(a[child])<0){
                a[i] = a[child];
                //将父节点与子节点值交换
                //但是仍不推出循环，使用i = child往下比较
            }else
                break;
        }
        a[i]=tmp;

    }

    //由某值位置，返回其左儿子位置
    private static int leftChild(int i) {
        return 2*i+1;
    }

    private static <AnyType extends Comparable<? super AnyType>>
    void swapReferencec(AnyType[] a, int i, int j) {
        AnyType tmp;
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp ;
    }

    public static void main(String[] args) {
        Integer[] a = {34,4,213,6,23,55,77,223};
        heapSort(a);
        for(int i = 0; i<a.length; i++){
            System.out.print(a[i]+" ");
        }
    }
}
