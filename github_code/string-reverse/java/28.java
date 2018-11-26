import java.util.StringTokenizer;

public class StringChange {
    public static void main(String[] args){
        //remove a char in string, http://www.runoob.com/java/string-removing-char.html
        String str = "this is java";
        System.out.println(removeCharAt(str, 3));

        //replace, http://www.runoob.com/java/string-replace.html
        String str1 = "hello hello world";
        System.out.println(str1.replace('h', 'w'));
        System.out.println(str1.replaceAll("he", "ab"));
        System.out.println(str1.replaceFirst("he", "ab"));

        //reverse, http://www.runoob.com/java/string-reverse.html
        String string = "runoob";
        String reverse = new StringBuffer(string).reverse().toString();
        System.out.println("before: " + string + ", after: " + reverse);

        //split
        System.out.println("---------split----------");
        String str2 = "www-runoob-com";
        String[] tmp = str2.split("-");
        for(int i=0; i<tmp.length; i++){
            System.out.println(tmp[i]);
            System.out.println();
        }

        //StringTokenizer
        String str3 = "This is String , split by StringTokenizer , created by runoob";
        StringTokenizer st = new StringTokenizer(str3);
        while(st.hasMoreElements()){
            System.out.println(st.nextElement());
        }
        StringTokenizer st2 = new StringTokenizer(str3, ",");
        while (st2.hasMoreElements()){
            System.out.println(st2.nextElement());
        }

        //to other case
        System.out.println("------to other case------");
        String str4 = "string runoob";
        String s1 = str4.toUpperCase();
        String s2 = str4.toLowerCase();
        System.out.println(s1);
        System.out.println(s2);



    }
    public static String removeCharAt(String str, int index){
        return str.substring(0, index) + str.substring(index+1);
    }
}
