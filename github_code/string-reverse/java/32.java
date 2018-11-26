import static org.junit.Assert.*;
import org.junit.Test;

public class ReverseString {
    StringBuilder sb;
    
	public String reverse(String str) {
		sb = new StringBuilder(str);;
		// can use sb.reverse();
		for(int i = 0; i < str.length()/2; i++) {
			mirrorSwap(i);
		}
		return sb.toString();
	}
	
	private void mirrorSwap(int i) {
	    char temp = sb.charAt(i);
		sb.setCharAt(i, sb.charAt(sb.length() - i - 1));
		sb.setCharAt(sb.length() - i - 1, temp);
	}
	
	public class ReverseTests {
		
	    @Test
	    public void testDoubleReverse() {
	    	ReverseString sol = new ReverseString();
	        String str = "Some very long text";
	        System.out.println(sol.reverse(str));
	        assertEquals(sol.reverse(str), "txet gnol yrev emoS");
	        assertEquals(str, sol.reverse(sol.reverse(str)));
	    }

	    @Test
	    public void testEmpty() {
	    	ReverseString sol = new ReverseString();
	    	String str = "";
	    	assertTrue(sol.reverse(str).equals(""));
	    }
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str = "Some very long text";
		ReverseString sol = new ReverseString();
		System.out.println(sol.reverse(str));
		System.out.println(sol.reverse(sol.reverse(str)));
	}
}