package Programming;



public class StringReverseExample {

    public static void main(String args[])  {

        //original string
        String str = "Sony is going to introduce Internet TV soon";
        System.out.println("Original String: " + str);

        //reversed string using Stringbuffer
        String reverseStr = new StringBuffer(str).reverse().toString();
        System.out.println("Reverse String in Java using StringBuffer: " + reverseStr);

        //iterative method to reverse String in Java
        reverseStr = reverse(str);
        System.out.println("Reverse String in Java using Iteration: " + reverseStr);

        //recursive method to reverse String in Java
        reverseStr = reverseRecursively(str);
        System.out.println("Reverse String in Java using Recursion: " + reverseStr);
        //substitution method to reverse String in Java
        reverseStr = reverseChar2(str);
        System.out.println("Reverse String in Java using substitution: " + reverseStr);

    }

    public static String reverse(String str) {
        StringBuilder strBuilder = new StringBuilder();
        char[] strChars = str.toCharArray();

        for (int i = strChars.length - 1; i >= 0; i--) {
            strBuilder.append(strChars[i]);
        }

        return strBuilder.toString();
    }

    public static String reverseRecursively(String str) {

        //base case to handle one char string and empty string
        if (str.length() < 2) {
            return str;
        }

        return reverseRecursively(str.substring(1)) + str.charAt(0);

    }
    public static String reverseChar(String s){
    	String rever_s="";
    	char [] str_arr = s.toCharArray();
    	for (int i=0;i<s.length()/2;i++){
    		char temp = str_arr[i];
    		str_arr[i] = str_arr[s.length()-i-1];
    		str_arr[s.length()-i-1] = temp;
    	}
    	for (int i=0;i<s.length();i++){
    		rever_s += str_arr[i];
    	}
    	return rever_s;
    } 
    public static String reverseChar2(String s){
    	String rever_s="";
    	for (int i=s.length()-1;i>=0;i--){
    		rever_s += s.charAt(i);
    	}
    	return rever_s;
    } 
}


