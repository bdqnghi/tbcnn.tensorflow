

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



class Table {
public:
    Table(unsigned int);
    ~Table();

    void init();
    
    unsigned short lowest(unsigned int row, unsigned int maxcol);

    
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


    static unsigned short penalty; 
private:
    
    unsigned int tsize;
    
    unsigned short *tmp;
    
    unsigned short **table;

    
    vector<Character>stack;

    
    map<WordForm *, unsigned short> solutions;
};

#endif    

