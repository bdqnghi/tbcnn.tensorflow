package _String._Reverse;
import java.util.*;
import org.junit.Test;

//  541. Reverse String II
//  https://leetcode.com/problems/reverse-string-ii/description/
//  String
//  Reverse String
//  Reverse Words in a String III
//
//  reverse the first k characters for every 2k
//  Input: s = "abcdefg", k = 2  |  Output: "bacdfeg"
//  4:1
//
//
public class _541_String_Reverse_String_II_E {
//------------------------------------------------------------------------------
    //1
    //Java Concise Solution
    /**
     * 0            k           2k          3k
     * |-----------|-----------|-----------|---
     * +--reverse--+           +--reverse--+
     * i          j            i+k         j+k
     */
    public class Solution1 {
        public String reverseStr(String s, int k) {
            char[] arr = s.toCharArray();
            int n = arr.length;
            int i = 0;

            while(i < n) {
                int j = Math.min(i + k - 1, n - 1);//防止j越界
                swap(arr, i, j);
                i += 2 * k;
            }
            return String.valueOf(arr);
        }

        private void swap(char[] arr, int l, int r) {//swap这个区间全部
            while (l < r) {
                char temp = arr[l];
                arr[l++] = arr[r];
                arr[r--] = temp;
            }
        }
    }

    @Test
    public void test1_1(){
        Solution1 sol = new Solution1();
        System.out.println(sol.reverseStr("123456789", 1));//123456789
        System.out.println(sol.reverseStr("123456789", 2));//213465789
        System.out.println(sol.reverseStr("123456789", 3));//321456987
        System.out.println(sol.reverseStr("123456789", 4));//432156789
        System.out.println(sol.reverseStr("1234567", 2));//2134657
    }
//------------------------------------------------------------------------------
    //2
    //[C++][Java] Clean Code
    /**
     * 0            k           2k          3k
     * |-----------|-----------|-----------|---
     * +--reverse--+           +--reverse--+
     */
    public class Solution2 {
        public String reverseStr(String s, int k) {
            char[] ca = s.toCharArray();
            for (int left = 0; left < ca.length; left += 2 * k) {
                for (int i = left, j = Math.min(left + k - 1, ca.length - 1); i < j; i++, j--) {
                    char tmp = ca[i];
                    ca[i] = ca[j];
                    ca[j] = tmp;
                }
            }
            return new String(ca);
        }
    }

//------------------------------------------------------------------------------
    //3
    //Verbose Java Solution, StringBuilder(s)
    //Tried to maximize usage of StringBuilder :)
    public class Solution3 {
        public String reverseStr(String s, int k) {
            StringBuilder sb = new StringBuilder();

            int i = 0, j = 0;
            while (i < s.length()) {
                // first k
                j = i + k <= s.length() ? i + k : s.length();
                sb.append((new StringBuilder(s.substring(i, j))).reverse().toString());

                if (j >= s.length()) break;

                // second k
                i = j;
                j = i + k <= s.length() ? i + k : s.length();
                sb.append(s.substring(i, j));

                i = j;
            }

            return sb.toString();
        }

    }




//------------------------------------------------------------------------------
    //4
    //6 lines java solution with O(n) runtime
    public class Solution4 {
        public String reverseStr(String s, int k) {
            StringBuilder res = new StringBuilder();
            for (int i = 0; i < s.length(); i++) {
                if (i % (2 * k) < k) res.insert(i - i % (2 * k), s.charAt(i));
                else res.append(s.charAt(i));
            }
            return res.toString();
        }
    }


//------------------------------------------------------------------------------
}
/*
Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.

Example:
Input: s = "abcdefg", k = 2  |  Output: "bacdfeg"



Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]
Seen this question in a real interview before?   Yes  No
Companies
Google

Related Topics
String

Similar Questions
Reverse String
Reverse Words in a String III
 */