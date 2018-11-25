

#include "manager.h"
#include "ordenacao.h"

#include <time.h>
#include <ctime>

#include <iomanip>

#include <fstream>


int main(){

    std::srand(std::time(0)); 

    
    int tamBase[] = { 1000, 5000, 10000, 15000, 50000, 100000, 500000, 600000, 700000, 800000, 900000, 1000000 };

    
    
    
    
    std::ofstream arqsaidaInsertionSortMelhor;
    arqsaidaInsertionSortMelhor.open( "dadosInsertionSortMelhor.txt", std::ios::out );
    if( !arqsaidaInsertionSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados InsertionSortMelhor..." << std::endl;

    
    arqsaidaInsertionSortMelhor << "#Dados para o script geraGrafico.gnu do InsertionSortMelhor" << std::endl;
    
    arqsaidaInsertionSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;


    
    std::ofstream arqsaidaInsertionSortPior;
    arqsaidaInsertionSortPior.open( "dadosInsertionSortPior.txt", std::ios::out );
    if( !arqsaidaInsertionSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados InsertionSortPior..." << std::endl;

    
    arqsaidaInsertionSortPior << "#Dados para o script geraGrafico.gnu do InsertionSortPior" << std::endl;
    
    arqsaidaInsertionSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    
    std::ofstream arqsaidaInsertionSortMedio;
    arqsaidaInsertionSortMedio.open( "dadosInsertionSortMedio.txt", std::ios::out );
    if( !arqsaidaInsertionSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados InsertionSortMedio..." << std::endl;

    
    arqsaidaInsertionSortMedio << "#Dados para o script geraGrafico.gnu do InsertionSortMedio" << std::endl;
    
    arqsaidaInsertionSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;

    
    
    
    
    std::ofstream arqsaidaSelectionSortMelhor;
    arqsaidaSelectionSortMelhor.open( "dadosSelectionSortMelhor.txt", std::ios::out );
    if( !arqsaidaSelectionSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados SelectionSortMelhor..." << std::endl;

    
    arqsaidaSelectionSortMelhor << "#Dados para o script geraGrafico.gnu do SelectionSortMelhor" << std::endl;
    
    arqsaidaSelectionSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;

    
    std::ofstream arqsaidaSelectionSortPior;
    arqsaidaSelectionSortPior.open( "dadosSelectionSortPior.txt", std::ios::out );
    if( !arqsaidaSelectionSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados SelectionSortPior..." << std::endl;

    
    arqsaidaSelectionSortPior << "#Dados para o script geraGrafico.gnu do SelectionSortPior" << std::endl;
    
    arqsaidaSelectionSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    
    std::ofstream arqsaidaSelectionSortMedio;
    arqsaidaSelectionSortMedio.open( "dadosSelectionSortMedio.txt", std::ios::out );
    if( !arqsaidaSelectionSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados SelectionSortMedio..." << std::endl;

    
    arqsaidaSelectionSortMedio << "#Dados para o script geraGrafico.gnu do SelectionSortMedio" << std::endl;
    
    arqsaidaSelectionSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;




    
    
    
    
    std::ofstream arqsaidaQuickSortMelhor;
    arqsaidaQuickSortMelhor.open( "dadosQuickSortMelhor.txt", std::ios::out );
    if( !arqsaidaQuickSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados QuickSortMelhor..." << std::endl;

    
    arqsaidaQuickSortMelhor << "#Dados para o script geraGrafico.gnu do QuickSortMelhor" << std::endl;
    
    arqsaidaQuickSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;

    
    std::ofstream arqsaidaQuickSortPior;
    arqsaidaQuickSortPior.open( "dadosQuickSortPior.txt", std::ios::out );
    if( !arqsaidaQuickSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados QuickSortPior..." << std::endl;

    
    arqsaidaQuickSortPior << "#Dados para o script geraGrafico.gnu do QuickSortPior" << std::endl;
    
    arqsaidaQuickSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    
    std::ofstream arqsaidaQuickSortMedio;
    arqsaidaQuickSortMedio.open( "dadosQuickSortMedio.txt", std::ios::out );
    if( !arqsaidaQuickSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados QuickSortMedio..." << std::endl;

    
    arqsaidaQuickSortMedio << "#Dados para o script geraGrafico.gnu do QuickSortMedio" << std::endl;
    
    arqsaidaQuickSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;


    
    
    
    
    std::ofstream arqsaidaMergeSortMelhor;
    arqsaidaMergeSortMelhor.open( "dadosMergeSortMelhor.txt", std::ios::out );
    if( !arqsaidaMergeSortMelhor.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados MergeSortMelhor..." << std::endl;

    
    arqsaidaSelectionSortMelhor << "#Dados para o script geraGrafico.gnu  do MergeSortMelhor" << std::endl;
    
    arqsaidaMergeSortMelhor << "#X" << std::setw(10) << "#Y" << std::endl;

    
    std::ofstream arqsaidaMergeSortPior;
    arqsaidaMergeSortPior.open( "dadosMergeSortPior.txt", std::ios::out );
    if( !arqsaidaMergeSortPior.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados MergeSortPior..." << std::endl;

    
    arqsaidaMergeSortPior << "#Dados para o script geraGrafico.gnu  do MergeSortPior" << std::endl;
    
    arqsaidaMergeSortPior << "#X" << std::setw(10) << "#Y" << std::endl;

    
    std::ofstream arqsaidaMergeSortMedio;
    arqsaidaMergeSortMedio.open( "dadosMergeSortMedio.txt", std::ios::out );
    if( !arqsaidaMergeSortMedio.is_open() ){
        return 0;
    }

    std::cout << "Gerando dados MergeSortMedio..." << std::endl;

    
    arqsaidaMergeSortMedio << "#Dados para o script geraGrafico.gnu  do MergeSortMedio" << std::endl;
    
    arqsaidaMergeSortMedio << "#X" << std::setw(10) << "#Y" << std::endl;


    for( int i = 0 ; i <  4; ++i ){
        std::cout << "===========================\n";
        std::cout << "Tamanho de busca = " << tamBase[i] << "\n";
        std::cout << "===========================\n";

        
        std::cout << "InsertionSort: \n";
        std::function < void( int*, int ) >insertion = insertionSort;
        analiseCasos( arqsaidaInsertionSortMelhor, arqsaidaInsertionSortPior, arqsaidaInsertionSortMedio, tamBase[i], insertion );
        std::cout << "\n";

        
        std::cout << "SelectionSort: \n";
        std::function < void( int*, int ) >selection = selectionSort;
        analiseCasos( arqsaidaSelectionSortMelhor, arqsaidaSelectionSortPior, arqsaidaSelectionSortMedio, tamBase[i], selection );
        std::cout << "\n";
    }


    for( int i = 0 ; i <  12; ++i ){
        std::cout << "===========================\n";
        std::cout << "Tamanho de busca = " << tamBase[i] << "\n";
        std::cout << "===========================\n";

        
        std::cout << "QuickSort: \n";
        std::function < int( int*, int, int ) >quick = quickSort;
        analiseCasos2( arqsaidaQuickSortMelhor, arqsaidaQuickSortPior, arqsaidaQuickSortMedio, tamBase[i], quick );
        std::cout << "\n";

        
        std::cout << "MergeSort: \n";
        std::function < int( int*, int, int ) >merge = mergesort;
        analiseCasos2( arqsaidaMergeSortMelhor, arqsaidaMergeSortPior, arqsaidaMergeSortMedio, tamBase[i], merge );
        std::cout << "\n";

    }

    
    std::cout << "Fechando o arquivo dadosInsertionSort.txt..." << std::endl;
    arqsaidaInsertionSortMelhor.close();
    arqsaidaInsertionSortPior.close();
    arqsaidaInsertionSortMedio.close();

    
    std::cout << "Fechando o arquivo dadosSelectionSort.txt..." << std::endl;
    arqsaidaSelectionSortMelhor.close();
    arqsaidaSelectionSortPior.close();
    arqsaidaSelectionSortMedio.close();

    
    std::cout << "Fechando o arquivo dadosQuickSort.txt..." << std::endl;
    arqsaidaQuickSortMelhor.close();
    arqsaidaQuickSortPior.close();
    arqsaidaQuickSortMedio.close();

    
    std::cout << "Fechando o arquivo dadosMergeSort.txt..." << std::endl;
    arqsaidaMergeSortMelhor.close();
    arqsaidaMergeSortPior.close();
    arqsaidaMergeSortMedio.close();

    return 0;

}
