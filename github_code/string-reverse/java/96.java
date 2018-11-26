package com.anteoy.dataStructuresAndAlgorithm.dahaiguai.zhoudazhuang;

/**
 * Created by zhoudazhuang
 * Date: 17-4-1
 * Time: 下午3:06
 * Description : 字符串倒序 优化速度和空间
 */
public class Stringreverse {

    public static String stringreverse1(String aa) {

        char[] chars = aa.toCharArray();
        char[] charsnew = new char[chars.length];
        for (int i = 0; i < chars.length; i++) {
            charsnew[i] = chars[chars.length - i - 1];
        }

//        System.out.println(String.valueOf(charsnew));//charsnew.toString() char的实现方式不同 不能使用toString
        return String.valueOf(charsnew);
    }


    public static String stringreverse2(String aa) {

        char[] chars = aa.toCharArray();
        for (int i = 0; i < chars.length / 2; i++) {//注意chars.length/2
            char tmp;
            tmp = chars[i];
            chars[i] = chars[chars.length - i - 1];
            chars[chars.length - i - 1] = tmp;
        }
        return String.valueOf(chars);
    }

    /**
     * from niuk 和我的第二种方法思路差不多
     * 链接：https://www.nowcoder.com/questionTerminal/dc3542438f3f4dc5ba3e2ce66b44a20e
     * 来源：牛客网
     * 例如 str ="abcd" 
     *  长度是4 ，只需要进行a 与d  b 与 c交换
     * 声明两个指针 head ,tail.
     * head = str ; //指向头
     * tail= len-1;//指向尾节点
     * 让head和 tail交换,然后head++ ;tail--;
     *
     * @param str
     * @return
     */
    static String reverString(String str) {
        if (str == null || str.length() == 0) {
            return str;
        }
        char[] chArr = str.toCharArray();
        char tmp = '\0';//redundant 多余的
        int head = 0;
        int tail = chArr.length - 1;
        while (head < tail) {
            tmp = chArr[head];
            chArr[head] = chArr[tail];
            chArr[tail] = tmp;
            head++;
            tail--;
        }
        return new String(chArr);
    }

    public static void main(String[] args) {
        System.out.println(stringreverse1("abcd"));
        System.out.println(stringreverse2("abcd"));
        System.out.println(reverString("abcd"));
    }
}
