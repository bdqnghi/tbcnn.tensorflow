/**
 * M�todo Heal-Sort - ordena um array de Strings.
 * 
 * @author Jo�o Moreira Dias
 * @version Sexta-feira, 8 de Junho de 2012
 */
public class heap{
    /**
     * M�todo main - o main do programa.
     * 
     * @param   Nada  N�o Tem
     */    
    public static void main(){
        //Declara��o do indice.
        int i;
        
        //Declara��o de uma array de contactos.
        String arr[] = {"Abilio", "Isabel", "Ricardo", "Paula", "Fernando"};

        //Imprimir uma introdu��o ao codigo
        System.out.println("15) Implementar o m�todo Heap-Sort, para ordena��o de um conjunto de");
        System.out.println("registos (em cada registo, a chave � um nome com, at� 15 caracteres).");
        System.out.println("O programa dever� apresentar os passos principais do processo de ordena��o.\n\n");;
        System.out.println("Por: Jo�o Moreira Dias - 24972");
        System.out.println("Universidade Portucalense Infante D. Henrique\n\n");

        System.out.println("Array N�o-ordenada\n---");

        //Ciclo para escrever a array n�o ordenada.      
        for (i = 0; i < arr.length; i++)
            System.out.print(arr[i]+" ");

        //Ciclo para carrega a array e o upper bound da mesma para a funcao de ordenamento.
        for(i=arr.length; i>1; i--){
            fnSortHeap(arr, i - 1);
        }

        System.out.println("\n\n\nArray Ordenada\n---");

        //Ciclo para escrever a array ordenada.
        for (i = 0; i < arr.length; i++)
            System.out.print(arr[i]+" ");

        System.out.println("\n\n-FIM-");
    }

    /**
     * M�todo fnSortHeap - Fun��o de ordenamento por m�todo Heap-Sort.
     * 
     * @param  array[]      A array de stings que � passada pelo main.
     * @param  arr_ubound   N�mero de indice do upper bond da array passada como parametro.
     */
    public static void fnSortHeap(String array[], int arr_ubound){
        //Declara��o do indice i.
        int i;
        
        //Declara��o do indice a.
        int a;
        
        //Declara��o do filho esquerdo.
        int filhoE;
        
        //Declara��o do filho direito. 
        int filhoD;
        
        //Declara��o do filho minimo.
        int filhoM;
        
        //Declara��o da raiz.
        int raiz;
        
        //Declara��o de uma String de armazenamento de dados temporaria.
        String temp;
        
        //Dar o valor da raiz para ser no meio dos valores da array
        raiz = (arr_ubound-1)/2;

        //Ciculo para percorer a heap
        
        //
        for(a = raiz; a >= 0; a--){
            for(i=raiz; i>=0; i--){
                filhoE = (2*i)+1;
                filhoD = (2*i)+2;
                if((filhoE <= arr_ubound) && (filhoD <= arr_ubound)){
                    if(array[filhoD].compareTo (array[filhoE])>=0)
                        filhoM = filhoD;
                    else
                        filhoM = filhoE;
                }
                else{
                    if(filhoD > arr_ubound)
                        filhoM = filhoE;
                    else
                        filhoM = filhoD;
                }

                if(array[i].compareTo(array[filhoM])<0){
                    //As seguintes linhas de c�digo s�o um "swap" entre o array[i] e o filhoM. Onde o filhoM � actualizdo
                    temp = array[i];
                    array[i] = array[filhoM];
                    array[filhoM] = temp;
                }
            }
        }
        
        //As seguintes linhas de codigo s�o um "swap" entre attay[0] e o array[arr_ubound]
        temp = array[0];
        array[0] = array[arr_ubound];
        array[arr_ubound] = temp;
        
        return;
    }
}