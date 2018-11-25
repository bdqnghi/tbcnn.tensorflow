

#include "Typedef.h"
#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>
#include <iomanip>

class Levenshtein
{

    public:
        Levenshtein(WordList& a, WordList& b):Levenshtein(a,b,1,1,1) {};
        Levenshtein(WordList& a, WordList& b, Cost pen):Levenshtein(a,b,pen,pen,pen) {};

        
        Levenshtein(WordList& a, WordList& b, Cost subPen, Cost insPen, Cost delPen):sentenceA(a),sentenceB(b),substitutionCost(subPen),deletionCost(delPen),insertionCost(insPen) {
            #if DBG>0
                std::cout << "Size of a is: "<<a.size()<<std::endl;
                std::cout << "Size of b is: "<<b.size()<<std::endl;
            #endif


            

            
            distances.resize(a.size());
            edits.resize(a.size());


            
            for(unsigned int j=0;j<a.size();j++) {
                distances[j].resize(b.size());
                edits[j].resize(b.size());
            }
        };
        virtual ~Levenshtein();


        
        void setCost(const EditOperation& type, const Cost newCost);

        
        Cost getCost(const EditOperation& type);

        
        void setEditOperation(const unsigned int i, const unsigned int j, EditOperation operation);

        
        EditOperation getEditOperation(const unsigned int i, const unsigned int j);

        
        EditOperation determineEditOperation(const Word& a, const Word& b);
        void printSentences(const WordList& a, const WordList& b);
        Cost getPreviousCost(const unsigned int i, const unsigned int j);
        Cost getDistance(const unsigned int i, const unsigned int j);
        void calculateDistance();
        void calculateDistance(const WordList& senA, const WordList& senB);
        void setSentences(const WordList& a, const WordList& b);
        void printDistanceMatrix();
        void printEditMatrix();
        void countEditingOperations(Cost& insertions,Cost& deletion, Cost& substitutions);
        
        double getWER(Cost& distance,size_t referenceSize);

        
        void update(const unsigned int rows, const unsigned int columns);
    protected:
    private:
        WordList& sentenceA, sentenceB;
        Cost substitutionCost, deletionCost, insertionCost;
        DistanceMatrix distances; 
        EditMatrix edits;
};

#endif 
