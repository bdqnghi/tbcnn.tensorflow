import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */
        Stack stk = new Stack();
        Queue que = new LinkedList();
        for(int i=0;i<A.length();i++){
            stk.push(A.charAt(i));
            que.add(A.charAt(i));
        }
        while(!stk.isEmpty() && !que.isEmpty()){
            if(stk.pop() != que.remove()){
                System.out.println("No");
                return;
            }
        }
        System.out.println("Yes");
    }
}
