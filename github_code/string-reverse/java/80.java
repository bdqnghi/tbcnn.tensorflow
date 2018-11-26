import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Stringreverse {
	 public static void main(String args[])throws IOException
	 {
		 BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		 String str=br.readLine();
		 String revstring="";
		 for(int i=str.length()-1;i>=0;--i)
		 {
			revstring +=str.charAt(i); 
		 }
		 System.out.println(revstring);
		 if(revstring.equalsIgnoreCase(str))
		 {
			 System.out.println("Palindrome "+str);
		 }
		 else 
		 {System.out.println("no");
	 }

}
}
