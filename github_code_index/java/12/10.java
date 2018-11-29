package java_matrix_multiplication;

public class Java_Matrix_Multiplication {

    public static void carpim(int[][] a, int[][] b) {

        //Sonuç matrisi yaratılıyor.
        int[][] c = new int[a.length][b[0].length];

        //Çarpma işlemi yapılıyor.
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < b[0].length; j++) {
                for (int k = 0; k < b.length; k++) {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
            }
        }

        //Sonuç ekrana yazdırılıyor.
        for (int i = 0; i < c.length; i++) {
            for (int j = 0; j < c[0].length; j++) {
                System.out.print(c[i][j] + " ");
            }
            System.out.println();
        }

    }

    public static void printScreen(int[][] c) {
        for (int i = 0; i < c.length; i++) {
            for (int j = 0; j < c[0].length; j++) {
                System.out.print(c[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        //Örnek olarak iki 3x3 lük iki matris yaratiliyor.
        Java_Matrix_Multiplication jmm = new Java_Matrix_Multiplication();
        int[][] a = new int[][]{{1, 2, 3}, {3, 3, 3}, {5, 6, 2}};
        System.out.println("A matrisi : ");
        jmm.printScreen(a);
        int[][] b = new int[][]{{1, 5, 3}, {2, 9, 6}, {7, 8, 5}};
        System.out.println("B matrisi : ");
        jmm.printScreen(b);
        System.out.println("Carpim matrisi : ");
        jmm.carpim(a, b);

    }
}
