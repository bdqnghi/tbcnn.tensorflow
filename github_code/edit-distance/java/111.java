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
    	
/*    	for(int i=0;i<X.length();i++)
    	{
    		if(Y.charAt(i)=='-')
    		{y[i]=(char) (Y.charAt(i)+Y.charAt(i+1)); i++;}
    		else
    			y[i]=Y.charAt(i);	
    		System.out.print("Y"+y[i]);

    	}
    	for(int i=0;i<Y.length();i++)
    	{
    		if(Y.charAt(i)=='-')
    		{y[i]=(char) (Y.charAt(i)+Y.charAt(i+1)); i++;}
    		else
    			y[i]=Y.charAt(i);	
    		System.out.print("Y"+y[i]);
    	}
  */  	
    	
    	if(Y.contains(X))
    return 0;
    	else
    return 1;
    }
 
}

