package algorithm;

/**
 * 原始字符串反转
 * @version 1.00 28 Jul 2018
 * @author Fortune F.Yu
 */
public class Stringreverse {

	/*
	 * 通过String类的charAt()的方法来获取字符串中的每一个字符，然后将其拼接为一个新的字符串
	 */
	public static String charAtreverse(String s) {
		String reverse = "";
		for(int i=0;i<s.length();i++) {
			reverse = s.charAt(i) + reverse;
		}
		return reverse;
	}
	
	
	/*
	 * 通过String的toCharArray()方法获得字符串中的每一个字符并转换为字符数组，
	 * 然后用一个空的新字符串从后向前一个个的拼接成新的字符串
	 */
	public static String  toCharArrayreverse(String s) {
		char[] array = s.toCharArray();
		String reverse = "";
		for(int i=array.length -1;i>0;i--) {
			reverse = reverse + array[i];
		}
		return reverse;
	}
	
	
	/*
	 * 通过StringBuiler的reverse()的方法
	 */
	public static String StringBuilerreverse(String s) {
		StringBuilder sb = new StringBuilder(s);
		String reverse = sb.reverse().toString();
		return reverse;
	}
	
	
	/*
	 * 利用递归，取字符串的左右两部分子串s(0, length / 2)和s（length / 2，length-1），交换左右顺序拼接形成新的字符串
	 * 其中左右子串内部亦做左右交换拼接，直至所有子串返回新的字符串为止
	 */
	public static String recursiverreverse(String s) {
		int length = s.length();
		if (length < 2) {
			return s;
		}
		String Left = s.substring(0,length/2);
		String right = s.substring(length/2 ,length);
		String reverse = recursiverreverse(right) + recursiverreverse(Left);
		return reverse;
	}
	

}
