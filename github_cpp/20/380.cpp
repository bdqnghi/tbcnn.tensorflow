

#include "hmm.h"
#include "util.h"

#include <fstream>
#include <cassert>
#include <iostream>
#include <iomanip>

using namespace std;


//========================
//   Minimal Functions
//========================
void ShowDetail(const vector<string>& sentence, const vector<HmmKey>& pos_answers, const vector<HmmKey>& pos_results, const vector<bool> &unknown_flags)
{


  for(int i = 0; i < sentence.size(); i++){

    cout << setw(15) << sentence[i] << " " 
	 << setw(4)  << pos_answers[i] << " ";

    //未知語のチェック 
    if (unknown_flags[i] == true){

      if(pos_answers[i] == pos_results[i]){
	cout << setw(4)  << pos_results[i]
	     << "   Unknown"
	     << endl;
      }else{
	cout << "\x1b[31m" 
	     << setw(4) << pos_results[i] 
	     << "   Unknown" 
	     << "\x1b[0m"  
	     << endl;
      }

    }else{

      if(pos_answers[i] == pos_results[i]){
	cout << setw(4)  << pos_results[i] << endl;
      }else{
	cout << "\x1b[31m" << setw(4) << pos_results[i] << "\x1b[0m" <<endl;
      }

    }

  }
  cout << endl;
}





//========================
//       HmmNode
//========================

HmmNode::HmmNode(const HmmKey key) : m_key(key){
  m_transitions_count = 0;
  m_emissions_count = 0;
  m_rareword_count = 0;
  m_transitions = make_unique<Transitions>();
  m_emissions = make_unique<Emissions>();
  m_femissions = make_unique<FeatureEmissions>();
}

void HmmNode::EmissionLearning(const string &word){
  m_emissions_count++;
  (*m_emissions)[word]++;
}

void HmmNode::TransitionLearning(const HmmKey &key){
  m_transitions_count++;
  (*m_transitions)[key]++;
}


void HmmNode::FeatureEmissionLearning(F_TYPE type, const int count){
  (*m_femissions)[type]+= count;
  m_rareword_count += count;
}


//========================
//         Hmm
//========================

Hmm::Hmm(const int th, const int n) : RareWordThreshold(th), N(n){
  m_nodes = make_unique<HmmNodes>();
  m_vocablary = make_unique<Vocablary>();
  CreateNode(START_NODE_KEY);

  SetupClassifiers();
}

HmmNodePtr Hmm::GetOrCreateNode(const HmmKey &key){
  auto node = m_nodes->find(key);
  if (node == m_nodes->end()){
    (*m_nodes)[key] = CreateNode(key);
  }
  return (*m_nodes)[key];
}

HmmNodePtr Hmm::CreateNode(const HmmKey &key){
  assert(m_nodes->find(key) == m_nodes->end());
  (*m_nodes)[key] = make_shared<HmmNode>(key);
  return (*m_nodes)[key];
}


void Hmm::Learn(const string &filename){

  ifstream ifs(filename);
  if(ifs.fail()){
    cout << "failed to read text." << endl;
    exit(1);
  }

  HmmNodePtr node = GetNode(START_NODE_KEY);
  string line;

  while(getline(ifs,line)){
    auto strv = split(line);
 
    if (strv.size() != 0){
      node->TransitionLearning(strv[1]);
      node = GetOrCreateNode(strv[1]);

      node->EmissionLearning(strv[0]);
      AddToVocablary(strv[0]);

    }else{
      node = GetNode(START_NODE_KEY);
    }
  }


  for(auto node_map = m_nodes->begin(); node_map != m_nodes->end(); node_map++){
    HmmNodePtr node = node_map->second;
    const Emissions & emissions = node->GetEmissions();
    for(auto emission = emissions.begin(); emission != emissions.end(); emission++){
      // 訓練時に使った単語の特徴についても記録

      int count = emission->second;
      
      //頻度が一定以下の単語のみ未知語の特徴からの推定に用いる 
      if (count <= RareWordThreshold){
	const string& word = emission->first;
	auto f_type = ClassifyUnknown(word);
	node->FeatureEmissionLearning(f_type, count);
      }
      
    }
  }
      
   // node = GetNode("NN");
   // for(auto it = F_TYPES.begin(); it != F_TYPES.end(); it++){
   //  cout << *it << " " << node->GetFeatureEmissionProb((F_TYPE)(*it)) << endl;
   // }
   // exit(1);
}



void Hmm::Show(HmmNodePtr node, const string &type){
  
  cout << "---- [HmmKey] : " << node->GetKey() << " ----" << endl;
  if (type == "emission"){
    auto emissions = node->GetEmissions();
    for(auto it = emissions.begin(); it != emissions.end(); it++){
      cout << it->first << " " << GetEmissionProb(it->first, node)<< endl;
    }
  }else if (type == "transition"){
    auto transitions = node->GetTransitions();
    for(auto it = transitions.begin(); it != transitions.end(); it++){
      cout << it->first << " " << GetTransitionProb(it->first, node)<< endl;
    }
  }
}



vector<HmmKey> Hmm::Viterbi(const vector<string> &o){
  int i,j,k;

  unordered_map<HmmKey, vector<HmmKey>> route_prev;
  unordered_map<HmmKey, vector<HmmKey>> route_next;
  unordered_map<HmmKey, double> prob_prev;
  unordered_map<HmmKey, double> prob_next;


  // from start node
  HmmNodePtr start_node = GetOrCreateNode(START_NODE_KEY);
 
 for(auto it = m_nodes->begin(); it != m_nodes->end(); it++){
    const HmmKey key = it->first; 
    const HmmNodePtr node = it->second;
    route_prev[key].push_back(key);
    prob_prev[key] = GetTransitionProb(key, start_node);
    prob_prev[key] *= GetEmissionProb(o[0], node);
  }

  for(i = 1; i < o.size(); i++){
    for(auto it_next = m_nodes->begin(); it_next != m_nodes->end(); it_next++){
      HmmKey key_next = it_next->first;
      HmmNodePtr node_next = it_next->second;
      prob_next[key_next] = 0;
      double max_prob = 0;
      HmmKey max_prob_key;

      //1つ前のイテレーションにおける各ノードからの遷移確率を合計 
      for(auto it_prev = m_nodes->begin(); it_prev != m_nodes->end(); it_prev++){
	const HmmKey key_prev = it_prev->first;
	const HmmNodePtr node_prev = it_prev->second;
	double prob = prob_prev[key_prev] * GetTransitionProb(key_next, node_prev);
	if(prob > max_prob){
	  max_prob = prob;
	  max_prob_key = key_prev;
	}
	prob_next[key_next] += prob;
      }

      prob_next[key_next] *= GetEmissionProb(o[i], node_next);
      
      //最も確率の高いルートを選択
      route_next[key_next] = route_prev[max_prob_key];
      route_next[key_next].push_back(key_next);
    }

    prob_prev = prob_next;
    route_prev = route_next;
  }

  HmmKey max_prob_key;
  double max_prob = 0;

  for(auto it = m_nodes->begin(); it != m_nodes->end(); it++){
    const HmmKey key= it->first; 
    if (prob_next[key] > max_prob){
      max_prob = prob_next[key];
      max_prob_key = key;
    }
  }

  return route_next[max_prob_key];

}


double Hmm::Test(const string & filename){

  ifstream ifs(filename);
  if(ifs.fail()){
    cout << "failed to read text." << endl;
    exit(1);
  }
  string line;
  vector<string> sentence;
  vector<HmmKey> pos_answers;

  int total_word_count = 0;
  int right_unknown_word_count = 0;
  int right_known_word_count = 0;

  vector<bool> unknown_flags;
  int unknown_word_count = 0;
  
  while(getline(ifs,line)){
    auto strv = split(line);
 
    if (strv.size() != 0){
      total_word_count++;
      if (m_vocablary->find(strv[0]) == m_vocablary->end()){
	unknown_word_count++;
	unknown_flags.push_back(true);
      }else{
	unknown_flags.push_back(false);
      }
      sentence.push_back(strv[0]);
      pos_answers.push_back(strv[1]);

    }else{
      bool mistake_flag = false;
      auto pos_results = Viterbi(sentence);
    
      //未知語or既知語に分けて正解と比較 
      for(int i = 0; i < pos_results.size(); i++){
	if(pos_results[i] == pos_answers[i]){
	  if(m_vocablary->find(sentence[i]) != m_vocablary->end()){
	    right_known_word_count++;
	  }else{
	    right_unknown_word_count++;
	  }
	}else{
	  mistake_flag = true;
	}
      }

#ifdef DETAIL
      if (mistake_flag == true){
	ShowDetail(sentence, pos_answers, pos_results, unknown_flags);
      }
#endif
      sentence.clear();
      pos_answers.clear();
      unknown_flags.clear();
	
    }
  }

  cout << "Accuracy(Known)   : " 
       << 100.0 * (double)right_known_word_count / (double)(total_word_count - unknown_word_count) 
       << "% (" << right_known_word_count << "/" << (total_word_count - unknown_word_count) << ")"
       << endl;

  cout << "Accuracy(Unknown) : " 
       << 100.0 * (double)right_unknown_word_count / (double)(unknown_word_count) 
       << "% (" << right_unknown_word_count << "/" << (unknown_word_count) << ")"
       << endl;

  cout << "Accuracy(Total)   : " 
       << 100.0 * (double)(right_known_word_count + right_unknown_word_count) / (double)(total_word_count) 
       << "% (" << (right_unknown_word_count + right_known_word_count) << "/" << (total_word_count) << ")"
       << endl;

  return (double)(right_known_word_count + right_unknown_word_count) / (double)(total_word_count) * 100.0;
}



//===========================
//     Features
//===========================


F_TYPE Hmm::ClassifyUnknown(const string &str){
  for(auto it = F_TYPES.begin(); it != F_TYPES.end(); it++){
    if (Classifiers[*it] == NULL){
      continue; 
    }
    
    if (Classifiers[*it](str)){
      return (F_TYPE)(*it); 
    }
  }
  return "F_OTHERS";
}

void Hmm::SetupClassifiers(){

  auto matchSuffix = [](const string & str, const vector<string> tokens){
    for(auto it = tokens.begin(); it != tokens.end(); it++){
      int len =  it->size();
      if(str.size() >= len){
	if(str.substr(str.size() - len) == *it){
	  return true;
	}
      }
    }
    return false;
  };

  auto matchAll = [](const string & str, const vector<string> tokens){
    for(auto it = tokens.begin(); it != tokens.end(); it++){
      if(str == *it){
	return true;
      }
    }
    return false;
  };

  // 未知語に対する分類
  // ここでは各単語が一意に属するように分類するため、F_TYPESの先頭のほうが優先度が高い

  Classifiers["F_CAP"] = [&](const string& str){
    assert(str.size() > 0);
    if(str[0] >= 'A' && str[0] <= 'Z'){
      return true;
    }
    return false;
  };

  Classifiers["F_CD"] = [&](const string& str){
    int n = str.size();
    assert(str.size() > 0);
    
    if(str[0] >= '0' && str[0] <= '9' && str[n-1] >= '0' && str[n-1] <= '9'){
      return true;
    }
    return false;
  };

  Classifiers["F_END_LY"] = [&](const string& str){
    const vector<string> tokens = {
      "ly"
    };
    return matchSuffix(str, tokens);
  };


  Classifiers["F_END_ADJ"] = [&](const string& str){
    const vector<string> tokens = {
      "less", "ible", "able", "ful", "ous", "al", "an", "ent", "ical", "ive", "ary", "esque"
    };
    return matchSuffix(str, tokens);
  };

  Classifiers["F_END_NOUN"] = [&](const string& str){
    const vector<string> tokens = {
      "eer", "ess", "ion", "age", "ty", "hood", "ment", "ics" , "dom", "ist", "ance", "cy"
    };
    return matchSuffix(str, tokens);
  };

  Classifiers["F_END_ED"] = [&](const string& str){
    const vector<string> tokens = {
      "ed"
    };
    return matchSuffix(str, tokens);
  };

  Classifiers["F_END_ER"] = [&](const string& str){
    const vector<string> tokens = {
      "er"
    };
    return matchSuffix(str, tokens);
  };

  Classifiers["F_END_EST"] = [&](const string& str){
    const vector<string> tokens = {
      "est"
    };
    return matchSuffix(str, tokens);
  };

  Classifiers["F_END_ING"] = [&](const string& str){
    const vector<string> tokens = {
      "ing"
    };
    return matchSuffix(str, tokens);
  };
  Classifiers["F_END_S"] = [&](const string& str){
    const vector<string> tokens = {
      "s"
    };
    return matchSuffix(str, tokens);
  };

  Classifiers["F_VERB"] = [&](const string& str){
    const vector<string> tokens = {
      "ize", "lify"
    };
    return matchSuffix(str, tokens);
  };

}



