

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
		return 0; 
	}

	
	ifstream trans(argv[1]);
	ifstream ref(argv[2]);
	if (!trans.good())
	{
		cerr << "ERROR: Opening translation ("<< argv[1] <<") failed." << endl;
		return 1; 
	}
	if (!ref.good())
	{
		cerr << "ERROR: Opening reference ("<< argv[2] <<") failed." << endl;
		return 1; 
	}

	string	trans_line				= "",
		ref_line				= "";
	double	average_levenshtein_dist		= 0,
		average_posindependent_levenshtein_dist = 0;

	
	unsigned int	sentenceCount		= 0;
	Levenshtein*	sentence50_lev		= NULL;
	string		sentence50_trans	= "",
			sentence50_ref		= "";
	
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

		
			vector<string> trans_line_vec = stringSplit(trans_line, " ");
			vector<string> ref_line_vec   = stringSplit(ref_line  , " ");

			sort( trans_line_vec.begin(), trans_line_vec.end() );
			sort( ref_line_vec.begin()  , ref_line_vec.end()   );

			vector<unsigned int> current_trans_sorted = l.insertSentence(trans_line_vec);
			vector<unsigned int> current_ref_sorted   = l.insertSentence(ref_line_vec);

		Levenshtein *current_posindependent_lev = new Levenshtein(current_trans_sorted, current_ref_sorted);

		
		average_levenshtein_dist                += current_lev->getDistance();
		average_posindependent_levenshtein_dist += current_posindependent_lev->getDistance();

		
		cout	<< "\n***\nBLEU-Score:\t\t"	<< current_bleu->bleuScore(MAX_N_GRAMS)
			<< "\nLevenshtein:\t\t"		<< current_lev->getDistance()
			<< "\npos-ind. Levenshtein:\t"	<< current_posindependent_lev->getDistance()
			<< "\n\t t: " << trans_line
			<< "\n\t r: " << ref_line
			<< endl;
		







		unsigned int maxN = min((unsigned int)min((unsigned int)MAX_N_GRAMS, (unsigned int)current_trans.size()-1), (unsigned int)current_ref.size()-1);


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

	

	
	average_levenshtein_dist		/= (double)sentenceCount;
	average_posindependent_levenshtein_dist /= (double)sentenceCount;

	cout	<< "\n***\n\n***\naverage levenshtein distance: "     << average_levenshtein_dist
		<< "\naverage pos.independent levenshtein distance: " << average_posindependent_levenshtein_dist
		<< endl;


	

	

	
	double temp = bleu2.bleu2(MAX_N_GRAMS);
	cout << "\n***\n\n***\nOverall-BLEU-score:  " <<  temp << endl;

	return 0; 
}
