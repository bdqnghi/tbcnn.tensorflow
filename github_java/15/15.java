public class rodcutting {
    static int[] p = new int[10];
    static int q;
    static int[] vals = new int[10];

    public static int max(int arg1, int arg2) {
        return arg1 > arg2 ? arg1 : arg2;
    }

    public static int cutRod(int n) {
        int k;
        if (n == 0)
            return 0;
        q = -999999;
        for (int i = 1; i <= n; i++) {
            if(vals[n-i] !=0 )
                k = vals[n-i];
            else
                k = cutRod(n-i);
            q = max(q, p[i] + k);
        }
        vals[n] = q;
        return q;
    }
    public static int bottomUp(int n){
        int [] r = new int[n+1];
        r[0] = 0;
        for(int j = 1; j<=n;j++){
            int q = -99999;
            for(int i=1;i<=j;i++){
                q = max(q,p[i]+r[j-i]);

            }
            r[j] =q;

        }
        return r[n];
    }
    public static int bottomUpCutInclCutCost(int n,int costPerCut){
        int [] pMinusCutCost = new int[n+1];
        int [] r = new int[n+1];
        for(int k = 1; k<=n;k++){
            pMinusCutCost[k] = p[k]-costPerCut;
        }
        r[0] = 0;
        for(int j = 1; j<=n;j++){
            int q = -99999;
            for(int i=1;i<=j;i++){
                q = max(q,pMinusCutCost[i]+r[j-i]);

            }
            r[j] =q;
        }
        return r[n]+costPerCut;
    }

    public static void main(String[] args) {
        int opt;
        p[1] = 6;
        p[2] = 9;
        p[3] = 14;
        p[4] = 20;
        p[5] = 26;
        p[6] = 29;
        p[7] = 35;
        p[8] = 40;
        p[9] = 43;
        opt = cutRod(9);
        //opt = bottomUp(9);
        System.out.println(opt);
    }
}