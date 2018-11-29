/**
 * @file    main.cpp
 * @brief   Código fonte do prgrama com medição de tempo de execução dos algoritmos de busca
 * @author  Bianca Santiago (bianca.santiago72@gmail.com)
 * @author  Jaine Budke (jainebudke@hotmail.com)
 * @since   18/04/2017
 * @date    22/05/2017
 */

#include "manager.h"
#include "ordenacao.h"

#include <time.h>
#include <ctime>

#include <iomanip>

#include <fstream>

/**
*@brief Função principal que contém o tempo de execução dos algoritmos de busca.
*/
int main(){

    std::srand(std::time(0)); // semente do rand

    // declara os diferentes tamanhos de base de busca que serão analisados
    int tamBase[] = { 1000, 5000, 10000, 15000, 50000, 100000, 500000, 600000, 700000, 800000, 900000, 1000000 };

    ///////////////////////////////////////////////////////////////////////////
    // GRAVANDO DADOS EM ARQUIVOS dadosInsertionSortMelhor.txt, dadosInsertionSortPior.txt, dadosInsertionSortMedio.txt
    ///////////////////////////////////////////////////////////////////////////
    // Gravando em dadosInsertionSortMelhor.txt
    std::ofstream arqsaidaInsertionSortMelhor;
    arqsaidaInsertionSortMelhor.open( "dadosInsertionSortMelhor.txt", std::ios::out );
    if( !arqsaidaInsertionSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados InsertionSortMelhor..." << std::endl;

    // Grava o cabeçalho
    arqsaidaInsertionSortMelhor << "#Dados para o script geraGrafico.gnu do InsertionSortMelhor" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaInsertionSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;


    // Gravando em dadosInsertionSortPior.txt
    std::ofstream arqsaidaInsertionSortPior;
    arqsaidaInsertionSortPior.open( "dadosInsertionSortPior.txt", std::ios::out );
    if( !arqsaidaInsertionSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados InsertionSortPior..." << std::endl;

    // Grava o cabeçalho
    arqsaidaInsertionSortPior << "#Dados para o script geraGrafico.gnu do InsertionSortPior" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaInsertionSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    // Gravando em dadosInsertionSortMedio.txt
    std::ofstream arqsaidaInsertionSortMedio;
    arqsaidaInsertionSortMedio.open( "dadosInsertionSortMedio.txt", std::ios::out );
    if( !arqsaidaInsertionSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados InsertionSortMedio..." << std::endl;

    // Grava o cabeçalho
    arqsaidaInsertionSortMedio << "#Dados para o script geraGrafico.gnu do InsertionSortMedio" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaInsertionSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;

    ///////////////////////////////////////////////////////////////////////////
    // GRAVANDO DADOS EM ARQUIVOS dadosSelectionSortMelhor.txt, dadosSelectionSortPior.txt, dadosSelectionSortMedio.txt
    ///////////////////////////////////////////////////////////////////////////
    // Gravando dadosSelectionSortMelhor.txt
    std::ofstream arqsaidaSelectionSortMelhor;
    arqsaidaSelectionSortMelhor.open( "dadosSelectionSortMelhor.txt", std::ios::out );
    if( !arqsaidaSelectionSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados SelectionSortMelhor..." << std::endl;

    // Grava o cabeçalho
    arqsaidaSelectionSortMelhor << "#Dados para o script geraGrafico.gnu do SelectionSortMelhor" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaSelectionSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;

    // Gravando dadosSelectionSortPior.txt
    std::ofstream arqsaidaSelectionSortPior;
    arqsaidaSelectionSortPior.open( "dadosSelectionSortPior.txt", std::ios::out );
    if( !arqsaidaSelectionSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados SelectionSortPior..." << std::endl;

    // Grava o cabeçalho
    arqsaidaSelectionSortPior << "#Dados para o script geraGrafico.gnu do SelectionSortPior" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaSelectionSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    // Gravando dadosSelectionSortMedio.txt
    std::ofstream arqsaidaSelectionSortMedio;
    arqsaidaSelectionSortMedio.open( "dadosSelectionSortMedio.txt", std::ios::out );
    if( !arqsaidaSelectionSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados SelectionSortMedio..." << std::endl;

    // Grava o cabeçalho
    arqsaidaSelectionSortMedio << "#Dados para o script geraGrafico.gnu do SelectionSortMedio" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaSelectionSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;




    ///////////////////////////////////////////////////////////////////////////
    // GRAVANDO DADOS EM ARQUIVOS dadosQuickSortMelhor.txt, dadosQuickSortPior.txt, dadosQuickSortMedio.txt
    ///////////////////////////////////////////////////////////////////////////
    // Gravando dadosQuickSortMelhor.txt
    std::ofstream arqsaidaQuickSortMelhor;
    arqsaidaQuickSortMelhor.open( "dadosQuickSortMelhor.txt", std::ios::out );
    if( !arqsaidaQuickSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados QuickSortMelhor..." << std::endl;

    // Grava o cabeçalho
    arqsaidaQuickSortMelhor << "#Dados para o script geraGrafico.gnu do QuickSortMelhor" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
     * W - Chave de busca
    */
    arqsaidaQuickSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;

    // Gravando dadosQuickSortPior.txt
    std::ofstream arqsaidaQuickSortPior;
    arqsaidaQuickSortPior.open( "dadosQuickSortPior.txt", std::ios::out );
    if( !arqsaidaQuickSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados QuickSortPior..." << std::endl;

    // Grava o cabeçalho
    arqsaidaQuickSortPior << "#Dados para o script geraGrafico.gnu do QuickSortPior" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
     * W - Chave de busca
    */
    arqsaidaQuickSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    // Gravando dadosQuickSortMedio.txt
    std::ofstream arqsaidaQuickSortMedio;
    arqsaidaQuickSortMedio.open( "dadosQuickSortMedio.txt", std::ios::out );
    if( !arqsaidaQuickSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados QuickSortMedio..." << std::endl;

    // Grava o cabeçalho
    arqsaidaQuickSortMedio << "#Dados para o script geraGrafico.gnu do QuickSortMedio" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
     * W - Chave de busca
    */
    arqsaidaQuickSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;


    ///////////////////////////////////////////////////////////////////////////
    // GRAVANDO DADOS EM ARQUIVOS dadosMergeSortMelhor.txt, dadosMergeSortPior.txt, dadosMergeSortMedio.txt
    ///////////////////////////////////////////////////////////////////////////
    // Gravando dadosMergeSortMelhor.txt
    std::ofstream arqsaidaMergeSortMelhor;
    arqsaidaMergeSortMelhor.open( "dadosMergeSortMelhor.txt", std::ios::out );
    if( !arqsaidaMergeSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados MergeSortMelhor..." << std::endl;

    // Grava o cabeçalho
    arqsaidaSelectionSortMelhor << "#Dados para o script geraGrafico.gnu  do MergeSortMelhor" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaMergeSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;

    // Gravando dadosMergeSortPior.txt
    std::ofstream arqsaidaMergeSortPior;
    arqsaidaMergeSortPior.open( "dadosMergeSortPior.txt", std::ios::out );
    if( !arqsaidaMergeSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados MergeSortPior..." << std::endl;

    // Grava o cabeçalho
    arqsaidaMergeSortPior << "#Dados para o script geraGrafico.gnu  do MergeSortPior" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaMergeSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    // Gravando dadosMergeSortMedio.txt
    std::ofstream arqsaidaMergeSortMedio;
    arqsaidaMergeSortMedio.open( "dadosMergeSortMedio.txt", std::ios::out );
    if( !arqsaidaMergeSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados MergeSortMedio..." << std::endl;

    // Grava o cabeçalho
    arqsaidaMergeSortMedio << "#Dados para o script geraGrafico.gnu  do MergeSortMedio" << std::endl;
    /*
     * X - Tamanho da base de busca
     * Y - Tempo de execução
    */
    arqsaidaMergeSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;


    for( int i = 0 ; i <  4; ++i ){
        std::cout << "===========================\n";
        std::cout << "Tamanho de busca = " << tamBase[i] << "\n";
        std::cout << "===========================\n";

        // RESULTADO COM ORDENACAO InsertionSort
        std::cout << "InsertionSort: \n";
        std::function < void( int*, int ) >insertion = insertionSort;
        analiseCasos( arqsaidaInsertionSortMelhor, arqsaidaInsertionSortPior, arqsaidaInsertionSortMedio, tamBase[i], insertion );
        std::cout << "\n";

        // RESULTADO COM ORDENACAO SelectionSort
        std::cout << "SelectionSort: \n";
        std::function < void( int*, int ) >selection = selectionSort;
        analiseCasos( arqsaidaSelectionSortMelhor, arqsaidaSelectionSortPior, arqsaidaSelectionSortMedio, tamBase[i], selection );
        std::cout << "\n";
    }


    for( int i = 0 ; i <  12; ++i ){
        std::cout << "===========================\n";
        std::cout << "Tamanho de busca = " << tamBase[i] << "\n";
        std::cout << "===========================\n";

        // RESULTADO COM ORDENACAO QuickSort
        std::cout << "QuickSort: \n";
        std::function < int( int*, int, int ) >quick = quickSort;
        analiseCasos2( arqsaidaQuickSortMelhor, arqsaidaQuickSortPior, arqsaidaQuickSortMedio, tamBase[i], quick );
        std::cout << "\n";

        // RESULTADO COM ORDENACAO mergeSort
        std::cout << "MergeSort: \n";
        std::function < int( int*, int, int ) >merge = mergesort;
        analiseCasos2( arqsaidaMergeSortMelhor, arqsaidaMergeSortPior, arqsaidaMergeSortMedio, tamBase[i], merge );
        std::cout << "\n";

    }

    // FECHANDO ARQUIVO COM DADOS IS
    std::cout << "Fechando o arquivo dadosInsertionSort.txt..." << std::endl;
    arqsaidaInsertionSortMelhor.close();
    arqsaidaInsertionSortPior.close();
    arqsaidaInsertionSortMedio.close();

    // FECHANDO ARQUIVO COM DADOS SS
    std::cout << "Fechando o arquivo dadosSelectionSort.txt..." << std::endl;
    arqsaidaSelectionSortMelhor.close();
    arqsaidaSelectionSortPior.close();
    arqsaidaSelectionSortMedio.close();

    // FECHANDO ARQUIVO COM DADOS QS
    std::cout << "Fechando o arquivo dadosQuickSort.txt..." << std::endl;
    arqsaidaQuickSortMelhor.close();
    arqsaidaQuickSortPior.close();
    arqsaidaQuickSortMedio.close();

    // FECHANDO ARQUIVO COM DADOS MS
    std::cout << "Fechando o arquivo dadosMergeSort.txt..." << std::endl;
    arqsaidaMergeSortMelhor.close();
    arqsaidaMergeSortPior.close();
    arqsaidaMergeSortMedio.close();

    return 0;

}
