 

import java.io.*;
class stringreverse
{
    public static void main()throws IOException
    {
        String S, W, W1;
        int i,j;
       BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
        System.out.println("Enter String");
        S=br.readLine();
         W="";
         S=S+" ";
        for (i=0;i<S.length();i++)
        {
            if (S.charAt(i)==' ')
            {
                for (j=W.length()-1;j>=0;j--)
                System.out.print(W.charAt(j));
                System.out.print(" ");
                W="";
            }
            else 
            W=W+S.charAt(i);
        }
    }
}