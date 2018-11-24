#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <cstdint>

using namespace std;

const int MAXN = 100;

char p[MAXN], s[MAXN/2]; int T[MAXN+1];
int np = strlen(p), ns = strlen(s);

void makeTable()
{
   T[0] = -1;
   int cnd = 0;
   for (int i = 1; i <= np; i++)
   {
      T[i] = cnd;
      while (cnd >= 0 && p[cnd] != p[i])
         cnd = T[cnd];
      cnd++;
   }
}

void KnuthMorrisPratt()
{
   int cnd = 0;                          // position courante dans le motif p
   for (int i = 0; i <= ns; i++)         // tant qu'on ne lit pas
   {
      while (cnd >= 0 && p[cnd] != s[i]) // le prochain char de p
         cnd = T[cnd];                   // on recule dans p
      cnd++;         // maintenant que le prochain char convient, avancer
      if (cnd == np) // on a atteint la fin de p, donc on a trouvé un match
      {
         // on recule dans p au cas où le prochain match chevauche
         printf("match at %d\n", i - np + 1); 
         cnd = T[cnd];
      }
   }
}

int main(void)
{
   return 0;
}
