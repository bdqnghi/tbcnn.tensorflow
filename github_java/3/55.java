package algorithms;

/**
 * @autor mvl on 04.09.2017.
 */
public class TowerOfHanoi {
    public static void main(String[] args) {
        int count = 3;
        System.out.println(TowerOfHanoi('A', 'B', 'C', count));
    }

    public static String TowerOfHanoi(char a, char b, char c, int count){
        String result = "";

        if (count > 1)
            result += TowerOfHanoi(a, c, b, count-1);

        if (count > 1) result += "\n";
        result += a + "->" + b;

        if (count > 1)
            result += "\n" + TowerOfHanoi(c, b, a, count-1);

        return result;
    }
}
