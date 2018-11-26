package _String._Reverse;
import java.util.*;
import org.junit.Test;

//  344. Reverse String
//  https://leetcode.com/problems/reverse-string/
//
//  Two Pointers String
//
//  Reverse Vowels of a String
//  Reverse String II
//  4:1 string转为char[]后对撞型双指针翻转array。
//  Given s = "hello", return "olleh".
public class _344_String_Reverse_String_E {
//------------------------------------------------------------------------------
    //1
    //https://discuss.leetcode.com/topic/43296/java-simple-and-clean-with-explanations-6-solutions
    //[JAVA] Simple and Clean with Explanations [6 Solutions]
    //https://www.ratchapong.com/algorithm-practice/leetcode/reverse-string [Full solutions]
    public class Solution1 {
        public String reverseString(String s) {
            char[] word = s.toCharArray();
            int i = 0;
            int j = s.length() - 1;
            while (i < j) {
                char temp = word[i];
                word[i] = word[j];
                word[j] = temp;
                i++;
                j--;
            }
            return new String(word);
        }
    }

//------------------------------------------------------------------------------
    //2
    //https://discuss.leetcode.com/topic/43296/java-simple-and-clean-with-explanations-6-solutions
    //Approach: Iterative Swapping Using Two Pointers
    //留意下这个位运算的swap方法
    public class Solution2 {
        public String reverseString(String s) {
            char[] word = s.toCharArray();
            int i = 0;
            int j = s.length() - 1;
            while (i < j) {
                word[i] = (char) (word[i] ^ word[j]);
                word[j] = (char) (word[i] ^ word[j]);
                word[i] = (char) (word[i] ^ word[j]);
                i++;
                j--;
            }
            return new String(word);
        }
    }

//------------------------------------------------------------------------------
    //3
    //https://discuss.leetcode.com/topic/43296/java-simple-and-clean-with-explanations-6-solutions
    //记着byte也可以转为String
    public class Solution3 {
        public String reverseString(String s) {
            byte[] bytes = s.getBytes();
            int i = 0;
            int j = s.length() - 1;
            while (i < j) {
                bytes[i] = (byte) (bytes[i] ^ bytes[j]);
                bytes[j] = (byte) (bytes[i] ^ bytes[j]);
                bytes[i] = (byte) (bytes[i] ^ bytes[j]);
                i++;
                j--;
            }
            return new String(bytes);
        }
    }

//------------------------------------------------------------------------------
    //4
    //Java- easiest method- 2-line code, attach ed another method
    //就是用了StringBuilder好利用StringBuilder的reverse方法，作弊呀
    class Solution4{
        //method 1: use StringBuilder
        public String reverseString(String s) {
            StringBuilder sb = new StringBuilder(s);
            return sb.reverse().toString();
        }

        //method 2: use swap method
        public String reverseString2(String s){
            if(s == null || s.length() == 0)
                return "";
            char[] cs = s.toCharArray();
            int begin = 0, end = s.length() - 1;
            while(begin <= end){
                char c = cs[begin];
                cs[begin] = cs[end];
                cs[end] = c;
                begin++;
                end--;
            }

            return new String(cs);
        }
    }

//------------------------------------------------------------------------------
}
/*
Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".

Seen this question in a real interview before?   Yes  No
Related Topics
Two Pointers String

Similar Questions
Reverse Vowels of a String
Reverse String II
 */