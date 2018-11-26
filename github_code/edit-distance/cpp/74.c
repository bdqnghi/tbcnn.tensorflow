/** This library is under the 3-Clause BSD License

Copyright (c) 2017, Orange S.A.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, 
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors 
     may be used to endorse or promote products derived from this software without
     specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 Author: Johannes Heinecke
 Version:  1.0 as of 6th April 2017
*/

#ifndef __TABLE_H__
#define __TABLE_H__



#include <iostream>
#include <vector>
#include <map>

using std::ostream;
using std::vector;
using std::map;

using std::endl;

#include "Util.h"
#include "LexicalEntry.h"

//#define DEBUG

class Table {
public:
    Table(unsigned int);
    ~Table();

    void init();
    /** la valeur la plus basse de la ligne row */
    unsigned short lowest(unsigned int row, unsigned int maxcol);

    /** rendre la penalité la plus basse (au dessus et à gauche dans la table */
    int minNeighbour(unsigned int row, unsigned int col, int cost);

    friend ostream& operator<<(ostream& out, const Table& t);
    void status(ostream &out, const Character *word, unsigned short maxrow, unsigned short maxcol);

    inline unsigned short get(unsigned row, unsigned col) {
#ifdef DEBUG
        std::cout << "GET " << row << " " << col << std::endl;
#endif
        return table[row][col];
    }

    inline void set(unsigned row, unsigned col, unsigned short val) {
        table[row][col] = val;
    }

    inline void push(Character &c) {
        stack.push_back(c);
    }

    inline void pop() {
        stack.pop_back();
    }

    inline unsigned int stacksize() {
        return stack.size();
    }

    inline void addResult(WordForm *wi, unsigned short distance) {
        solutions[wi] = distance;
    }

    inline map<WordForm *, unsigned short> * getresults() {
        return &solutions;
    }

    void printstack(ostream &out) {
        out << '[';
        vector<Character>::iterator vi = stack.begin();
        if (vi != stack.end()) {
            if (*vi == 0) out << '0';
            else out << *vi;
            for (++vi;
                    vi != stack.end(); ++vi) {
                out << ',' << *vi;
            }
        }
        out << ']' << endl;
    }


    static unsigned short penalty; // penalty for differences in Levenshtein distance
private:
    // taille du tableau pour Levenshtein
    unsigned int tsize;
    // pointer pour allouer la mémoire
    unsigned short *tmp;
    // pointer sur les lignes
    unsigned short **table;

    // le stack (noeuds actuellement traversés lors de la recherche avec correction)
    vector<Character>stack;

    // les solutions: WordInfo: Levenshtein-distance
    map<WordForm *, unsigned short> solutions;
};

#endif    

