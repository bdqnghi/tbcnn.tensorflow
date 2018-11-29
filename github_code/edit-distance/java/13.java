package matching;
import java.lang.*;

import java.io.*;
public class editdistance 
{
    public static int min(int a,int b)
    {
        return a<b?a:b; 
    }     
    
    
    public static int min3(int a,int b,int c)
    {
        return min(min(a,b),c);
    }
    
    
    public static int EditDistance( String X, String Y, int m, int n )
    {
	int left,right,corner = 0;
    // Base cases
    if( m == 0 && n == 0 )
	return 0;

    if( m == 0 )
	return n;

    if( n == 0 )
	return m;

    // Recurse
    left = EditDistance(X, Y, m-1, n) + 1;
    right = EditDistance(X, Y, m, n-1) + 1;
    if((X.charAt(m-1)!=Y.charAt(n-1)))
    {
        corner = EditDistance(X, Y, m-1, n-1)+1 ;
    }
    else
    {
        corner = EditDistance(X, Y, m-1, n-1)+0 ;
    }
            //+(X.charAt(m-1)!=Y.charAt(n-1));
            //(X[m-1] != Y[n-1]);
    //System.out.println("\t"+left+"\t"+right+"\t"+corner);
    return min3(left, right, corner);
}
 
}

