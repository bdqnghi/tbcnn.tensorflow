#include <iostream>
#include <cstring>
using namespace std;
unsigned int counterdelete;
unsigned int counterinsert;
unsigned int prime[8] = {1007,2017,8069,32297,129193,516793,1917173};
unsigned int counter;

struct player{
    char nameplayer[10];
    unsigned int score = NULL;
    bool flag = false;
    bool deleteflag = false;
};

unsigned int hashf(char name[11],unsigned int n) {
    unsigned int P = 1, hashname = 0;
    unsigned int lengthname = strlen(name);
    for ( int i = 0; i<lengthname; i++) {
        hashname = (hashname+P*(name[i]))%n;
        P = (P*(31))%n;
    }
    return hashname;
}

unsigned int hashf2(char name[10],unsigned int n) {
    unsigned int P = 1, hashname = 0;
   unsigned  int lengthname = strlen(name);
    for ( int i = 0; i<lengthname; i++) {
        hashname = (hashname+P*(name[i]))%(n);
        P = (P*(41))%(n);
    }
    return hashname;
}

bool ifexist( char name[10],unsigned int score, player *&tab,unsigned int n,unsigned int hashname ) {
    if (!tab[hashname].flag || tab[hashname].deleteflag == true) return false;

    if( strcmp(tab[hashname].nameplayer,name) == 0 ) {
        if(tab[hashname].score < score ) {tab[hashname].score = score;}
        return true;
    }
    return false;
}

void insertvalue( unsigned int hashname, char name[10],unsigned int score, player *& tab) {
        strcpy(tab[hashname].nameplayer,name);
        tab[hashname].score = score;
        tab[hashname].flag = true;
        counterinsert++;
        tab[hashname].deleteflag = false;
}

void inserthash(char name[10], unsigned int score, player *&tab,unsigned int n) {
    unsigned int hashname = hashf(name,n);
    if(ifexist(name,score,tab,n,hashname)) return;
    if( tab[hashname].deleteflag == false && tab[hashname].flag == false ) {
        insertvalue(hashname,name,score,tab);
    }
    else {
       unsigned  int secondhash = hashf2(name, n-1);
          if ( secondhash == 0 ) secondhash = n-1;
        unsigned int value = (secondhash + hashname)%n;
        while(tab[value].flag == true) {
            if( tab[value].deleteflag == false && ifexist(name,score,tab,n,value) == true) return;
            value = (value+secondhash)%n;
        }
        insertvalue(value,name,score,tab);
    }
}

void find( char name[10], player *&tab,unsigned int n) {
    unsigned int hashname = hashf(name,n);
    if(!tab[hashname].flag) {
            cout << "ERROR" << endl;
            return;
    }
    if( tab[hashname].deleteflag == false && strcmp(tab[hashname].nameplayer,name) == 0) {
       cout << tab[hashname].score << endl;
        return;
    }

    unsigned int secondhash = hashf2(name, n-1);
    if ( secondhash == 0 ) secondhash = n-1;
    unsigned int value = (secondhash + hashname)%n;
    while(tab[value].flag) {
        if( tab[value].deleteflag == false && strcmp(tab[value].nameplayer,name) == 0) {
            cout << tab[value].score << endl;
            return;
        }
        value = (value+secondhash)%n;
    }
    cout << "ERROR" << endl;
}

void deletehash( char name[10], player*& tab,unsigned int n) {

    unsigned int hashname = hashf(name,n);
    if(!tab[hashname].flag) {
            cout << "ERROR" << endl;
            return;
    }

    if( tab[hashname].deleteflag == false && strcmp(tab[hashname].nameplayer,name) == 0 ) {
        cout << tab[hashname].nameplayer << " " << tab[hashname].score << endl;
        tab[hashname].deleteflag = true;
        counterinsert--;
        counterdelete++;
        return;
    }

   unsigned int secondhash = hashf2(name, n-1);
   if ( secondhash == 0 ) secondhash = n-1;

   unsigned int value = (secondhash + hashname)%n;
    while(tab[value].flag) {
        if( tab[value].deleteflag == false && strcmp(tab[value].nameplayer,name) == 0 ) {
            cout << tab[value].nameplayer << " " << tab[value].score << endl;
            tab[value].deleteflag = true;
            counterdelete++;
            counterinsert--;
            return;
        }
        value = (value+secondhash)%n;
    }
    cout << "ERROR" << endl;
}

player* doubletab(player*& tab,unsigned int n,unsigned int newsize) {

    player * newtab = new player[newsize];

    for ( int i = 0; i<n; i++ ) {
        if(tab[i].flag == true && tab[i].deleteflag == false ) {
            inserthash(tab[i].nameplayer, tab[i].score, newtab, newsize);
        }
    }
    counterdelete = 0;
    delete[] tab;
    return newtab;
}

player* cleartab(player*& tab,unsigned int n) {

    player * newtab = new player[n];

    for ( int i = 0; i<n; i++ ) {
        if(tab[i].flag == true && tab[i].deleteflag == false ) {
            inserthash(tab[i].nameplayer, tab[i].score, newtab, n);
        }
    }
    counterdelete = 0;
    delete[] tab;
    return newtab;
}

int main()
{
    ios_base::sync_with_stdio(0);
    unsigned int n,z,score, sizetab;
    player * tab;
    char in[11];
    char name[11];
    cin >> z;
    while(z--) {
        cin >> n;
        counterinsert = 0;
        counterdelete = 0;
        counter = 1;
        sizetab = 1007;
        tab = new player[1007];
        while(n--) {
            cin >> in;
            if ( in[0] == 'I') {
                    cin >> name >> score;
                    inserthash(name,score,tab,sizetab);
            }
            if ( in[0] == 'F')
                {
                    cin >> name;
                    find(name,tab,sizetab);
                }
            if ( in[0] == 'D')
                {
                    cin >> name;
                    deletehash(name,tab,sizetab);
                }

            if ( counterinsert > sizetab/2) {
                    tab = doubletab(tab,sizetab, prime[counter]);
                    sizetab = prime[counter];
                    counter++;
                }

            if( counterdelete > sizetab/4) {
                    tab = cleartab(tab,sizetab);
              }

            }
          delete[] tab;
        }
    return 0;
}
