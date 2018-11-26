package Test;

public class Stringreverse {

	public void reverse(String s1) {
		char[] s = s1.toCharArray();
		int i = 0, j = s.length - 1;
		while (i < j) {

			char temp = s[i];
			s[i] = s[j];
			s[j] = temp;
			i++;
			j--;
		}
		// for(char c:s)
		for (i = 0; i < s.length; i++) {
			char c = s[i];
			System.out.print(c);
		}
		
		
		//System.out.println(new String(s));
	}

	public static void main(String[] args) {
		String s1 = "SMITHA";
		Stringreverse reverse = new Stringreverse();
		reverse.reverse(s1);

	}

}
