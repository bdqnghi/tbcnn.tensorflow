package exercise;

public class StringReverseStringBufferReverseTostring {
	
	// Source: http://examples.javacodegeeks.com/core-java/lang/string/java-string-reverse-example/
	
	public static void main(String[] args) {
			 
		        String str = "This was a String to reverse";
			 
			        String reverse = new StringBuffer(str).reverse().toString();
			 
			        System.out.println("Normal String is : " + str + " \nReverse String is : "+reverse);
			        
			        //This will output:

			        	//Normal String is : This was a String to reverse 
			        	//Reverse String is : esrever ot gnirtS a saw sihT

			        	//This is the easiest way you can reverse a String in Java.
			    }

}
