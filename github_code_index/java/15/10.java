public class RodCutting{
    public static void main(String[] args){
        int[] a={2,5,7,8};
        int length=5;

        int[][] mas=new int[a.length+1][length+1];
        mas[0][0]=0;
        for(int j=0;j<=length;j++){
            for(int i=1;i<a.length+1 ;i++){

                if(j>=i){
                    mas[i][j]=Math.max(mas[i-1][j],a[i-1]+mas[i][j-1]);
                }
                else{
                    mas[i][j]=mas[i-1][j];
                }
            }
        }

        for(int i=0;i<mas.length;i++) {
            for (int j = 0; j <= length; j++) {
                System.out.print(mas[i][j]+"\t");
            }
            System.out.println();
        }

    }
}


//import java.util.Scanner;
//
//public class RodCutting {
//
//    public int Cut_Rod(int p[], int n) throws Exception{
//        if(n & gt= p.length ){
//            throw new Exception("rod of length can not grater than the price array length");
//        }
//        if (n == 0) {
//            return 0;
//        }
//        int q = Integer.MIN_VALUE;
//        for (int i = 1; i &lt;= n; i++) {
//            q = Math.max(q, (p[i] + Cut_Rod(p, n - i)));
//        }
//        return q;
//    }
//
//    public int Memoized_Cut_Rod(int p[], int n) throws Exception{
//        if(n & gt;= p.length){
//            throw new Exception("rod of length can not grater than the price array length");
//        }
//        int r[] = new int[n + 1];
//        for (int i = 0; i &lt;= n; i++) {
//            r[i] = Integer.MIN_VALUE;
//        }
//        return Memoized_Cut_Rod_Aux(p, n, r);
//    }
//
//    public int Memoized_Cut_Rod_Aux(int p[], int n, int r[]) throws Exception{
//        if(n &gt;= p.length){
//            throw new Exception("rod of length can not grater than the price array length");
//        }
//        int q;
//        if (r[n] &gt;= 0) {
//            return r[n];
//        }
//        if (n == 0) {
//            q = 0;
//        } else {
//            q = Integer.MIN_VALUE;
//            for (int j = 1; j &lt;= n; j++) {
//                q = Math.max(q, (p[j] + Memoized_Cut_Rod_Aux(p, n - j, r)));
//            }
//        }
//        r[n] = q;
//        return q;
//    }
//
//    public int Bottom_up_Cut_Rod(int p[], int n)  throws Exception{
//        if(n &gt;= p.length ){
//            throw new Exception("rod of length can not grater than the price array length");
//        }
//        int r[] = new int[n + 1];
//        r[0] = 0;
//
//        for (int j = 1; j &lt;= n; j++) {
//            int q = Integer.MIN_VALUE;
//            for (int i = 1; i &lt;= j; i++) {
//                q = Math.max(q, (p[i] + r[j - i]));
//            }
//            r[j] = q;
//        }
//        return r[n];
//    }
//
//    public void Extended_Bottom_Up_Cut_Rod(int p[], int n)  throws Exception{
//        if(n &gt;= p.length ){
//            throw new Exception("rod of length can not grater than the price array length");
//        }
//        int r[] = new int[n + 1];
//        int s[] = new int[n + 1];
//        r[0] = 0;
//        for (int j = 1; j &lt;= n; j++) {
//            int q = Integer.MIN_VALUE;
//            for (int i = 1; i &lt;= j; i++) {
//                if (q &lt; (p[i] + r[j - i])) {
//                    q = p[i] + r[j - i];
//                    s[j] = i;
//                }
//
//            } r[j] = q;
//        }
//
//        while (n &gt; 0) {
//            System.out.print(s[n] + "  ");
//            n = n - s[n];
//        }
//    }
//
//    public static void main(String args[]) throws Exception {
//        int[] p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
//
//        System.out.print("Enter the value of rod of length n = ");
//        Scanner input = new Scanner(System.in);
//        int n = input.nextInt();
//        if(n &gt;= p.length || n &lt;= 0){
//            throw new Exception("rod of length can not grater than the price array length OR n &lt;= 0");
//        }
//
//        System.out.print("[Cut_rod] Rod of Lenght = "+n+" and solution = ");
//        RodCutting rd = new RodCutting();
//        int y = rd.Cut_Rod(p, n);
//        System.out.println(y);
//
//        System.out.print("[Memozied_Cut_rod] Rod of Lenght = "+n+" and solution = ");
//        RodCutting rd1 = new RodCutting();
//        int x = rd1.Memoized_Cut_Rod(p, n);
//        System.out.println(x);
//
//        System.out.print("[Bottom_Up_Cut_rod] Rod of Lenght = "+n+" and solution = ");
//        RodCutting rd2 = new RodCutting();
//        int z = rd2.Bottom_up_Cut_Rod(p, n);
//        System.out.println(z);
//
//        System.out.print("[Extended_Bottom_Up_Cut_rod] Rod of Lenght = "+n+" and the cuts  =&gt; ");
//        RodCutting rd3 = new RodCutting();
//        rd3.Extended_Bottom_Up_Cut_Rod(p, n);
//
//    }
//}
///*
//Enter the value of rod of length n = 7
//[Cut_rod] Rod of Lenght = 7 and solution = 18
//[Memozied_Cut_rod] Rod of Lenght = 7 and solution = 18
//[Bottom_Up_Cut_rod] Rod of Lenght = 7 and solution = 18
//[Extended_Bottom_Up_Cut_rod] Rod of Lenght = 7 and the cuts  =&gt; 1  6
//BUILD SUCCESSFUL (total time: 3 seconds)
//*/