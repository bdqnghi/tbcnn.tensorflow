/*
 ============================================================================
 Nome        : Sorting Algorithm - Bubble Sort(Ordenação por Flutuação)
 Autor       : Renan Watanabe
 Data        : 24/05/2017
 Explicação  : Percorrer o vetor diversas vezes, a cada passagem fazendo flutuar para o topo o maior elemento da sequência.

 Links       : https://pt.wikipedia.org/wiki/Bubble_sort
               https://www.toptal.com/developers/sorting-algorithms/bubble-sort
               http://www.geeksforgeeks.org/bubble-sort/

Youtube      : https://www.youtube.com/watch?v=nmhjrI-aW5o
 ============================================================================
 */

public class BubbleSort{

    public static void main(String[] args){
        int[] meuArray = {3, 8, 15, 10, 1, 2, 3};
        exibirValores(meuArray);
        ordenarBubbleSort(meuArray);
        exibirValores(meuArray);
    }

    private static void ordenarBubbleSort(int meuArray[]){

        for(int i = 0; i < meuArray.length; ++i){
            for(int j = 0; j < meuArray.length - i - 1; ++j){
                if(meuArray[j] > meuArray[j+1]){
                    int temporario = meuArray[j];
                    meuArray[j] = meuArray[j+1];
                    meuArray[j+1] = temporario;
                }
            }
        }
    }

    private static void exibirValores(int meuArray[]){
        for(int i = 0; i < meuArray.length; ++i){
            System.out.print(meuArray[i] + " ");
        }
        System.out.println();
    }
    
}
