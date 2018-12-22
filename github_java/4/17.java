 import  java.util.Scanner ;
public class insertionsort {
   


    public  static  void  main ( String [] args ) {
        // declarando o objeto
        Scanner tcl =  new  Scanner ( System.in);
        // declarando o vetor
        int vetor [] = new int [5];
        // atribuindo valores a ele
        for( int i =  0 ; i < vetor.length; i ++ ) {
            vetor [i] = tcl . nextInt ();
        }
        int aux;
        // deixar o vetor no aux
        for( int i =  0 ; i < vetor.length; i ++ ) {
            aux = vetor [i];
            // verify
            for( int j = i - 1 ; j >=  0 && vetor[j] > aux; j -- ) {
            vetor [j +  1 ] = vetor [j];  
            vetor [j] = aux;  
            }
        }
        System.out.println("");
        // mostrar na tela
        for( int i =  0 ; i < vetor.length; i ++ ) {
            System.out.print(vetor [i]+"\t");
        }
    }
    
}

