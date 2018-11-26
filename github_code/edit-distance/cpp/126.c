/*
 * DamerauLevenshteinDistance.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: bijoys
 */

#include <tr1/unordered_map>
#include <iostream>
#include <string>

#include "DamerauLevenshteinDistance.hpp"

using namespace std;


DamerauLevenshteinDistance::DamerauLevenshteinDistance(){

}


int DamerauLevenshteinDistance::getDamerauLevenshteinDistance(string normalized_string1, string normalized_string2){

	//string normalized_string1,normalized_string2;
	//transform(string1.begin(), string1.end(),normalized_string1.begin(), ::tolower );
	//transform(string2.begin(), string2.end(),normalized_string2.begin(), ::tolower );

	if(normalized_string1.empty()){
		if(normalized_string2.empty())
			return 0;
		else
			return normalized_string2.length();
	} else if (normalized_string2.empty()){
		return normalized_string1.length();
	}

	string map_key;
	int comp = normalized_string1.compare(normalized_string2);
	if(comp == 0)
		return 0; //Return 0 if they are exactly same
	else if(comp<0)
		map_key = normalized_string1 + " " + normalized_string2;
	else
		map_key = normalized_string2 + " " + normalized_string1;

	//Find if distance already calculated
	tr1::unordered_map<string,int>::const_iterator distance = distance_map.find(map_key);
	if(distance != distance_map.end())
		return distance->second;

	//Calculate Damerau-Levenshtein distance
	int string1_len = normalized_string1.length();
	int string2_len = normalized_string2.length();
	int matrix[string1_len+1][string2_len+1];
	for(int i=0;i<=string1_len;i++)
		matrix[i][0] = i;
	for(int j=0;j<=string2_len;j++)
		matrix[0][j] = j;

	for(int i = 1; i <= string1_len; ++i) {
		for(int j = 1; j <= string2_len; ++j) {

			if(normalized_string1[i-1] == normalized_string2[j-1]){
				matrix[i][j] = matrix[i-1][j-1];
			} else {
				matrix[i][j] = minimum(matrix[i-1][j],matrix[i][j-1],matrix[i-1][j-1])+1;
			}
		}
	}

	distance_map[map_key] = matrix[string1_len][string2_len];
	return matrix[string1_len][string2_len];
}


int DamerauLevenshteinDistance::minimum(int n1,int n2, int n3){
	// 2 comparisions
	return ((n1<n2)?((n1 < n3)?n1:n3):((n2 < n3)?n2:n3));
}




