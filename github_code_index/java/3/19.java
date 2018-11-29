package pracks;
import java.io.*;
public class towerofhanoi {
 public static void tower(int n,char frompeg,char usingpeg,char topeg){
	 if(n==0)
		 return;
		 else{
			 tower(n-1,frompeg,topeg,usingpeg);
			 System.out.println("Move disk "+n+" from "+frompeg+" to "+topeg);
			 tower(n-1,usingpeg,frompeg,topeg);
		 }
 }
 public static void main(String []ar ) throws IOException{
	 BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	 System.out.println("Enter The No. Of Disks: ");
	 int n=Integer.parseInt(br.readLine());
	 tower(n,'A','B','C');	 
 }
}
