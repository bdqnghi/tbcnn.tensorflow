








#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void isort(int *v, int lenv);


extern "C"  int intcmp(const void*, const void*);  

int main()
{
   unsigned int  i, size;
   int  *zahlen1, *zahlen2;
   time_t zeit1, zeit2;

   cout << "\n     Die Performance der Sortieralgorithmen"
        << "\n        Quick-Sort  und  Selection-Sort"
        << "\n     werden verglichen.\n\n"
        << "\nWieviele Zahlen sollen sortiert werden?   ";

   cin >> size;

   zahlen1 = new int[size];
   zahlen2 = new int[size];

   
   cout << "\nEs werden " << size << " Zufallszahlen erzeugt.\n";

   srand((unsigned)time(NULL));       
                                      
   for(i = 0 ; i < size ; ++i)
      zahlen1[i] = zahlen2[i] = rand();   

   cout << "\nDas Sortieren beginnt! Bitte warten.\n";

   time(&zeit1);                      
                                      
   qsort(zahlen1, size, sizeof(int), intcmp);  
   time(&zeit2);

   cout  << "\nDie Zeit fuer den Quick-Sort: "
         <<   zeit2 - zeit1 << " Sekunden.\n"
         << "\nIch sortiere wieder. Bitte warten!\n";

   time(&zeit1);                      
   isort(zahlen2, size);              
   time(&zeit2);

   cout << "\nDie Zeit fuer den Insertion-Sort: "
        << zeit2 - zeit1 << " Sekunden.\n"
        << "\nSortierte Zahlen ausgeben? (j/n)\n\n";                                           

   char c;  cin >> c;
   if( c == 'J' || c == 'j')
     for( i = 0 ; i < size ; ++i)
       cout << setw(10) <<  zahlen1[i];

   cout << endl;
   return 0;
}


extern "C"  int intcmp( const void *a, const void *b)
{
   return (*(int*)a - *(int*)b);
}





void isort( int *a, int len)   
{                              
   register int *b, *minp;
   int *last, help;

   last = a + len - 1;         

   for( ; a <= last; ++a)      
   {                           
      minp = a;                
                               
      for( b = a+1; b <= last; ++b)     
         if( *b < *minp )               
             minp = b;

      help = *a, *a = *minp, *minp = help;       
   }
}
