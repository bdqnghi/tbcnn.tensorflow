import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        String pos="No";
        char ch[]=A.toCharArray();
        int n=A.length();
        int i,j;
        for(i=0,j=n-1;i<=j;i++,j--)
        {
            if(ch[i]==ch[j]){pos="Yes";}
            else{pos="No"; break;}
        }
        System.out.print(pos);
        /* Enter your code here. Print output to STDOUT. */
        
    }
}
