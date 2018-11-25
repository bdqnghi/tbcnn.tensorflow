

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <time.h>
#include "bubblesort.h"
#include "quicksort.h"
#include "mergesort.h"
#include <cmath>


const int BUBBLE_SORT = 1;
const int QUICK_SORT = 2;
const int MERGE_SORT = 3;


const int TIME_FUNCTION = 1;
const int CLOCK_FUNCTION = 2;


const int RAND_RANGE_MAX = 100000;


const int SIZE_VETOR_INIT = 5000;
const int SIZE_VETOR_MAX = 100000;
const int INCREASE_SIZE_VETOR = 5000;

#define TIME_BUBBLE_PATH "dados-coletados/time_bubble.dat"
#define TIME_QUICK_PATH "dados-coletados/time_quick.dat"
#define TIME_MERGE_PATH "dados-coletados/time_merge.dat"
#define CLOCK_BUBBLE_PATH "dados-coletados/clock_bubble.dat"
#define CLOCK_QUICK_PATH "dados-coletados/clock_quick.dat"
#define CLOCK_MERGE_PATH "dados-coletados/clock_merge.dat"

using namespace std;


int *vetorQuickSort;
int *vetorBubbleSort;
int *vetorMergeSort;
int tamanho;


void criarVetor(int tamanhoVetor, int semente) {
    srand(semente);

    
    vetorQuickSort = new int[tamanhoVetor];
    vetorBubbleSort = new int[tamanhoVetor];
    vetorMergeSort = new int[tamanhoVetor];

    
    for (int i = 0; i < tamanhoVetor; i++) {
        vetorQuickSort[i] =  rand() % RAND_RANGE_MAX;
        vetorBubbleSort[i] = rand() % RAND_RANGE_MAX;
        vetorMergeSort[i] = rand() % RAND_RANGE_MAX;
    }
}


void imprimeVetor(string nomeVetor, int *vetor, int n) {
    cout << nomeVetor << ":  ";
    for(int i = 0; i < n; i++){
        cout << vetor[i] << " ";
    }
    cout << endl;
}




void clearFiles() {

    const string files[] = {TIME_BUBBLE_PATH, TIME_QUICK_PATH, TIME_MERGE_PATH,
                    CLOCK_BUBBLE_PATH, CLOCK_QUICK_PATH, CLOCK_MERGE_PATH};

    for (int i = 0; i < 6; i++){
        ofstream init;
        
        init.open(files[i], ios_base::in);
        
        if (init) {
            
            init.close();
            if( files[i] == TIME_BUBBLE_PATH){
                remove(TIME_BUBBLE_PATH);
            }else if( files[i] == TIME_QUICK_PATH){
                remove(TIME_QUICK_PATH);
            }else if( files[i] == TIME_MERGE_PATH){
                remove(TIME_MERGE_PATH);
            }else if( files[i] == CLOCK_BUBBLE_PATH){
                remove(CLOCK_BUBBLE_PATH);
            }else if( files[i] == CLOCK_QUICK_PATH){
                remove(CLOCK_QUICK_PATH);
            }else if( files[i] == CLOCK_MERGE_PATH){
                remove(CLOCK_MERGE_PATH);
            }

        }
    }
}




void saveInFile(string content, string path){
    ofstream out;
    out.open(path, ios::app); 
    out << content << endl;
    out.close();
}

void saveInFile(int sizeVetor, double media ,double dp_inf, double dp_sup, string path){
    ofstream out;
    out.open(path, ios::app);
    out << sizeVetor << " " << media << " " << dp_inf << " " << dp_sup << endl;
    out.close();
}



double ordenaVetorTime(int algorithm, int size){
    time_t time_init;

    
    QuickSort qs = QuickSort();
    BubbleSort bs = BubbleSort();
    MergeSort ms = MergeSort();

    
    switch (algorithm) {
        case QUICK_SORT:
            time(&time_init);
            qs.start(vetorQuickSort, size);
            return time(NULL) - time_init;
        case BUBBLE_SORT:
            time_init = time(NULL);
            bs.start(vetorBubbleSort, size);
            return time(NULL) - time_init;
        case MERGE_SORT:
            time_init = time(NULL);
            ms.start(vetorMergeSort, size);
            return time(NULL) - time_init;
        default:
            cout << "ERROR" << endl;
        break;
    }
    return -1;
}


double ordenaVetorClock(int algorithm, int size) {
    clock_t clock_init;

    
    QuickSort qs = QuickSort();
    BubbleSort bs = BubbleSort();
    MergeSort ms = MergeSort();

    
    switch (algorithm) {
        case QUICK_SORT:
            clock_init = clock();
            qs.start(vetorQuickSort, size);
            return clock() - clock_init;
        case BUBBLE_SORT:
            clock_init = clock();
            bs.start(vetorBubbleSort, size);
            return clock() - clock_init;
        case MERGE_SORT:
            clock_init = clock();
            ms.start(vetorMergeSort, size);
            return clock() - clock_init;
    }
    return -1;
}


double mediaVetor(double *vetor, int size){
    
    double media = 0.0;
    
    if (size <= 0) {
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        media += vetor[i];
    }
    return media/(size*1.0);
}

double desvioPadrao(double *vetor, int sizeVetor, double media){
    double soma = 0;
    double variancia = 0;
    for(int i = 0; i < sizeVetor; i++){
        soma += abs((vetor[i] - media) * (vetor[i] - media));
    }
    variancia = soma / (1.0*sizeVetor);
    return sqrt(variancia);
}


void performanceAnalysis(int sizeVetor, int function){

    
    double pontoBubble [10];
    double pontoQuick  [10];
    double pontoMerge  [10];

    
    for(int i = 0; i < 10; i++){
        
        criarVetor(sizeVetor, i);

        
        double durationBubble;
        double durationQuick;
        double durationMerge;

        
        if (function == TIME_FUNCTION) {
            
            durationBubble = ordenaVetorTime(BUBBLE_SORT, sizeVetor);
            durationQuick = ordenaVetorTime(QUICK_SORT, sizeVetor);
            durationMerge = ordenaVetorTime(MERGE_SORT, sizeVetor);

        
        } else if (function == CLOCK_FUNCTION) {
            
            durationBubble = ordenaVetorClock(BUBBLE_SORT, sizeVetor);
            durationQuick = ordenaVetorClock(QUICK_SORT, sizeVetor);
            durationMerge = ordenaVetorClock(MERGE_SORT, sizeVetor);
        }else{
            cout << "ERROR" << endl;
        }

        
        pontoBubble[i] = durationBubble;
        pontoQuick [i] = durationQuick;
        pontoMerge [i] = durationMerge;
    }

    
    double pointBubbleSort = mediaVetor(pontoBubble, 10);
    double pointQuickSort = mediaVetor(pontoQuick, 10);
    double pointMergeSort = mediaVetor(pontoMerge, 10);

    double dpBS = desvioPadrao(pontoBubble, 10, pointBubbleSort);
    double dpQS = desvioPadrao(pontoQuick, 10, pointQuickSort);
    double dpMS = desvioPadrao(pontoMerge, 10, pointMergeSort);

    
    
        
        
    
        
       
        
        
        
    


    if (function == TIME_FUNCTION) {
        
        saveInFile(sizeVetor,  pointBubbleSort, pointBubbleSort - dpBS, pointBubbleSort + dpBS, TIME_BUBBLE_PATH);
        saveInFile(sizeVetor,  pointQuickSort, pointQuickSort - dpQS,  pointQuickSort + dpQS, TIME_QUICK_PATH);
        saveInFile(sizeVetor,  pointMergeSort, pointMergeSort - dpMS, pointMergeSort + dpMS, TIME_MERGE_PATH);
    } else if (function == CLOCK_FUNCTION) {
        
        double b = ((float)pointBubbleSort)/CLOCKS_PER_SEC;
        double q = ((float)pointQuickSort)/CLOCKS_PER_SEC;
        double m = ((float)pointMergeSort)/CLOCKS_PER_SEC;
        double dpb = ((float)dpBS)/CLOCKS_PER_SEC;
        double dpq = ((float)dpQS)/CLOCKS_PER_SEC;
        double dpm = ((float)dpMS)/CLOCKS_PER_SEC;
        saveInFile(sizeVetor, b, b - dpb, b+dpb, CLOCK_BUBBLE_PATH);
        saveInFile(sizeVetor, q, q - dpq, q+dpq, CLOCK_QUICK_PATH);
        saveInFile(sizeVetor, m, m - dpm, m+dpm, CLOCK_MERGE_PATH);
    }
}


int main(int argc, char *argv[]) {
	system("mkdir dados-coletados");
    
    clearFiles();
    clock_t clock_init; 

    
    for (int i = SIZE_VETOR_INIT; i <= SIZE_VETOR_MAX; i += INCREASE_SIZE_VETOR) {
        
        clock_init = clock();

        
        performanceAnalysis(i,  TIME_FUNCTION);
        performanceAnalysis(i,  CLOCK_FUNCTION);

        
        cout << i <<"  -  " << clock() - clock_init << endl;
    }

    string script_gnuplot_dp = "set encoding iso_8859_1 \n"
                            "set grid \n"
                            "set key top left \n"
                            "set title 'Análise de desempenho com a função Clock' \n"
                            "set xlabel 'Tamanho do vetor' \n"
                            "set ylabel 'Tempo (segundos)' \n"
                            "# BubbleSort \n"
                            "plot 'clock_bubble.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                            "rep 'clock_bubble.dat' using 1:2:3:4 t 'BubbleSort' with yerrorbars ls 1 lt 8 \n"
                            "# QuickSort \n"
                            "rep 'clock_quick.dat' using 1:2 notitle with linespoints ls 2 lt 6 \n"
                            "rep 'clock_quick.dat' using 1:2:3:4 t 'QuickSort' with yerrorbars ls 2 lt 6 \n"
                            "# Mergesort \n"
                            "rep 'clock_merge.dat' using 1:2 notitle with linespoints ls 3 lt 5 \n"
                            "rep 'clock_merge.dat' using 1:2:3:4 t 'Mergesort' with yerrorbars ls 3 lt 5 \n"
                            "set terminal png \n"
                            "set output 'grafico_clock.png' \n"
                            "replot \n"
                            "\n"
                            "\n"
                            "set encoding iso_8859_1 \n"
                            "set grid \n"
                            "set key top left \n"
                            "set title 'Análise de desempenho com a função Time'\n"
                            "set xlabel 'Tamanho do vetor' \n"
                            "set ylabel 'Tempo (segundos)' \n"
                            "# BubbleSort \n"
                            "plot 'time_bubble.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                            "rep 'time_bubble.dat' using 1:2:3:4 t 'BubbleSort' with yerrorbars ls 1 lt 8 \n"
                            "# QuickSort \n"
                            "rep 'time_quick.dat' using 1:2 notitle with linespoints ls 2 lt 6 \n"
                            "rep 'time_quick.dat' using 1:2:3:4 t 'QuickSort' with yerrorbars ls 2 lt 6 \n"
                            "# Mergesort \n"
                            "rep 'time_merge.dat' using 1:2 notitle with linespoints ls 3 lt 5 \n"
                            "rep 'time_merge.dat' using 1:2:3:4 t 'Mergesort' with yerrorbars ls 3 lt 5 \n"
                            "set terminal png \n"
                            "set output 'grafico_time.png' \n"
                            "replot \n" ;

    string script_gnuplot_simple = "set title 'Desempenho de Algoritmos de Ordenação usando Clock'; \n"
                            "set key box right bottom outside title 'Algoritmos de Ordenação'; \n"
                            "set xlabel 'Tamanho do Vetor'; set ylabel 'Tempo Decorrido (Segundos)'; \n"
                            "plot 'clock_bubble.dat' using 1:2 title 'BubbleSort' with lines, 'clock_quick.dat' using 1:2 title 'QuickSort' with lines, 'clock_merge.dat' using 1:2 title 'MergeSort' with lines; \n"
                            "set terminal png size 1000,680; \n"
                            "set output 'clock.png'; \n"
                            "replot  \n"
                            "\n"
                            "set title 'Desempenho de Algoritmos de Ordenação usando Time'; \n"
                            "set key box right bottom outside title 'Algoritmos de Ordenação'; \n"
                            "set xlabel 'Tamanho do Vetor'; set ylabel 'Tempo Decorrido (Segundos)'; \n"
                            "plot 'time_bubble.dat' using 1:2 title 'BubbleSort' with lines, 'time_quick.dat' using 1:2 title 'QuickSort' with lines, 'time_merge.dat' using 1:2 title 'MergeSort' with lines; \n"
                            "set terminal png size 1000,680; \n"
                            "set output 'time.png'; \n"
                            "replot \n";

    saveInFile(script_gnuplot_dp, "dados-coletados/script_gnuplot.gnu");

    system("cd dados-coletados && gnuplot script_gnuplot.gnu");

    return 0;
}
