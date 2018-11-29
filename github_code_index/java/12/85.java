import java.util.Scanner;

 class MatrixMultiplication {

   public static void main(String[] args) throws Exception
{
       Scanner s = new Scanner(System.in);
       System.out.print("Enter number of rows in A: ");
       int rowsInA = s.nextInt();
       System.out.print("Enter number of columns in A / rows in B: ");
       int columnsInA = s.nextInt();
       System.out.print("Enter number of columns in B: ");
       int columnsInB = s.nextInt();
       double[][] a = new double[rowsInA][columnsInA];
       double[][] b = new double[columnsInA][columnsInB];
       System.out.println("Enter matrix A");
       for (int i = 0; i < a.length; i++) {
           for (int j = 0; j < a[0].length; j++) {
               a[i][j] = s.nextDouble();
           }
       }
       System.out.println("Enter matrix B");
       for (int i = 0; i < b.length; i++) {
           for (int j = 0; j < b[0].length; j++) {
               b[i][j] = s.nextDouble();
           }
       }
       double[][] c = multiply(a, b);
       System.out.println("Product of A and B is");
       for (int i = 0; i < c.length; i++) {
           for (int j = 0; j < c[0].length; j++) {
               System.out.print(c[i][j] + " ");
           }
           System.out.println();
       }
   }

   public static double[][] multiply(double[][] a, double[][] b) {
       int rowsInA = a.length;
       double columnsInA = a[0].length; // same as rows in B
       int columnsInB = b[0].length;
       double[][] c = new double[rowsInA][columnsInB];
       for (int i = 0; i < rowsInA; i++) {
           for (int j = 0; j < columnsInB; j++) {
               for (int k = 0; k < columnsInA; k++) {
                   c[i][j] = c[i][j] + a[i][k] * b[k][j];
               }
           }
       }
       return c;
   }
}
