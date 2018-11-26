package algos;

import java.util.Deque;
import java.util.LinkedList;

class StringReverseString {

    public String reverseVowels(String s) {
    	if(s.length() <= 1) return s;
        Deque<Integer> vPos = new LinkedList<>();
        for (int i = 0; i < s.length(); i++) {
			if("AEIOUaeiou".indexOf(s.charAt(i)) != -1) {
				vPos.offer(i);
			}
		}
        char[] ch = s.toCharArray();
        while(!vPos.isEmpty()) {
        	Integer p1 = vPos.pollFirst();
        	Integer p2 = vPos.pollLast();
        	if(p2 != null) {
        		char temp = ch[p1];
        		ch[p1] = ch[p2];
        		ch[p2] = temp;
        	}
        }
        return new String(ch);
    }

}