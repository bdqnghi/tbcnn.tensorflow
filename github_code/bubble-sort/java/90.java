package AlgoritmoBubbleSort;

import java.io.FileWriter;
import java.io.IOException;

public class MainCSVBubble2AndBubbleAndSelection {

    public static void main(String[] args) {

        // Fila com os valores Crescentes
        try {
            Popula p = new Popula();
            // Aqui definimos o local de criacao do arquivo CSV, no meu Ubuntu coloquei esta
            // rota
            FileWriter writer = new FileWriter("/home/dev3/Documentos/arrayBubbleSort2AndBubbleSortAndSelectionSort.csv");

            // Faz o cabeçalho do arquivo CSV

            writer.append("BubbleSort2-Cresc,");
            writer.append("BubbleSort2-Decresc,");
            writer.append("BubbleSort2-Aleatorio,");
            writer.append("BubbleSort-Cresc,");
            writer.append("BubbleSort-Decresc,");
            writer.append("BubbleSort-Aleatorio,");
            writer.append("SelectionSort-Cresc,");
            writer.append("SelectionSort-Decresc,");
            writer.append("SelectionSort-Aleatorio,");

            writer.append('\n');
            for (int n = 1; n <= 100; n++) {
                int[] crescenteVar      = new int[n];
                int[] decrescenteVar    = new int[n];
                int[] aleatorioVar      = new int[n];

                // Adicionando os elementos na filaCrescentes
                p.crescente(crescenteVar);
                p.decrescente(decrescenteVar);
                p.aleatorio(aleatorioVar);

                BubbleSort2 bubblesort21 = new BubbleSort2();
                BubbleSort2 bubblesort22 = new BubbleSort2();
                BubbleSort2 bubblesort23 = new BubbleSort2();

                BubbleSort bubblesort1 = new BubbleSort();
                BubbleSort bubblesort2 = new BubbleSort();
                BubbleSort bubblesort3 = new BubbleSort();

                SelectionSort selection1 = new SelectionSort();
                SelectionSort selection2 = new SelectionSort();
                SelectionSort selection3 = new SelectionSort();

                // Escreve no arquivo CSV
                writer.append(bubblesort21.recebeVetor(crescenteVar) + ",");
                writer.append(bubblesort22.recebeVetor(decrescenteVar) + ",");
                writer.append(bubblesort23.recebeVetor(aleatorioVar) + ",");
                writer.append(bubblesort1.recebeVetor(crescenteVar) + ",");
                writer.append(bubblesort2.recebeVetor(decrescenteVar) + ",");
                writer.append(bubblesort3.recebeVetor(aleatorioVar) + ",");
                writer.append(selection1.recebeVetor(crescenteVar) + ",");
                writer.append(selection2.recebeVetor(decrescenteVar) + ",");
                writer.append(selection3.recebeVetor(aleatorioVar) + ",");
                writer.append('\n');

                // Criando CSV com o array
                // 99 para pegar o array cheio
                if (n == 100) {
                    
                    writer.flush();
                    writer.close();
                    System.out.println("Arquivo CSV criado com Sucesso!");
                }
            }
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}