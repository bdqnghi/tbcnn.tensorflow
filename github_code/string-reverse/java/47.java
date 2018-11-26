package strRev;

// String " This is a test
//CASE 1
	/*
	 * Returns the Reversed string i.e reversed to "tset a si sihT"
	 * This case is handled in the public String reverse(String userInput) function.
	 * NOTE: Recursive below too does the same thing as CASE1.public String recursiveReverseString(String s)
	 * 

//CASE 2
	 * Reverese the words i.e reversed to "test a is this"
	 * This case is handled in the public String reverse(String[] source)
	 * 

// CASE 3 
	* Reverse the words within a sentence i.e "sihT si a tsert"
	* This case ia a combination of CASE1 and CASE2
	* i.e Reverse the entire string first and then reverse the words.
	* 
*/
public class reverse {
	public static void main(String args[]) {
		ReverseString rs = new ReverseString();
		String str = "String to     be reversed.";
		// String[] str = "What is going on".split(" ");
		String newStr = rs.reverse(str);
		System.out.println(newStr);

	}
}

class ReverseString {
	
	//  CASE 1: Method a)Recursive
		public String recursiveReverseString(String s) {
			if (s.length() == 0)
				return s;

			return recursiveReverseString(s.substring(1)) + s.charAt(0);
		}

		//  CASE 1: Method b) Reverse a sentence without the word being reversed...similar to the
		// recursive.
		
		public String reverse(String userInput) {
			StringBuffer temp = new StringBuffer();
			for (int i = userInput.length() - 1; i >= 0; i--) {
				temp.append(userInput.charAt(i));
			}
			
			// return temp.toString()
			String newStr = temp.toString();
			newStr = reverse(newStr.split("\\b"));
			return newStr.toString();
		}
	
	// CASE2: Reverse the words.
	public String reverse(String[] source) {
		StringBuffer sb = new StringBuffer();
		for (int i = source.length; i-- > 0;) {
			sb.append(source[i]);
		}
		return sb.toString();
		// System.out.println("[" + sb.toString() + "]");

	}
}
