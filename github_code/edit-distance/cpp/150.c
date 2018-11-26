/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   levenshtein_equation.cpp
 * Author: sainivi1
 * 
 * Created on February 25, 2017, 6:09 PM
 */

#include "levenshtein_equation.h"
#include "m2_structs.h"
#include "m1.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int get_levenshtein_distance (string a, string b){
	if (a == b)
		return 0;
	if (a.empty())
		return b.size();
	if (b.empty())
		return a.size();

	vector<int> work_vector_0;
	vector<int> work_vector_1;

	work_vector_1.resize(b.size() + 1);

	for (unsigned i = 0; i < work_vector_1.size(); i++){
		work_vector_0.push_back(i);
	}

	for (unsigned i = 0; i < a.length(); i++){
		work_vector_1[0] = i + 1;

		for (unsigned j = 0; j < b.length(); j++){
			int cost;
                        
                        //check for case sensitivity 
			if (a[i] == b[j] || a[i] + 'a' - 'A' == b[j] || a[i] == b[j] + 'a' - 'A')
				cost = 0;
			else
				cost = 1;
			work_vector_1[j + 1] = std::min(work_vector_1[j] + 1, work_vector_0[j + 1] + 1);
			work_vector_1[j + 1] = min(work_vector_1[j + 1], work_vector_0[j] + cost);
		}

		work_vector_0 = work_vector_1;
	}

	return work_vector_1[b.length()];
}

bool levenschtein_compare(levenschteinSortedThings a, levenschteinSortedThings b) {
    return a.distance < b.distance;
}

void sort_levenschtein(string& query, vector<levenschteinSortedThings>& lev_vector, myPosition& my_pos){
    for (unsigned i = 0; i < lev_vector.size(); i++){
        lev_vector[i].distance = get_levenshtein_distance(lev_vector[i].name, query);
        lev_vector[i].distance += find_distance_between_two_points(lev_vector[i].position, my_pos.position)/100000;
    }
    sort(lev_vector.begin(), lev_vector.end(), levenschtein_compare);
}
