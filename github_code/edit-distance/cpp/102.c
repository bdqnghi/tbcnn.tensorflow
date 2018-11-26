/* 
 * File: Levenshtein.cpp
 * Author: Weiming Hu
 *
 * Created on Aug 3, 2017, 1:44 PM
 *
 * This file contains the function to compute the Levenshtein distance
 * of two string. The function can be used to guess the intended argument 
 * of an unknown one.
 *
 * The implementation is referenced from Github
 * https://github.com/git/git/blob/master/levenshtein.h
 *
 * Thanks to the pointer of Vlad Lazarenko
 * http://lazarenko.me/smart-getopt/
 */

/*
 * This function implements the Damerau-Levenshtein algorithm to
 * calculate a distance between strings.
 *
 * Basically, it says how many letters need to be swapped, substituted,
 * deleted from, or added to string1, at least, to get string2.
 *
 * The idea is to build a distance matrix for the substrings of both
 * strings.  To avoid a large space complexity, only the last three rows
 * are kept in memory (if swaps had the same or higher cost as one deletion
 * plus one insertion, only two rows would be needed).
 *
 * At any stage, "i + 1" denotes the length of the current substring of
 * string1 that the distance is calculated for.
 *
 * row2 holds the current row, row1 the previous row (i.e. for the substring
 * of string1 of length "i"), and row0 the row before that.
 *
 * In other words, at the start of the big loop, row2[j + 1] contains the
 * Damerau-Levenshtein distance between the substring of string1 of length
 * "i" and the substring of string2 of length "j + 1".
 *
 * All the big loop does is determine the partial minimum-cost paths.
 *
 * It does so by calculating the costs of the path ending in characters
 * i (in string1) and j (in string2), respectively, given that the last
 * operation is a substitution, a swap, a deletion, or an insertion.
 *
 * This implementation allows the costs to be weighted:
 *
 * - w (as in "sWap")
 * - s (as in "Substitution")
 * - a (for insertion, AKA "Add")
 * - d (as in "Deletion")
 *
 * Note that this algorithm calculates a distance _iff_ d == a.
 */

#include "Levenshtein.h"

size_t
levenshtein(const std::string & str1, const std::string & str2,
        size_t w, size_t s, size_t a, size_t d) {

    auto len1 = str1.size(), len2 = str2.size();
	auto row0 = new size_t[len2 + 1], 
         row1 = new size_t[len2 + 1], 
         row2 = new size_t[len2 + 1];
	size_t i = 0, j = 0;

    for (; j <= len2; j++)
        row1[j] = j * a;
    for (; i < len1; i++) {

        row2[0] = (i + 1) * d;
        for (j = 0; j < len2; j++) {

            // substitution
            row2[j + 1] = row1[j] + s * (str1[i] != str2[j]);

            // swap
            if (i > 0 && j > 0 && str1[i - 1] == str2[j] &&
                    str1[i] == str2[j - 1] &&
                    row2[j + 1] > row0[j - 1] + w)
                row2[j + 1] = row0[j - 1] + w;

            // deletion
            if (row2[j + 1] > row1[j + 1] + d)
                row2[j + 1] = row1[j + 1] + d;

            // insertion
            if (row2[j + 1] > row2[j] + a)
                row2[j + 1] = row2[j] + a;
        }

        // swap arr
        auto dummy = row0;
        row0 = row1;
        row1 = row2;
        row2 = dummy;
    }

    i = row1[len2];
    delete [] row0;
    delete [] row1;
    delete [] row2;

    return i;
}
