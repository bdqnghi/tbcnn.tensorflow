import java.util.*;
import java.lang.*;
import java.io.*;
class Ideone
{
	public static void main (String[] args) throws java.lang.Exception
	{
		int t=0;
		String s1="wipro technologies bangaluru";
		System.out.println("GIVEN INPUT-"+s1);
		String s2=s1.toUpperCase();
		System.out.println("UPPER CASE OF INPUT-"+s2);
		String[] c=s2.split(" ");
		String[] a=s1.split(" ");
		String[] b=new String[10];
	           StringBuilder n1=new StringBuilder();
	           n1.append(s1);
	           System.out.println("REVERSE OF INPUT-"+n1.reverse());
	           String n3=n1.toString();
	           String[] z=n3.split(" ");
	           System.out.println("CAMELCASE - REVERSE STRING:");
	           for(int i=0;i<z.length;i++)
		{
			String y1=z[i].substring(1);
			char x=z[i].charAt(0);
			char j=Character.toUpperCase(x);
			System.out.print(j+y1+"\t");
		}
		System.out.print("\n");
		System.out.println("CAMELCASE - GIVEN STRING:");
		for(int i=0;i<a.length;i++)
		{
			String y1=a[i].substring(1);
			char x=a[i].charAt(0);
			char j=Character.toUpperCase(x);
		             b[i]=j+y1;
			System.out.print(b[i]+"\t");
		}
		System.out.print("\n");
		System.out.println("REVERSE:");
		for(int j=a.length-1;j>=0;j--){
			StringBuilder n2=new StringBuilder();
 n2.append(b[j]);
	           System.out.print(n2.reverse()+"\t");
	           }
		System.out.print("\n");
		System.out.println("ONLY FISRT LETTER SMALL:");
            	for(int i=0;i<c.length;i++)
		{
			
			String y1=c[i].substring(1);
			char x=a[i].charAt(0);
			char j=Character.toLowerCase(x);
		             b[i]=j+y1;
			System.out.print(b[i]+"\t");
		}
	}
}
    GIVEN INPUT-wipro technologies bangaluru
    
    UPPER CASE OF INPUT-WIPRO TECHNOLOGIES BANGALURU
    
    REVERSE OF INPUT-urulagnab seigolonhcet orpiw
    
    CAMELCASE - REVERSE STRING:
    Urulagnab	Seigolonhcet	Orpiw
    
    CAMELCASE - GIVEN STRING:
    Wipro	Technologies	Bangaluru
    
    REVERSE:
    urulagnaB	seigolonhceT	orpiW
    
    ONLY FISRT LETTER SMALL:
    wIPRO	tECHNOLOGIES	bANGALURU	

