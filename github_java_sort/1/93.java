

public class InsertionSort{

    public static void main(String[] args){
        int[] meuArray = {3, 8, 15, 10, 1, 2, 3};
        exibirValores(meuArray);
        ordenarInsertionSort(meuArray);
        exibirValores(meuArray);
    }

    private static void ordenarInsertionSort(int meuArray[]){
        for(int i = 1; i < meuArray.length; ++i){
            int valor = meuArray[i];
            int j = i - 1;

            while(j >= 0 && meuArray[j] > valor){
                meuArray[j+1] = meuArray[j];
                j = j - 1;
            }
            meuArray[j+1] = valor;
        }
    }

    private static void exibirValores(int meuArray[]){
        for(int i = 0; i < meuArray.length; ++i){
            System.out.print(meuArray[i] + " ");
        }
        System.out.println();
    }
}
