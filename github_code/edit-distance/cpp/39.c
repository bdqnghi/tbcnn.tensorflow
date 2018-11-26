/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program rates a translation with the BLEU-Score and the Levenshtein-Distance.
 * It expects 2 parameters: a <b>translation</b> and its <b>reference</b>.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "includes/constants.h"
#include "classes/Lexicon.h"
#include "classes/Bleu.h"
#include "classes/Levenshtein.h"
#include "classes/Bleu2.h"

using namespace std;

static Lexicon l;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " translation reference" << endl;
		return 0; // EXIT_FAILURE;
	}

	// open files
	ifstream trans(argv[1]);
	ifstream ref(argv[2]);
	if (!trans.good())
	{
		cerr << "ERROR: Opening translation ("<< argv[1] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}
	if (!ref.good())
	{
		cerr << "ERROR: Opening reference ("<< argv[2] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}

	string	trans_line				= "",
		ref_line				= "";
	double	average_levenshtein_dist		= 0,
		average_posindependent_levenshtein_dist = 0;

	// read trans and ref and calculate the ratings
	unsigned int	sentenceCount		= 0;
	Levenshtein*	sentence50_lev		= NULL;
	string		sentence50_trans	= "",
			sentence50_ref		= "";
	// akkus for overall BLEU-Score
	double overallBrevityPenalty = 0;
	unsigned int overallNGrams = 0;
	unsigned int overallNGramsMatching = 0;
	unsigned int overallTransSize = 0;
	unsigned int overallRefSize = 0;
	double overallPrecision = 0;
	double overallMaxN = 0;

	Bleu2 bleu2;
	while (getline(trans, trans_line) && getline(ref, ref_line))
	{
		vector<unsigned int> current_trans = l.insertSentence(trans_line);
		vector<unsigned int> current_ref   = l.insertSentence(ref_line);

		bleu2.addSentence(MAX_N_GRAMS,current_trans,current_ref);
		Bleu        *current_bleu = new Bleu       (current_trans, current_ref);
		Levenshtein *current_lev  = new Levenshtein(current_trans, current_ref);

		// sort line to calculate the pos-independent Levinshtein-Distance
			vector<string> trans_line_vec = stringSplit(trans_line, " ");
			vector<string> ref_line_vec   = stringSplit(ref_line  , " ");

			sort( trans_line_vec.begin(), trans_line_vec.end() );
			sort( ref_line_vec.begin()  , ref_line_vec.end()   );

			vector<unsigned int> current_trans_sorted = l.insertSentence(trans_line_vec);
			vector<unsigned int> current_ref_sorted   = l.insertSentence(ref_line_vec);

		Levenshtein *current_posindependent_lev = new Levenshtein(current_trans_sorted, current_ref_sorted);

		// sums for avg distances
		average_levenshtein_dist                += current_lev->getDistance();
		average_posindependent_levenshtein_dist += current_posindependent_lev->getDistance();

		// output
		cout	<< "\n***\nBLEU-Score:\t\t"	<< current_bleu->bleuScore(MAX_N_GRAMS)
			<< "\nLevenshtein:\t\t"		<< current_lev->getDistance()
			<< "\npos-ind. Levenshtein:\t"	<< current_posindependent_lev->getDistance()
			<< "\n\t t: " << trans_line
			<< "\n\t r: " << ref_line
			<< endl;
		// overall BLEU

//		overallTransSize	+= current_trans.size();
//		overallRefSize 		+= current_ref.size();
//		overallNGrams		+= current_bleu->nGramsAll;
//		overallNGramsMatching	+= current_bleu->nGramsMatchingAll;
//		overallPrecision	+= current_bleu->Cakku;

		unsigned int maxN = min((unsigned int)min((unsigned int)MAX_N_GRAMS, (unsigned int)current_trans.size()-1), (unsigned int)current_ref.size()-1);
//		overallMaxN += maxN;

		sentenceCount++;

		if (sentenceCount==50)
		{
			sentence50_lev   = current_lev;
			sentence50_trans = trans_line;
			sentence50_ref   = ref_line;
		}
		else
		{
			delete current_posindependent_lev;
			delete current_bleu;
			delete current_lev;
		}
	}

	// Output for sentence 50:
/*
	cout	<< "\n***\n\n***\nSentence50:\nLevenshtein:\t\t" << sentence50_lev->getDistance()
		<< "\nLevenshtein-Path:\t" << sentence50_lev->getPathOps()
		<< "\n" << sentence50_lev->getPath(l)
		<< "\n\t t: " << sentence50_trans
		<< "\n\t r: " << sentence50_ref
		<< endl;
*/
	// Output the avarages
	average_levenshtein_dist		/= (double)sentenceCount;
	average_posindependent_levenshtein_dist /= (double)sentenceCount;

	cout	<< "\n***\n\n***\naverage levenshtein distance: "     << average_levenshtein_dist
		<< "\naverage pos.independent levenshtein distance: " << average_posindependent_levenshtein_dist
		<< endl;


	// Output for overall BLEU-Score

	// overallBrevityPenalty
/*	int c = overallTransSize;
	int r = overallRefSize;
	overallBrevityPenalty = -1;
	if (c > r)
		overallBrevityPenalty = 1;
	if (c > 0)
		overallBrevityPenalty = (double)exp(((double)(1-r)/(double)c));

	// overallPrecision
	for (int i = 0; i < MaxN; i++)
	{
		if (Precision == 0)
			overallPrecision += 0;
		else
			overallPrecision += log(Precision[i])/(double)MaxN
	}
*/
	// (double)overallNGramsMatching/(double)overallNGrams
	double temp = bleu2.bleu2(MAX_N_GRAMS);
	cout << "\n***\n\n***\nOverall-BLEU-score:  " <<  temp << endl;

	return 0; //EXIT_SUCCESS;
}
