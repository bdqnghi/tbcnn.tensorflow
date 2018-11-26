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

/** cette classe contient une table pour calculer la distance de Levenshtein entre
 * le mot recherche et la chaine trouvée en parourant l'arbre binaire, elle stock
 * aussi les pointer sur les solutions
 * de l'arbre binaire. Une objet de cette classe est dans Correcteur afin d'etre threadsave
 */
class Calculator {
public:
    /**
     *  Créér un calculateur
     * @param size taille du mot le plus longue du lexique (pour préparer une table avec une taille correcte)
     */
    Calculator(unsigned int size);
    ~Calculator();

    /** réinitialiser le tableau pour une nouvelle recherche */
    void init();
    /** la valeur la plus basse de la ligne row
     * @param row la ligne qui nous intéresse
     * @param maxcol la colonne la plus à droit à regarder
     * @return la valeur la plus basse trouvée dans la ligne
     */
    unsigned int lowest(unsigned int row, unsigned int maxcol);

    /** rendre la penalité la plus basse (au dessus et à gauche dans la table

     * @param row la ligne qui nous intéresse
     * @param col la colonne  qui nous intéresse
     * @param cost le cout a rajouter
     * @return la valeur la plus basse dans le voisinage
     */
    unsigned int minNeighbour(unsigned int row, unsigned int col, int cost);

    friend ostream& operator<<(ostream& out, const Calculator& t);
    /**
     * afficher le tableau en état actuel
     * @param out le flux à utiliser
     * @param word le mot rechercher
     * @param maxrow la ligne la plus basse à afficher
     * @param maxcol la colonne la plus à droite à afficher
     */
    void status(ostream &out, const Character *word, unsigned int maxrow, unsigned int maxcol);

  /**
   *  prendre une valeur du tableau
   * @param row la ligne
   * @param col la colonne
   * @return la valeur
   */
    inline unsigned int get(unsigned row, unsigned col) {
#ifdef DEBUG
        std::cout << "GET " << row << " " << col << std::endl;
#endif
        return table[row][col];
    }

    /**
     * mettre une valeur dans la table
     * @param row la ligne
     * @param col la colonne
     * @param val la valeur
     */
    inline void set(unsigned row, unsigned col, unsigned int val) {
        table[row][col] = val;
    }

    /**
     * Mettre le caractère courant dans le stack
     * @param c
     */
    inline void push(Character &c) {
        stack.push_back(c);
    }

    /**
     * éjecter le dernier caractère du stack
     */
    inline void pop() {
        stack.pop_back();
    }

    /**
     * taille actuelle du stack
     * @return taille du stack
     */
    inline unsigned int stacksize() {
        return stack.size();
    }

    /** l'avant-dernière élément du stack. Indéfini, si longueur de stack < 2 */
    inline Character getPenultime() {
        return stack.at(stack.size()-2);
    }

    /**
     * rajouter le mot du neoud actuelle à la liste des resultats, avec sa distance de Levenshtein
     * @param wi l'entré lexicale trouvé
     * @param distance sa distance de Levenshtein
     */
    inline void addResult(WordForm *wi, unsigned int distance) {
        solutions[wi] = distance;
    }

    /**
     * rendre les résultats
     * @return
     */
    inline map<const WordForm *, unsigned int> * getresults() {
        return &solutions;
    }

    /**
     * afficher le stack actuel
     * @param out
     */
    void printstack(ostream &out) {
        char dest[10];
        out << '[';
        vector<Character>::iterator vi = stack.begin();
        if (vi != stack.end()) {
            if (*vi == 0) out << '0';
            else {
                u8_wc_toutf8(dest, *vi);
                out << dest;
            }
            for (++vi; vi != stack.end(); ++vi) {
                u8_wc_toutf8(dest, *vi);
                out << ',' << dest;
            }
        }
        out << ']' << endl;
    }

    /** mettre les types de correction permises. (Bitmap, défini dans Noeud.h)  */
    inline void setCorrectionType(unsigned int t) {
        correctiontype = t;
    }

    /** obtenir les types de correction permises. (Bitmap, défini dans Noeud.h)  */
    inline unsigned int getCorrectionType() {
        return correctiontype;
    }

    /// penalty for differences in Levenshtein distance
    static unsigned int penalty;


private:
    /// taille du tableau pour Levenshtein
    unsigned int tsize;
    /// pointer pour allouer la mémoire
    unsigned int *tmp;
    /// pointer sur les lignes
    unsigned int **table;

    /// le stack (noeuds actuellement traversés lors de la recherche avec correction)
    vector<Character>stack;

    /// les solutions: WordInfo: Levenshtein-distance
    map<const WordForm *, unsigned int> solutions;

    /// bitmap des types of correction permises (@see Noeud.h)
    unsigned int correctiontype;
};

#endif

