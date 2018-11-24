/*
 * matrix-multiplication.cpp
 *
 *  Created on: Jul 2, 2012
 *      Author: wush
 */

#include <climits>
#include <vector>
#include "cormen.hpp"

using namespace Rcpp;

SEXP MatrixMultiplication(SEXP Rdim_list) {
	BEGIN_RCPP
	IntegerVector dim_list(Rdim_list);
	if (!dim_list.size()) {
		throw std::invalid_argument("dim_list should not length zero");
	}
	size_t n(dim_list.size() - 1);
	IntegerMatrix multiple_complexity(n, n);
	for(size_t start(0); start < n;start++) {
		multiple_complexity(start, start) = 0;
	}
	for(size_t diff(1);diff < n;diff++) {
		for( size_t start(0); start < n - diff;start++) {
			multiple_complexity(start, start + diff) = INT_MAX;
			for( size_t k(0);k < diff;k++) {
				size_t temp(0);
				temp += multiple_complexity(start, start + k);
				temp += multiple_complexity(start + k + 1, start + diff);
				temp += dim_list[start] *  dim_list[start + k + 1] * dim_list[start + diff + 1];
				if (temp < multiple_complexity(start, start + diff)) {
					multiple_complexity(start, start + diff) = temp;
				}
			}
		}
	}
	return multiple_complexity;
	END_RCPP
}


