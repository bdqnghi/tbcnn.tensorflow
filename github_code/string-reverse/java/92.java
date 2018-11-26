package cn.itcast.test.others.algorithm.recursive;

/**
 * 	Write a program to reverse a string using recursive methods. 
 * 	You should not use any string reverse methods to do this.
 * 
 * @author Vince Xu Yuan
 */
public class RecursiveForStringReverse {

	/**
	 * 	This is the main function to execute the algorithm
	 * @param args
	 */
	public static void main(String[] args) {
		
		/*	Show the reverse string	 */
		System.out.println("Reverse result: " + reverseString("Hello Java!"));
	}

	/**
	 * 	This is the method to reverse a string
	 * @param string
	 * @return
	 */
	private static String reverseString(String string) {
		
		/*	Intialize a null string for reverse string	*/
		String reverseString = "";
		
		/*	If the string length is 1, then directly output the string	*/
		if (string.length() == 1) {
			return string;
		
		/*	Else reverse the string using recursive method	*/
		} else {
			reverseString += string.charAt(string.length() - 1)
					+ reverseString(string.substring(0, string.length() - 1));
			return reverseString;
		}
	}
}
