// My HackerRank Submissions
//@Author - Devendra Kushwah
import java.io.*;
import java.util.*;

public class Solution {
       public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        int lengthOfA = A.length()-1;
        String answer = "Yes";
        for(int i =0; i<lengthOfA; i++){
            if(A.charAt(i)==A.charAt(lengthOfA-i))
                continue;
            else{
                answer ="No";
                break;
            }
        }
        System.out.println(answer);
    }
}