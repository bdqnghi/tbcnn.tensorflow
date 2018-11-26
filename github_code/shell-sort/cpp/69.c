#include <iostream>
#include <cstdlib>
#include <time.h>
#include "F_Ordenação.h"
#include <cstdlib>
#include <algorithm>
#include <stdio.h>

using namespace std;
using namespace ED;

template <typename T>
void preenche(T *vet,int n,int seed)
{

    Aleatorios<T> gerador(seed);
    for(int i=0; i<n; i++)
    {
        vet[i] = gerador.nextr();
    }

}
void imprime_medias(int n ,int line, int *vmedias, int tam, int met,FILE *file)
{

    int  j; //NUMERO DE METODOS

    fprintf(file,"%d;", n);
    cout<<endl;
    cout<<"tamanho "<< line<<"    ";

    for (j=0; j<met; j++){

        fprintf(file,"%d;", *vmedias);
        cout<<" "<<*vmedias++;

    }
    fprintf(file,"\n");
    cout<<endl;


}

template<typename T>
int Media_Heap_Sort(T*vet, int n)
{

    int seed;
    int media_metodo=0, soma=0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {
        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::Heap_Sort(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;

    }


    media_metodo = soma/6;
    return(media_metodo);

}

template<typename T>
int Media_Quick_Sort(T *vet,int n)
{

    int seed;
    int media_metodo=0, soma=0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {
        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::quick_Sort(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;
    }


    media_metodo = soma/6;
    return(media_metodo);

}

template<typename T>
int Media_Merge_Sort(T *vet,int n)
{

    int seed;
    int media_metodo=0, soma = 0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {
        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::Merge_Sort(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;
    }


    media_metodo = soma/6;
    return(media_metodo);

}

template<typename T>
int Media_Shell_Sort_Shell(T *vet, int n)
{

    int seed;
    int media_metodo=0, soma = 0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {

        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::Shell_Sort_shell(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;

    }


    media_metodo = soma/6;
    return(media_metodo);

}

template <typename T>
int Media_Shell_Sort_Knuth(T *vet,int n)
{

    int seed;
    int media_metodo=0, soma=0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {

        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::Shell_Sort_knuth(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;
    }


    media_metodo = soma/6;
    return(media_metodo);

}

template <typename T>
int Media_Shell_Sort_Pardons(T *vet, int n)
{

    int seed;
    int media_metodo=0, soma = 0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {
        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::Shell_Sort_pardons(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;

    }


    media_metodo = soma/6;
    return(media_metodo);

}

template<typename T>
int Media_Quick_Sort_C(T *vet, int n)
{

    int seed;
    int media_metodo=0, soma=0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {
        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::Quick_Sort_C(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;

    }


    media_metodo = soma/6;
    return(media_metodo);

}

template<typename T>
int Media_Sort_Cpp(T *vet, int n)
{

    int seed;
    int media_metodo=0, soma=0;
    int start;
    int tmili;

    for(seed=0; seed<6; seed++)
    {
        preenche(vet, n, seed);

        start = clock();
        Ordenacao<T>::Sort_Cpp(vet,n);
        tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);
        soma += tmili;
    }


    media_metodo = soma/6;
    return(media_metodo);

}


int main(int argc, char *argv[])
{
    int n_min, n_max;
    n_min = 10000;   //TAMANHO MÍNIMO DOS VETORES QUE SERÃO ORDENADOS
    n_max = 65610000; //TAMANHO MÁXIMO DOS VETORES QUE SERÃO ORDENADOS

    unsigned long int *vet = new unsigned long int[n_max];// VETOR DE INTEIROS POSITIVOS


    int tam = 9;   //QUANTOS VETORES DE TAMANHOS DISTINTOS TEREMOS QUE TESTAR
    int met = 8;   //NUMERO DE METODOS QUE VAMOS TESTAR

    int medias[met]; // VETORES DE MÉDIAS DE TEMPO PARA MÉTODOS TESTADOS
    int *vmedias = &medias[0];

    FILE *file;
    file=fopen("resultados(2).csv","w");
    fprintf(file,"Tamanho; HeapSort;  QuickSort-Pivo central; MergeSort; ShellSort-Shell; ShellSort-Knuth; ShellSort-Pardons; QuickSort-C++; QuickSort-C;\n");

    int i, n;
    n = n_min;

    //LAÇO PARA EXECUTAR OS 'i' TAMANHOS DE VETORES
    for(i=0; i<tam; i++){

        medias[0] = Media_Heap_Sort(vet, n);
        medias[1] = Media_Quick_Sort(vet, n);
        medias[2] = Media_Merge_Sort(vet, n);
        medias[3] = Media_Shell_Sort_Shell(vet, n);
        medias[4] = Media_Shell_Sort_Knuth(vet, n);
        medias[5] = Media_Shell_Sort_Pardons(vet, n);
        medias[6] = Media_Sort_Cpp(vet, n);
        medias[7] = Media_Quick_Sort_C(vet, n);


        imprime_medias(n,i, vmedias, tam, met, file);
        n *= 3;

    }
    delete vet; // DESALOCA VETOR

    fclose(file);
    system("PAUSE");
    system("cls");
    return EXIT_SUCCESS;

}
