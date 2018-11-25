

#include "stringdistance.h"

using namespace std;


int Distance::debug = 0;
const int Distance::editCost_replace_base = 1;

const int HammingDistance::editCost = 1;

const int LevenshteinDistance::editCost_replace = 1;
const int LevenshteinDistance::editCost_insert = 1;
const int LevenshteinDistance::editCost_delete = 1;


double relativeDistance(double distance, const QString& left_string, const QString& right_string)
{
	double maxsize=0;
	double compsize=0;
	maxsize = left_string.length();
	compsize=right_string.length();
	if (compsize>maxsize)
		maxsize=compsize;
	return distance/(double)maxsize;
}



double Distance::operator()(const QString& left_string, const QString& right_string)
{
	m_distance = 0.00;
	if (left_string == right_string)
		return 0.00; 
	
	
	if (left_string.length () < right_string.length() )
	{
	    m_distance = calculate(right_string, left_string);
	}
	else
	{
	    m_distance = calculate(left_string, right_string);
	}


	return m_distance;
}


int Distance::nodeDistance(const QString& left_letter, const QString& right_letter)
{
	if ( left_letter == right_letter )
	{

		return 0;
	}
	else
	{

		return editCostReplace();
	}
}


double HammingDistance::calculate(const QString& left_string, const QString& right_string)
{
	double hammingDistance = 0.00;



	unsigned int i=0;
	unsigned int j=0;
	for ( ; i != left_string.length() && j != right_string.length() ;
	        ++i,++j)
		hammingDistance += double(nodeDistance(left_string[i], right_string[i]));
	for ( ; i != left_string.length() ; ++i )
	{
		++hammingDistance;

	}
	for ( ; j != right_string.length() ; ++j)
	{
		++hammingDistance;

	}
	return hammingDistance;
}



double LevenshteinDistance::calculate(const QString&  left_string, const QString& right_string)
{



	unsigned int left_size = left_string.length()+1;
	unsigned int right_size = right_string.length()+1;

	int *_D = new int[left_size * right_size];
	
	for (unsigned int i = 0 ; i < left_size * right_size; i++ )
	    _D[i] = 0;

#define D(a,b) (_D[(a)+(b)*left_size])





	unsigned int l,r;
	D(0,0) = 0;
	for(l = 1; l < left_size; l++)
		D(l,0) = D(l-1,0) + editCost_delete;
	for(r = 1; r < right_size; r++)
		D(0,r) = D(0,r-1) + editCost_insert;

	int tmp_value;
	for(l = 1; l < left_size; l++)
	{
		for(r = 1; r < right_size; r++)
		{
			tmp_value = QMIN( ( D(l-1,r)   + editCost_delete ),
			                 ( D(l-1,r-1) + nodeDistance(left_string[l-1], right_string[r-1]) ) ) ;
			D(l,r) = QMIN( tmp_value,
					( D(l,r-1)   + editCost_insert ) );
		}
	}
	
	double res (D(left_size-1,right_size-1));
	
	delete[] _D;
	
	return res;
}

