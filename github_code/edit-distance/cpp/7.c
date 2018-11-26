/* ****************************************************************************
    Copyright (C) 2003-2004 Eva Brucherseifer <eva.brucherseifer@basyskom.com>
		  2005	    Stanislav visnovsky <visnovsky@kde.org>

    This file is part of the KDE project

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

  In addition, as a special exception, the copyright holders give
  permission to link the code of this program with any edition of
  the Qt library by Trolltech AS, Norway (or with modified versions
  of Qt that use the same license as Qt), and distribute linked
  combinations including the two.  You must obey the GNU General
  Public License in all respects for all of the code used other than
  Qt. If you modify this file, you may extend this exception to
  your version of the file, but you are not obligated to do so.  If
  you do not wish to do so, delete this exception statement from
  your version.

**************************************************************************** */

#include "stringdistance.h"

using namespace std;

//! Debug-Messages 0 : off  1 : a few  10 : more 
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


/** This function walk trough the treeS(left & right) at the same time.
  * There are in both entities the same number of trees!
  * This function sums all the distances between all trees.
  * For the calculation of the distance between two trees, it calls the function calculate.
  */
double Distance::operator()(const QString& left_string, const QString& right_string)
{
	m_distance = 0.00;
	if (left_string == right_string)
		return 0.00; // saves calculation time, both entities are the same
	
	// swap strings, our matrix requires that	
	if (left_string.length () < right_string.length() )
	{
	    m_distance = calculate(right_string, left_string);
	}
	else
	{
	    m_distance = calculate(left_string, right_string);
	}

//	if (debug > 0)  cout << " --> total distance: " << m_distance << endl;
	return m_distance;
}

/** This function calculates the distance between two nodes.
  * For the calculation you can specify two variables gap & distance.
  */
int Distance::nodeDistance(const QString& left_letter, const QString& right_letter)
{
	if ( left_letter == right_letter )
	{
//		if (debug > 0)  cout << ".";
		return 0;
	}
	else
	{
//		if (debug > 0)  cout << "!";
		return editCostReplace();
	}
}

/** This function walks along the treeS(left & right) at the same time.
  * There are in both entities the same number of nodes, hopefully! But it doesn't care.
  * This function sums all the distances between all nodes.
  * For the calculation you can specify the distance between two nodes in variable distance
  */
double HammingDistance::calculate(const QString& left_string, const QString& right_string)
{
	double hammingDistance = 0.00;
//	if (debug > 0)
//		cout << left_string.length() << " " << right_string.length() << "\t";

	unsigned int i=0;
	unsigned int j=0;
	for ( ; i != left_string.length() && j != right_string.length() ;
	        ++i,++j)
		hammingDistance += double(nodeDistance(left_string[i], right_string[i]));
	for ( ; i != left_string.length() ; ++i )
	{
		++hammingDistance;
//		if (debug > 9)   cout << "!";
	}
	for ( ; j != right_string.length() ; ++j)
	{
		++hammingDistance;
//		if (debug > 9)   cout << "!";
	}
	return hammingDistance;
}


/** This function walk along the treeS(left & right) at the same time.
  * It uses the Levenshtein-algorithm for the calculation of the distance between two trees.
  * A matrice D is generated which represent the distribution of distances between two trees.
  * The last element represent the Levenshtein-distance.
  */
double LevenshteinDistance::calculate(const QString&  left_string, const QString& right_string)
{
//	if (debug > 0)
//		cout << left_string.length() << " " << right_string.length() << "\t";

	unsigned int left_size = left_string.length()+1;
	unsigned int right_size = right_string.length()+1;

	int *_D = new int[left_size * right_size];
	
	for (unsigned int i = 0 ; i < left_size * right_size; i++ )
	    _D[i] = 0;

#define D(a,b) (_D[(a)+(b)*left_size])


//	boost::numeric::ublas::matrix<int> D(left_size, right_size);
//	D = zero_boost::numeric::ublas::matrix<int>(left_size, right_size);

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

