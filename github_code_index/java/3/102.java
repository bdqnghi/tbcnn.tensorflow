package ctci.recursionDP;

import java.util.Stack;

/**
 * Created by raula on 3/3/2017.
 */
public class TowerOfHanoi {
    public static void main(String[] args) {
        Stack<Integer> source = new Stack();
        Stack<Integer> dest = new Stack();
        Stack<Integer> buf = new Stack();
        int n=7;
        for (int i = n; i >0 ; i--) {
            source.push(i);
        }

        moveDisks(source, buf,dest,n);
        while(!dest.isEmpty()) System.out.println(dest.pop());
        while(!source.isEmpty()) System.out.println(source.pop());
        while(!buf.isEmpty()) System.out.println(buf.pop());
    }

    private static void moveDisks(Stack<Integer> source, Stack<Integer> buf, Stack<Integer> dest,int n) {
        if (n==1){
            dest.push(source.pop());
        }else{
            moveDisks(source,dest,buf,n-1);
            dest.push(source.pop());
            moveDisks(buf,source,dest,n-1);
        }

    }
}
