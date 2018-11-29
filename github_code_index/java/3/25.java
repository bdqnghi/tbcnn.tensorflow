import java.util.*;

public class TowerOfHanoi
{
    public static void main(String[] args) {
        towerOfHanoi(4);
        System.out.println();
        System.out.println();
        towerOfHanoi(7);
        System.out.println();
        System.out.println();
        towerOfHanoi(21);
    }


    public static void towerOfHanoi(int n) {
        List<Stack<Integer>> pegs = new ArrayList<Stack<Integer>>();
        for(int i=0; i<3; ++i) {
            pegs.add(new Stack<Integer>());
        }
        for(int i=n; i>0; --i) {
            pegs.get(0).push(new Integer(i));
        }
        transfer(n, pegs, 0, 1, 2);
    }

    private static void transfer(int n, List<Stack<Integer>> pegs, int from, 
            int to, int intermediary)
    {
        if(n>0) {
            transfer(n-1, pegs, from, intermediary, to);
            pegs.get(to).push(pegs.get(from).pop());
            System.out.println("Block " + n + " moved from " + 
                    from + " to " + to);
            transfer(n-1, pegs, intermediary, to, from);
        }
    }
}
