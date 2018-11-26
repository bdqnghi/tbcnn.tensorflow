/** \brief This class provides methods and stores data needed to compute the Levenshtein-distance of two
 *  given strings.
 */

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

        /**< This is the basic ctor of this class. */
        Levenshtein(WordList& a, WordList& b, Cost subPen, Cost insPen, Cost delPen):sentenceA(a),sentenceB(b),substitutionCost(subPen),deletionCost(delPen),insertionCost(insPen) {
            #if DBG>0
                std::cout << "Size of a is: "<<a.size()<<std::endl;
                std::cout << "Size of b is: "<<b.size()<<std::endl;
            #endif


            /*! Idea: Provide a method to change the references a and b for recycling the Levenshtein-obj in the main.cpp
                and moreover, just compare two sentences in each call of the computeDistance(...) method.
            */

            /// Matrices with |A| rows
            distances.resize(a.size());
            edits.resize(a.size());


            /// And |B| columns.
            for(unsigned int j=0;j<a.size();j++) {
                distances[j].resize(b.size());
                edits[j].resize(b.size());
            }
        };
        virtual ~Levenshtein();


        /** \brief This function allows to set the penalties for Substitution, deletion or insertion individually.
         *
         * \param type The type of the edit operation.
         * \param newCost The new cost for the edit operation.
         *
         */
        void setCost(const EditOperation& type, const Cost newCost);

        /** \brief Returns the costs for a certain editing operation.
         *
         * \param type The editing operation.
         * \return The costs for the editing operation type.
         *
         */
        Cost getCost(const EditOperation& type);

        /** \brief Set an entry of the EditMatrix, i.e. store an edit operation in it.
         *
         * \param mtx The edit matrix.
         * \param i The row coordinate in the matrix.
         * \param j The column coordinate in the matrix.
         * \param operation The edit operation supposed to be stored.
         *
         */
        void setEditOperation(const unsigned int i, const unsigned int j, EditOperation operation);

        /** \brief Retrieve the edit operation performed for a certain pair of words.
         *
         * \param mtx The edit matrix containing all editing operations for all pairs of words.
         * \param i The row entry in the matrix.
         * \param j The column entry in the matrix.
         * \return The performed edit operations performed to translate word at position i to word at position j in the other sentence.
         *
         */
        EditOperation getEditOperation(const unsigned int i, const unsigned int j);

        /** \brief This method determines the editing operation for two given words.
         *
         * \param mtx The edit matrix containing all editing operations for all pairs of words.
         * \param i The row entry in the matrix.
         * \param j The column entry in the matrix.
         * \return The performed edit operations performed to translate word at position i to word at position j in the other sentence.
         *
         */
        EditOperation determineEditOperation(const Word& a, const Word& b);
        void printSentences(const WordList& a, const WordList& b);
        Cost getPreviousCost(const unsigned int i, const unsigned int j);
        Cost getDistance(const unsigned int i, const unsigned int j);
        void calculateDistance();/*!<Calculate the word distance between two sentences.*/
        void calculateDistance(const WordList& senA, const WordList& senB);
        void setSentences(const WordList& a, const WordList& b);
        void printDistanceMatrix();
        void printEditMatrix();
        void countEditingOperations(Cost& insertions,Cost& deletion, Cost& substitutions);
        /** \brief Computes the word error rate for two given sentences based on the members sentenceA and sentenceB.
         * \param distance The distance between the words, i.e. their respective levenshtein-distance.
         * \param referenceSize The size of the reference string.
         * \return The word error rate for two sentences=Levenshtein-distance/#words in reference=spoken sentence.
         *
         */
        double getWER(Cost& distance,size_t referenceSize);

        /** \brief This method updates the sizes of the distance and the edit matrices.
         *
         * \param rows The new number of rows.
         * \param columns The new number of columns of the matrices.
         */
        void update(const unsigned int rows, const unsigned int columns);/**< Reinitialize the cost and edit matrices. */
    protected:
    private:
        WordList& sentenceA, sentenceB;/**< Set of sentences to compare. */
        Cost substitutionCost, deletionCost, insertionCost;
        DistanceMatrix distances; ///Must be initialized first with their respective sizes!
        EditMatrix edits;
};

#endif // LEVENSHTEIN_H
