#include "stdafx.h"
#include "RodCutting.h"
#include<iostream>

RodCutting::RodCutting()
{
	r = new int[LENGTH];
	memset(r, -1, LENGTH*sizeof(int));
	p = new int[LENGTH]{1,5,8,9,10,17,17,20,24,30};
	/*
	for (int i = 0; i < LENGTH; i++) {
		std::cout << p[i] << " ";
	}*/
}


RodCutting::~RodCutting()
{
	delete[] r;
	delete[] p;
}

int max(int a, int b) {
	return (a <= b) ? b : a;
}

/*
	Do rod cutting in naive ways.
*/
int RodCutting::doRodCutting(int length)
{
	if (length == 0) return 0;
	int preis = -1;
	for (int i = 1; i <= length; i++) {
		preis = max(preis, p[i-1] + doRodCutting(length - i));
	}
	return preis;
}

int RodCutting::doRodCuttingMemoization(int length)
{	
	if (r[length] >= 0) return r[length];
	int preis = -1;
	for (int i = 1; i <= length; i++) {
		preis = max(preis, p[i - 1] + doRodCutting(length - i));
	}
	r[length] = preis;
	return preis;
}

int RodCutting::doRodCuttingBottomUp(int length,int* s)
{
	for (int i = 1; i <= length; i++) {
		int preis = p[i-1];
		s[i - 1] = i;
		for (int j = 1; j < i; j++) {
			if (preis < p[j - 1] + r[i - j - 1]){
				preis = p[j - 1] + r[i - j - 1];
				s[i-1] = j;
			}
		}
		r[i-1] = preis;
	}
	return r[length-1];
}
