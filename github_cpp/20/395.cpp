/*
 * hmm.cpp
 *
 *  Created on: 2016/09/03
 *      Author: ryosuke-k
 */

#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "hmm.h"
#include "conllu.h"
#include "utils.h"
#include "vocab2id.h"

using namespace std;

HMM::HMM(std::vector<vector<Conllu>> sentences) :
        mSentences(sentences) {
}

void HMM::makeVocab() {
//    Vocab2id vocab2int;
//    Vocab2id pos2int;
    for (auto sentence = mSentences.begin(); sentence != mSentences.end();
            ++sentence) {
        for (auto token = sentence->begin(); token != sentence->end();
                ++token) {
            string word = (*token).getLemma();
            string pos = (*token).getUpostag();
            mVocab_id_mp.setVocab(word);
            mPos_id_mp.setVocab(pos);
        }
    }
    mVocab_id_mp.setVocab("<UNK>");
    mPos_id_mp.setVocab("<s>");
    mPos_id_mp.setVocab("</s>");
}

void HMM::CountMap(map<int, int> *mp, int key) {
    auto itr = mp->find(key);
    if (itr != mp->end()) {
        itr->second++;
    } else {
        (*mp)[key] = 1;
    }
}

void HMM::CountMap(map<vector<int>, int> *mp, vector<int> key) {
    auto itr = mp->find(key);
    if (itr != mp->end()) {
        itr->second++;
    } else {
        (*mp)[key] = 1;
    }
}

void HMM::Count() {
    for (auto sentence = mSentences.begin(); sentence != mSentences.end();
            ++sentence) {
        int previous(mPos_id_mp.getId("<s>"));
        HMM::CountMap(&mContext_Count, previous);

        for (auto word = (*sentence).begin(); word != (*sentence).end();
                ++word) {
            int current_word = mVocab_id_mp.getId(word->getLemma());
            int current_pos = mPos_id_mp.getId(word->getUpostag());

            vector<int> trans { previous, current_pos };
            vector<int> emiss { current_pos, current_word };

            CountMap(&mTransitionCount, trans);
            CountMap(&mEmissionCount, emiss);
            CountMap(&mContext_Count, current_pos);
            previous = current_pos;
        }

        vector<int> to_end { previous, mPos_id_mp.getId("</s>") };
        CountMap(&mTransitionCount, to_end);
    }
}

void HMM::CalcProb() {
    // Transition table
    for (auto itr = mTransitionCount.begin(); itr != mTransitionCount.end();
            ++itr) {
        vector<int> key = itr->first;
        mTransition_Prob[key] = itr->second / double(mContext_Count[key[0]]);
    }

    // Emission table
    for (auto itr = mEmissionCount.begin(); itr != mEmissionCount.end();
            ++itr) {
        double lambda = 0.01;
        vector<int> key = itr->first;
        mEmission_Prob[key] =  itr->second
                / double(mContext_Count[key[0]])
                + (1 - lambda) * 1 / mVocab_id_mp.size();
        // Unknown words
        mEmission_Prob[ { key[0], mVocab_id_mp.getId("<UNK>") }] = 0.01;
    }
    cout  << "s " << endl;
}

void HMM::CreateModel() {
    HMM::makeVocab();
    HMM::Count();
    HMM::CalcProb();
}

void HMM::OutModel(char* modelfile) {
    ofstream outfile;
    outfile.open(modelfile, ios_base::out);

    for (auto itr = mTransition_Prob.begin(); itr != mTransition_Prob.end();
            ++itr) {
        vector<int> key = itr->first;
        double value = itr->second;
        outfile << "T" << " " << mPos_id_mp.getWord(key[0]) << " "
                << mPos_id_mp.getWord(key[1]) << " " << value << endl;
    }

    for (auto itr = mEmission_Prob.begin(); itr != mEmission_Prob.end();
            ++itr) {
        vector<int> key = itr->first;
        double value = itr->second;
        outfile << "E" << " " << mPos_id_mp.getWord(key[0]) << " "
                << mVocab_id_mp.getWord(key[1]) << " " << value << endl;
    }
}
