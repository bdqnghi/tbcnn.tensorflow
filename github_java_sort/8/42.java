
package java_celia.t5ArrayColecciones.Ordenacion;

public class JavaQuickSort {


    static int[] vector = {90, 50, 100, 70, 80, 60, 20, 10, 30, 40};


    void ordenaArray(int iz, int de) {

        int i, j, x, w;

        i = iz;
        j = de;

        x = vector[(iz + de) / 2];

        do {

            while (vector[i] < x) {
                i++; 
            }

            while (x < vector[j]) {
                j--; 
            }

            if (i <= j) {

                w = vector[i];

                vector[i] = vector[j];

                vector[j] = w;
                i++;  
                j--; 
            }
        } while (i <= j);


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
