package hackerrank.hackerrank;

import java.util.Scanner;

//Java String Reverse
public class JavaStringReverse {
	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */
        int i;
        boolean flag = true;
        for(i=0; i<A.length()/2; i++){
            if(!A.substring(i,i+1).equals(A.substring(A.length()-i-1, A.length()-i))){
                flag = false;
            }
        }
        if(flag){
            System.out.println("Yes");
        }else{
            System.out.println("No");
        }
	}
}
