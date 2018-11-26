import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
	Scanner sc=new Scanner(System.in);
	String s1=sc.nextLine();
	String s2=sc.nextLine();
	String s3=s1.concat(" " +s2);
	System.out.println(s3);
	String s4[]=s3.split(" ");
	for(int i=0;i<s4.length;i++){
	StringBuilder a=new StringBuilder(s4[i]);
	System.out.print(a.reverse() +" ");
	}
}
}
