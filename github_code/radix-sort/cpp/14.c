#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

void radixsort(int *v, int n){
    int i,m=0,exp=1;
	int *b = new int[n];
		for(i=0;i<n;i++)
		{
			if(v[i]>m)
				m=v[i];
		}

		while(m/exp>0)
		{
			int bucket[10]={0};
			for(i=0;i<n;i++)
				bucket[v[i]/exp%10]++;
			for(i=1;i<10;i++)
				bucket[i]+=bucket[i-1];
			for(i=n-1;i>=0;i--)
				b[--bucket[v[i]/exp%10]]=v[i];
			for(i=0;i<n;i++)
				v[i]=b[i];
			exp*=10;

       }
       delete [] b;
}

void radixsortinv(int *v, int n){
      int i,m=0,exp=1;
      int *b = new int[n];

		for(i=0;i<n;i++)
		{
			if(v[i]>m)
				m=v[i];
		}

		while(m/exp>0)
		{
			int bucket[10]={0};
			for(i=0;i<n;i++)
				bucket[v[i]/exp%10]++;
			for(i=1;i<10;i++)
				bucket[i]+=bucket[i-1];
			for(i=n-1;i>=0;i--)
				b[--bucket[v[i]/exp%10]]=v[i];
			for(i=0;i<n;i++)
				v[i]=b[i];
			exp*=10;

       }
       delete [] b;
}


int main(){
    cout << "Algoritmo Radix Sort (Somente Crescente)\n\n";
    FILE *leitura;

    int num = 0;
    int a;
    unsigned randnum;

    leitura = fopen( "100.txt", "r" );

    if( leitura == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    while( !feof(leitura) ){
        fscanf( leitura, "%i\n", &a);
        num++;
    }

    int *vetor = new int[num];
    int i = 0;

    fclose(leitura);
    leitura = fopen( "100.txt", "r" );

    while( !feof(leitura) ){
        fscanf( leitura, "%i\n", &a);
        vetor[i] = a;
        i++;
    }

	int start = clock();
	radixsort(vetor, num);
	int stop = clock();

	cout << "Numeros = 100; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura);
	leitura = fopen( "100.txt", "r" );
	i=0;

    while( !feof(leitura) ){
        fscanf( leitura, "%i\n", &a);
        vetor[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor, num);
	stop = clock();

//	cout << "Numeros = 100; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";

/*

    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor[i] << "\n";
    }
*/

    fclose(leitura);
    delete [] vetor;


    FILE *leitura2;
    leitura2 = fopen( "500.txt", "r" );
    num = 0;

    if( leitura2 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    while( !feof(leitura2) ){
        fscanf( leitura2, "%i\n", &a);
        num++;
    }

    int *vetor2 = new int[num];
    i = 0;

    fclose(leitura2);
    leitura2 = fopen( "500.txt", "r" );

    while( !feof(leitura2) ){
        fscanf( leitura2, "%i\n", &a);
        vetor2[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor2, num);
	stop = clock();

	cout << "Numeros = 500; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura2);
	leitura2 = fopen( "500.txt", "r" );
	i=0;

	while( !feof(leitura2) ){
        fscanf( leitura2, "%i\n", &a);
        vetor2[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor2, num);
	stop = clock();

//	cout << "Numeros = 500; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";

 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor2[i] << "\n";
    }
*/

    fclose(leitura2);
    delete [] vetor2;



    FILE *leitura3;
    leitura3 = fopen( "1000.txt", "r" );
    num = 0;

    if( leitura3 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    while( !feof(leitura3) ){
        fscanf( leitura3, "%i\n", &a);
        num++;
    }

    int *vetor3 = new int[num];
    i = 0;

    fclose(leitura3);
    leitura3 = fopen( "1000.txt", "r" );

    while( !feof(leitura3) ){
        fscanf( leitura3, "%i\n", &a);
        vetor3[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor3, num);
	stop = clock();

	cout << "Numeros = 1000; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura3);
	leitura3 = fopen( "1000.txt", "r" );
	i=0;

    while( !feof(leitura3) ){
        fscanf( leitura3, "%i\n", &a);
        vetor3[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor3, num);
	stop = clock();

//	cout << "Numeros = 1000; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";


 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor3[i] << "\n";
    }
*/

    fclose(leitura3);
    delete [] vetor3;


    FILE *leitura4;
    leitura4 = fopen( "5000.txt", "r" );
    num = 0;

    if( leitura4 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    num = 5000;
    int *vetor4 = new int[num];
    i = 0;

    fclose(leitura4);
    leitura4 = fopen( "5000.txt", "r" );

    while( !feof(leitura4) ){
        fscanf( leitura4, "%i\n", &a);
        vetor4[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor4, num);
	stop = clock();

	cout << "Numeros = 5000; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura4);
	leitura4 = fopen( "5000.txt", "r" );
	i=0;

    while( !feof(leitura4) ){
        fscanf( leitura4, "%i\n", &a);
        vetor4[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor4, num);
	stop = clock();

//	cout << "Numeros = 5000; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";


 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor4[i] << "\n";
    }
*/

    fclose(leitura4);
    delete [] vetor4;





    FILE *leitura5;
    leitura5 = fopen( "10000.txt", "r" );
    num = 0;

    if( leitura5 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    num = 10000;
    int *vetor5 = new int[num];
    i = 0;

    fclose(leitura5);
    leitura5 = fopen( "10000.txt", "r" );

    while( !feof(leitura5) ){
        fscanf( leitura5, "%i\n", &a);
        vetor5[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor5, num);
	stop = clock();

	cout << "Numeros = 10000; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

    fclose(leitura5);
    leitura5 = fopen( "10000.txt", "r" );
    i=0;

    while( !feof(leitura5) ){
        fscanf( leitura5, "%i\n", &a);
        vetor5[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor5, num);
	stop = clock();

//	cout << "Numeros = 10000; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";


 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor5[i] << "\n";
    }
*/

    fclose(leitura5);
    delete [] vetor5;



    FILE *leitura6;
    leitura6 = fopen( "50000.txt", "r" );
    num = 0;

    if( leitura6 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    num = 50000;
    int *vetor6 = new int[num];
    i = 0;

    fclose(leitura6);
    leitura6 = fopen( "50000.txt", "r" );

    while( !feof(leitura6) ){
        fscanf( leitura6, "%i\n", &a);
        vetor6[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor6, num);
	stop = clock();

	cout << "Numeros = 50000; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura6);
	leitura6 = fopen( "50000.txt", "r" );
	i=0;

    while( !feof(leitura6) ){
        fscanf( leitura6, "%i\n", &a);
        vetor6[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor6, num);
	stop = clock();

//	cout << "Numeros = 50000; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";


 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor6[i] << "\n";
    }
*/

    fclose(leitura6);
    delete [] vetor6;




    FILE *leitura7;
    leitura7 = fopen( "100000.txt", "r" );
    num = 0;

    if( leitura7 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    num = 100000;
    int *vetor7 = new int[num];
    i = 0;

    fclose(leitura7);
    leitura7 = fopen( "100000.txt", "r" );

    while( !feof(leitura7) ){
        fscanf( leitura7, "%i\n", &a);
        vetor7[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor7, num);
	stop = clock();

	cout << "Numeros = 100000; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura7);
	leitura7 = fopen( "100000.txt", "r" );
	i=0;

    while( !feof(leitura7) ){
        fscanf( leitura7, "%i\n", &a);
        vetor7[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor7, num);
	stop = clock();

//	cout << "Numeros = 100000; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";


 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor7[i] << "\n";
    }
*/

    fclose(leitura7);
    delete [] vetor7;





    FILE *leitura8;
    leitura8 = fopen( "500000.txt", "r" );
    num = 0;

    if( leitura8 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    num = 500000;
    int *vetor8 = new int[num];
    i = 0;

    fclose(leitura8);
    leitura8 = fopen( "500000.txt", "r" );

    while( !feof(leitura8) ){
        fscanf( leitura8, "%i\n", &a);
        vetor8[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor8, num);
	stop = clock();

	cout << "Numeros = 500000; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura8);
	leitura8 = fopen( "500000.txt", "r" );
	i=0;

    while( !feof(leitura8) ){
        fscanf( leitura8, "%i\n", &a);
        vetor8[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor8, num);
	stop = clock();

//	cout << "Numeros = 500000; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";


 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor8[i] << "\n";
    }
*/

    fclose(leitura8);
    delete [] vetor8;




    FILE *leitura9;
    leitura9 = fopen( "1000000.txt", "r" );
    num = 0;

    if( leitura9 == NULL){
        cout << "\nErro na abertura de arquivo.\n";
        exit(1);
        }

    num = 1000000;
    int *vetor9 = new int[num];
    i = 0;

    fclose(leitura9);
    leitura9 = fopen( "1000000.txt", "r" );

    while( !feof(leitura9) ){
        fscanf( leitura9, "%i\n", &a);
        vetor9[i] = a;
        i++;
    }

	start = clock();
	radixsort(vetor9, num);
	stop = clock();

	cout << "Numeros = 1000000; Ordenacao = Crescente; Tempo = " << stop - start << " milissegundos.\n\n";

	fclose(leitura9);
	leitura9 = fopen( "1000000.txt", "r" );
	i=0;

    while( !feof(leitura9) ){
        fscanf( leitura9, "%i\n", &a);
        vetor9[i] = a;
        i++;
    }

	start = clock();
	radixsortinv(vetor9, num);
	stop = clock();

//	cout << "Numeros = 1000000; Ordenacao = Descrescente; Tempo = " << stop - start << " milissegundos.\n\n";


 /*
    for(i=0; i<num; i++){
        cout << "vetor[" << i << "] = " << vetor9[i] << "\n";
    }
*/

    fclose(leitura9);
    delete [] vetor9;


return 0;
}

