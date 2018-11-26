
public class stringreverse {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//check whether string is palindrome or not
		
		String s = "madam";
		String t ="";
		for(int i=s.length()-1;i>=0;i--)
		{
			t = t+ s.charAt(i);//strings are similar to array but when we can to get the index we want to specify array like s[i]
			                                //where as strings as s.charAt(i);
				}

		if (s==t)
		{
			System.out.println("palindrome");
		}

	}

}
//we can concatnte using + operator in strings