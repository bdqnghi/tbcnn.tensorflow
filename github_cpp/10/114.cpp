

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




class Calculator {
public:
    
    Calculator(unsigned int size);
    ~Calculator();

    
    void init();
    
    unsigned int lowest(unsigned int row, unsigned int maxcol);

    
    unsigned int minNeighbour(unsigned int row, unsigned int col, int cost);

    friend ostream& operator<<(ostream& out, const Calculator& t);
    
    void status(ostream &out, const Character *word, unsigned int maxrow, unsigned int maxcol);

  
    inline unsigned int get(unsigned row, unsigned col) {
#ifdef DEBUG
        std::cout << "GET " << row << " " << col << std::endl;
#endif
        return table[row][col];
    }

    
    inline void set(unsigned row, unsigned col, unsigned int val) {
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

    
    inline Character getPenultime() {
        return stack.at(stack.size()-2);
    }

    
    inline void addResult(WordForm *wi, unsigned int distance) {
        solutions[wi] = distance;
    }

    
    inline map<const WordForm *, unsigned int> * getresults() {
        return &solutions;
    }

    
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

    
    inline void setCorrectionType(unsigned int t) {
        correctiontype = t;
    }

    
    inline unsigned int getCorrectionType() {
        return correctiontype;
    }

    
    static unsigned int penalty;


private:
    
    unsigned int tsize;
    
    unsigned int *tmp;
    
    unsigned int **table;

    
    vector<Character>stack;

    
    map<const WordForm *, unsigned int> solutions;

    
    unsigned int correctiontype;
};

#endif

