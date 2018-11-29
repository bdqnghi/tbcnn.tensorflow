import java.util.Map;
import java.util.HashMap;

public class Levenshtein {

public static void main(String[] args) {

	System.out.println("La distancia de edicion entre "+args[0]+" y "+args[1]+" es: "+ editDistance(args[0], args[1]));

} 

private static Map<Pair<String,String>,Integer> cache = new HashMap<Pair<String,String>,Integer>();

public static int editDistance(String str1, String str2) {
    if (str1==null || str2==null) throw new IllegalArgumentException("Cant compute edit distance on ull strings");
    if (str1.length()==0) return str2.length();
    if (str2.length()==0) return str1.length();
    int res1 = memoEditDistance(str1.substring(1,str1.length()),str2.substring(1,str2.length()));     
    int res2 = memoEditDistance(str1,str2.substring(1,str2.length()));     
    int res3 = memoEditDistance(str1.substring(1,str1.length()),str2);     
    return minimum(res1+(str1.charAt(0)==str2.charAt(0)?0:1), res2+1, res3+1);
}

public static int memoEditDistance(String str1, String str2) {
    if (!cache.containsKey(new Pair<String,String>(str1,str2))) {
        cache.put(new Pair<String,String>(str1,str2), new Integer(editDistance(str1, str2)));
        System.out.print("Miss ");
    }
    return cache.get(new Pair<String,String>(str1,str2)).intValue();
}

private static int minimum(int a, int b, int c){
		if (a<=b && a<=c)
			return a;
		if (b<=a && b<=c)
			return b;
		return c;
}

}
