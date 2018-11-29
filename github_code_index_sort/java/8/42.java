/**
 * @created on : 28-ago-2017, 12:04:52
 * @see
 * @since
 * @version
 * @author Raul Vela Salas
 */
package java_celia.t5ArrayColecciones.Ordenacion;

public class JavaQuickSort {

//                          0   1   2   3   4   5   6  7   8   9  
    static int[] vector = {90, 50, 100, 70, 80, 60, 20, 10, 30, 40};

//                        0       9
    void ordenaArray(int iz, int de) {

        int i, j, x, w;

        i = iz;
        j = de;
//      50 =        v50[3]
        x = vector[(iz + de) / 2];

        do {
//                    v14[0] < 50
            while (vector[i] < x) {
                i++; // 0 1 / 3 4 / 5 6
            }
//                 3 <   v34[9]
            while (x < vector[j]) {
                j--; // 5 4 / 3 2 / 5 4 / 5 4
            }
//              2 <= 9 
            if (i <= j) {
//           v102 =   v102[2]
                w = vector[i];
//                 v34[2] =     34[9]
                vector[i] = vector[j];
//                 102[9] = v102 // Machaca el anterior valor
                vector[j] = w;
                i++;  // 3 <= 9
                j--; // 3 <= 8
            }
        } while (i <= j);

//          
        w = vector[i];
        vector[i] = vector[de];
        vector[de] = w;

        if (iz < j) {
            ordenaArray(iz, j);
        }
        if (i < de) {
            ordenaArray(i, de);
        }
    }

    public static void main(String[] args) {

        JavaQuickSort j = new JavaQuickSort();
        j.ordenaArray(0, 9);

        for (int i = 0; i < vector.length; i++) {
            System.out.println(vector[i]);
        }

    }
}
