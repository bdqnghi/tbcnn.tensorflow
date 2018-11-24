/*
 * NaiveBayes.cpp
 *
 *  Created on: 15 de nov. de 2016
 *      Author: angela
 */

#include "NaiveBayes.h"
#include <iostream>
#include <string>
#include "helpers.h"

using namespace std;

NaiveBayes::NaiveBayes() {
	numAttr = 0;
	numCls = 0;
}

NaiveBayes::~NaiveBayes() {
	// TODO Auto-generated destructor stub
}

void NaiveBayes::setDataset(Dataset db) {
	dataset = db;
	numAttr = db.numAttr;
	numCls = db.numCls;
	pCls.resize(numCls, 0);
}

void NaiveBayes::train() {
	string currCls = "", currAttr = "";
	int c=0, a=0, tc, ta;
	int N = dataset.trainData.size();

	for(auto patt : dataset.trainData) {
		currCls = patt[numAttr];
		if(kClass.find(currCls) == kClass.end()) {
			kClass[currCls] = c++;
		}
		tc = kClass[currCls];
		pCls[tc]++;

		for(uint i=0; i<numAttr; i++) {
			currAttr = patt[i] + helpers::to_string(i);
			if(kAttr.find(currAttr) == kAttr.end()) {
				kAttr[currAttr] = a++;
				pAttrCls.push_back(vector<float>(numCls,0));
			}
			ta = kAttr[currAttr];
			pAttrCls[ta][tc]++;
		}
	}

	/*
	cout << "CONTADOR TOTALES\n";
	for(auto t : kClass) {
		cout << t.first << " => " << pCls[t.second] << endl;
	}

	for(auto t : kAttr) {
		cout << t.first << endl;
	}
	*/

	// Probability analysis
	for(auto &attr : pAttrCls) {
		for(uint i=0; i<numCls; i++)
			attr[i] = attr[i] * 1.0 / pCls[i];
	}

	for(auto &cls : pCls) {
		cls = cls * 1.0 / N;
	}
	/*
	cout << "\n-- RESULTS TRAINING --\n";
	for(auto t : kClass) {
		cout << t.first << " => " << pCls[t.second] << endl;
	}

	for(auto t : kAttr) {
		cout << t.first << " = " << pAttrCls[t.second][0] << endl;
	}
	*/
}

void NaiveBayes::test() {
	float prob, maxProb;
	string clsName = "", currAttr = "";
	vector<string> clsOut;

	for(auto patt : dataset.testData) {
		maxProb = 0;
		for(auto cls : kClass) {
			prob = 1;
			for(uint i=0; i<numAttr; i++) {
				currAttr = patt[i] + helpers::to_string(i);
				prob *= pAttrCls[kAttr[currAttr]][cls.second];
			}
			prob *= pCls[cls.second];

			if(prob > maxProb) {
				clsName = cls.first;
				maxProb = prob;
			}
		}
		clsOut.push_back(clsName);
	}

	cout << "\n--- RESULTS TEST ---\n";
	for(uint p=0; p<dataset.testData.size(); p++) {
		cout << p << " -> ";
		for(uint a=0; a<numAttr; a++) {
			cout << dataset.testData[p][a] << " - ";
		}
		cout << "CLS: " << clsOut[p] << endl;
	}
}
