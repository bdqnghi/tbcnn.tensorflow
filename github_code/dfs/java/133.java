import java.util.*;

public class depthfirstsearch {
        public static void main(String[] args)
        {
            Scanner sc = new Scanner(System.in);
            int q = sc.nextInt();
            while(q --> 0)
            {
                int n = sc.nextInt();
                int leap = sc.nextInt();
                int[] game = new int[n];
                for(int i=0;i<n;i++)
                {
                    game[i] = sc.nextInt();
                }
                System.out.println( canwingame(game,leap,0) ? "yes" : "no" );
            }
            sc.close();
        }
        public static boolean canwingame(int[] game,int leap,int m)
        {
            if(m<0 || game[m]==1) { return false; }
            else if (m+1 >= game.length || m+leap >= game.length)  { return true; }
            game[m] = 1;
            return canwingame(game,leap,m+1) || canwingame(game,leap,m-1) || canwingame(game,leap,m+leap);
        }
}
