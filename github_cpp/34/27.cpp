#include "rcpp_naive_bayes.h"
#include <functional>

using namespace Rcpp;

/**
 * @brief Called by NaiveBayesTrain, internal use only
 *
 * @param corpus_in A corpus
 * @return List A list of words/frequencies
 * @see http://css.dzone.com/articles/spam-filtering-naive-bayes
 **/

List NaiveBayesWordsFreq (List corpus_in)
{
    //BEGIN_RCPP
    int corpusSize = corpus_in.size();
    std::map<std::string, int> wordsFrequencies;
    std::map<std::string, int>::iterator it;
    std::vector<std::string>::iterator text_it;
    for (int i = 0; i < corpusSize; ++i) {
        std::vector<std::string> texts =
            as<std::vector<std::string> > (corpus_in[i]);
        std::sort (texts.begin(), texts.end());
        for (text_it = texts.begin(); text_it != texts.end(); ++text_it) {
            it = wordsFrequencies.find (*text_it);
            if (it != wordsFrequencies.end()) {
                it->second ++;
            } else {
                wordsFrequencies.insert
                (std::pair<std::string, int> (*text_it, 2));
            }
        }
    }
    return List::create (_["wordsFrequencies"] = wordsFrequencies,
                         _["corpusSize"] = corpusSize);
    //END_RCPP
}

/**
 * @brief Creates a training model from @a corpora_in
 *
 * @param corpora_in  A list of corpus
 * @return SEXP A RcppNaiveBayes class
 **/

SEXP NaiveBayesTrain (SEXP corpora_in)
{
    //BEGIN_RCPP
    List corpora (corpora_in);
    int corporaSize = corpora.size();
    List wordsList (corporaSize);
    int total = 0;
    for (int i = 0; i < corporaSize; i++) {
        List category = NaiveBayesWordsFreq (corpora[i]);
        wordsList[i] = category;
        total += as<int> (category["corpusSize"]);
    }
    List z = List::create (_["wordsList"] = wordsList,
                           _["categorySize"] = corporaSize,
                           _["totalCorpusSize"] = total);
    z.attr ("class") = "RcppNaiveBayesTrain";
    return z;
    //END_RCPP
}


SEXP NaiveBayesPredict (const List& wordsList_in, int categoryCount_in,
                        int factor_in, SEXP unknown_in)
{
    //BEGIN_RCPP
    std::vector<double> scores (categoryCount_in);
    std::vector<std::string> unknown =
        as<std::vector<std::string> > (unknown_in);
    if (unknown.size() == 0) {
        std::fill (scores.begin(), scores.end(), 0.0);
        return wrap (scores);
    }
    std::sort (unknown.begin(), unknown.end());
    std::vector<std::string>::iterator
    unknown_it,
    words_it,
    words_cursor;
    volatile long double s = 0.0;
    volatile int corpusSize = 0;
    for (int i = 0; i < categoryCount_in; ++i) {
        s = 1.0;
        List wordsFreqTable = wordsList_in[i];
        List wordsFrequencies = wordsFreqTable["wordsFrequencies"];
        corpusSize = as<int> (wordsFreqTable["corpusSize"]);
        std::vector<std::string> words =
            as<std::vector<std::string> > (wordsFrequencies.names());
        /**
         * As unknown is sorted as well as words by std::sort, if unknown_it
         * matches words_it then the next to unknown_it should attempt to match
         * from words_it rather than from begining.
        **/
        words_cursor = words.begin();
        for (unknown_it = unknown.begin();
                unknown_it != unknown.end();
                ++unknown_it) {
            for (words_it = words_cursor;
                    words_it != words.end();
                    ++words_it) {
                if (*words_it == *unknown_it) {
                    // NOTE must use `as' to get a proper value,
                    // other wise 1 obtained
                    s *= (as<long double> (wordsFrequencies[*words_it]));
                    words_cursor = words_it;
                    break;
                }
            }
        }
        // not use std::pow
        s /= (pow (corpusSize, unknown.size() - 1) * factor_in);
        scores[i] = s;
    }
    return wrap (scores);
    //END_RCPP
}

/**
 * @brief A predictor
 *
 * @param NBT_in A model return by NaiveBayesTrain
 * @param unknown_in A corpus or a text
 * @param isCorpus_in As is
 * @return SEXP A list of scores for each case
 **/

SEXP NaiveBayesPredict (SEXP NBT_in, SEXP unknown_in, SEXP isCorpus_in)
{
    //BEGIN_RCPP
    int isCorpus = as<int> (isCorpus_in);
    List NBT (NBT_in);
    List wordsList = NBT["wordsList"];
    int categoryCount = as<int> (NBT["categorySize"]);
    int factor = as<int> (NBT["totalCorpusSize"]);
    if (isCorpus) {
        List cases (unknown_in);
        int s = cases.size();
        List predictList (s);
        for (int i = 0; i < s; i++) {
            predictList[i] = NaiveBayesPredict
                             (wordsList, categoryCount, factor, cases[i]);
        }
        return predictList;
    } else {
        List z = NaiveBayesPredict
                 (wordsList, categoryCount, factor, unknown_in);
        return z;
    }
    //END_RCPP
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; ;
