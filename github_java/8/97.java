package HW7;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Scanner;
import java.util.Vector; 

public class editdistance {

    Vector<String> Ve= new Vector<String>(5,3);
    Vector<String> Ne= new Vector<String>(5,3);
    public  int min (int x, int y, int z){ //create a method to find the min value among 3 numbers
		int temp =x; 
		    if (temp > z) temp = z;
		    System.out.print(temp);
	}
    
	public void readfile(String inputFile) throws FileNotFoundException {
		InputStream in = new FileInputStream(inputFile);
		Scanner scan = new Scanner(in);
		while(scan.hasNext()) //read the file line by line
		{
			String str = scan.nextLine();
		    Ve.add(str);
		}
		scan.close();
	
	for (int j=0 ; j<Ve.size(); j++){ //for each line, load each word in a vector 
		Scanner scan2 = new Scanner(Ve.get(j));
		while(scan2.hasNext()){
	
	    String str2 = scan2.next();
		Ne.add(str2);
		
	}
		scan2.close();}
	

	
     for (int i=0 ; i<Ve.size()-1; i++){
    	 String a = Ve.get(i);//get pair of stings
    	 String b = Ve.get(i+1);
    	 int c;
    	 int contents[][] = new int[a.length()][b.length()];//declare a 2D vector to compare the distance of two strings
    	 for(int j = 0; j <= a.length(); j ++) {contents[j][0] = j;};
    	 for(int k = 0; k <= b.length();k ++) {contents[0][k] = k; };
    	 for(int j = 1; j <= a.length(); j ++)  {             //use a double loop to calculate the distance between two strings.
    	         for(int k = 1; k <= b.length(); k ++) {
    	                 if(a.substring(j, j+1) == b.substring(k, k+1)) {c = 0;}
    	                 else 
    	                 {c = 1; 
    	                 contents[j][k] = min(contents[j-1][k] + 1, contents[j][k-1] + 1, contents[j-1][k-1]+c);}
    	                 System.out.print( contents[j][k]+" ");
    	         }
    	 }
     }
     
	}
}
	
	
	
	
	
	
	
	
	
