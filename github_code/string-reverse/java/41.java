public class Stringreverse {
	public void run(String s)
	{
		System.out.println("Original String: " + s);
		String reversed = "";
		int i = s.length() - 1;
		while(i >= 0){
			reversed = reversed + s.charAt(i);
			i--;
		}
		System.out.println("Reversed String: " + reversed);
	}
	
	public void runWithoutTempVariable(String s)
	{
		System.out.println("Now lets see that without using a second string variable and only 1 temp.");
		System.out.println("Original String: " + s);
		int i = s.length() - 1;
		while(i >= (s.length() - 1) / 2){
			char temp = s.charAt(i);
			s = this.insertChar(s, s.charAt(((s.length() - 1) - i)), i);
			s = this.insertChar(s, temp, ((s.length() - 1) - i));
			i--;
		}
		System.out.println("Reversed String: " + s);
	}
	
	private String insertChar( String s, char j, int myIndex){
		String newString;
	
		StringBuilder builderString = new StringBuilder(s);
		builderString.setCharAt(myIndex, j);
		newString = builderString.toString();
	
		return newString;
	}
}