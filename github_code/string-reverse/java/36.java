//Francisco Sanchez Enriquez
import java.util.Scanner;


public class Lerning {
	public static void main(String[] args) {
		

            Scanner in = new Scanner(System.in);
	    String a = in.next();	    
            int lenght = a.length();
            String array[] = new String [lenght];
            int j=lenght, counter=0;
            
            for(int i=0; i<lenght; i++){
            String character;
            character = a.substring(i, i+1);
            array[i]=character;            
            }
                   
            for(int i=0; i<lenght; i++){
               if(array[i].equals(array[j-1])){
               counter++;             
               }
                j--;
            }
            
            if(counter==lenght){
            System.out.println("Yes");
            }else{                       
            System.out.println("No");
            }
    }	
}     