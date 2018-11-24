#include "SelectiveNaiveBayes.h"
#include <algorithm>

bool decreaseOrder(std::pair<std::string,int> first, std::pair<std::string,int> second)
{
	if(first.second>=second.second)
		return true;
	else
		return false;
}

SelectiveNaiveBayes::SelectiveNaiveBayes(int flag, string filename)
{
	m_filename=filename;
	m_input=new Input(2);
	m_prob_feature.resize(2);
	m_multiInput=new MultiInput(2);
	m_new_word.resize(2);
	m_flag=flag;
}

SelectiveNaiveBayes::SelectiveNaiveBayes()
{
	m_input=new Input(2);
	m_prob_feature.resize(2);
	m_multiInput=new MultiInput(2);
	m_new_word.resize(2);
}

SelectiveNaiveBayes::~SelectiveNaiveBayes(void)
{
}

string SelectiveNaiveBayes::getNextToken(istream &in)
{
	char c;
    string ans="";
    c=in.get();

	while(!in.eof())//cleaning non letter charachters
	{
		if(c>=-1&&c<=255)
		{
			if(!isalpha(c))
				c=in.get();
			else
				break;
		}
		else
			c=in.get();
	}
	while(true)
    {
		if(c>=-1&&c<=255)
		{
			if(isalpha(c))
			{
				ans.push_back(tolower(c));
				c=in.get();
			}
			else
				break;
		}
		else
			c=in.get();
		
    }
    return ans;
}

void SelectiveNaiveBayes::readingSingleFile(string filename)
{
	ifstream fin(filename.c_str());
	string s;
	string empty ="";
	while((s=getNextToken(fin))!=empty )
	{
		++m_wordsForTest[s];
	}
	fin.close();
}

void SelectiveNaiveBayes::preprocess()
{
	m_input->readingFiles("spam_2",0,0,49,50,1396);//1396
	m_input->readingFiles("easy_ham_2",1,0,49,50,700);
	m_multiInput->readingFiles("spam_2",0,0,49,50,1396);
	m_multiInput->readingFiles("easy_ham_2",1,0,49,50,700);
	if(!m_multiInput->m_words.empty());
		m_multiInput->m_words.clear();
		cout<<"read all training files!"<<endl;
}

double SelectiveNaiveBayes::calcProb(string word,int flag)
{
	double res;
	map<string,int>::iterator itr;
	itr=m_input->m_classWords[flag].find(word);
	if(itr!=m_input->m_classWords[flag].end())
		res=(1.0+(double)m_input->m_classWords[flag][word])
			/(m_input->m_sizeVocabulary+m_input->m_numTokens[flag]);
	else
	{
		res=1.0/(double)(m_input->m_sizeVocabulary+m_input->m_numTokens[flag]);
	}
	return res;
}

void SelectiveNaiveBayes::selectFeature()
{
	//std::vector<std::pair<std::string,int> > myVec(m_input->m_words.begin(), m_input->m_words.end());
	//std::sort(myVec.begin(),myVec.end(),&decreaseOrder);
	//int k=myVec.size()*0.01;
	//std::map<std::string,int> myMap;
	//for(int i=0;i<=k;i++)
	//{
	//	myMap[myVec[i].first]=myVec[i].second;
	//}
	map<string,int>::iterator itr;
	for(itr=m_input->m_words.begin();itr!=m_input->m_words.end();)
	{
		if(itr->second<=1300)
		{
			itr=m_input->m_words.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	double sum=(double)(m_input->m_docNum[0]+m_input->m_docNum[1]);
	double doc1=(double)m_input->m_docNum[0]/sum;
	double doc2=(double)m_input->m_docNum[1]/sum;
	probc0=doc1;
	probc1=doc2;
	double correct_rate=doc1>doc2? doc1:doc2;
	for(int i=0;i<m_input->m_words.size();i++)
	{
		double max_c_rate=correct_rate;
		string max_word=m_input->m_words.begin()->first;
		for(itr=m_input->m_words.begin();itr!=m_input->m_words.end();itr++)
		{
			double cur_rate=calcCorrectRate(itr->first);
			if(cur_rate>max_c_rate)
			{
				max_c_rate=cur_rate;
				max_word=itr->first;
			}
		}
		
		if(max_c_rate>correct_rate)
		{
			correct_rate=max_c_rate;
			m_input->m_words.erase(max_word);
			m_prob_feature[0][max_word]=calcProb(max_word,0);
			m_prob_feature[1][max_word]=calcProb(max_word,1);
			cout<<"correct_rate: "<<correct_rate<<endl;
			cout<<"feature word added: "<<max_word<<endl;
		}
		else
		{
			break;
		}
	}
}

bool SelectiveNaiveBayes::testTrainingfile(int index,string word,int flag)
{
	//if(!m_wordsForTest.empty())
	//	m_wordsForTest.clear();
	//readingSingleFile(filename);
	map<string,int> m_words_test=m_multiInput->m_classWords[flag][index];
	double sum=(double)(m_input->m_docNum[0]+m_input->m_docNum[1]);
	double doc0=(double)m_input->m_docNum[0]/sum;
	double doc1=(double)m_input->m_docNum[1]/sum;
	doc0=log10(doc0);
	doc1=log10(doc1);
	map<string,int>::iterator itr;
	for(itr=m_words_test.begin();itr!=m_words_test.end();itr++)
	{
		map<string,double>::iterator itr_feature;
		itr_feature=m_prob_feature[0].find(itr->first);
		if(itr_feature!=m_prob_feature[0].end())
			doc0+=log10(m_prob_feature[0][itr->first]);
		else if(itr->first==word)
			doc0+=log10((1.0+(double)m_input->m_classWords[0][word])
						/(m_input->m_sizeVocabulary+m_input->m_numTokens[0]));
		//else
		//	doc0+=log10(1.0/(double)(m_input->m_sizeVocabulary+m_input->m_numTokens[0]));

		itr_feature=m_prob_feature[1].find(itr->first);
		if(itr_feature!=m_prob_feature[1].end())
			doc1+=log10(m_prob_feature[1][itr->first]);
		else if(itr->first==word)
			doc1+=log10((1.0+(double)m_input->m_classWords[1][word])
						/(m_input->m_sizeVocabulary+m_input->m_numTokens[1]));
		//else
		//	doc1+=log10(1.0/(double)(m_input->m_sizeVocabulary+m_input->m_numTokens[1]));
	}
	if(doc0>=doc1)
	{
		if(flag==0)
			return true;
		else
			return false;
	}
	else
	{
		if(flag==1)
			return true;
		else
			return false;
	}
}

double SelectiveNaiveBayes::calcCorrectRate(string word)
{
	double res;
	double sum_correct=0.0;
	double sum=(double)m_input->m_total_flags.size();
	for(int i=0;i<(int)m_input->m_total_flags.size();i++)
	{
		int index=i;
		if(index>=m_input->m_docNum[0])
			index=i-m_input->m_docNum[0];
		bool flag=testTrainingfile(index,word,m_input->m_total_flags[i]);
		if(flag)
			sum_correct+=1.0;
	}
	res=sum_correct/sum;
	return res;
}

void SelectiveNaiveBayes::outputModelFile()
{
	m_new_word[0]=(double)1.0/(double)(m_input->m_sizeVocabulary+m_input->m_numTokens[0]);
	m_new_word[1]=(double)1.0/(double)(m_input->m_sizeVocabulary+m_input->m_numTokens[1]);
	cout<<m_new_word[0]<<endl;
	cout<<m_new_word[1]<<endl;
	ofstream f_out("model.txt");
	f_out<<"spam review probability:"<<endl;
	f_out<<probc0<<endl;
	f_out<<"spam word probability:"<<endl;
	f_out<<m_prob_feature[0].size()<<endl;

	map<string,double>::iterator posIter;
	for(posIter=m_prob_feature[0].begin();posIter!=m_prob_feature[0].end();posIter++)
	{
		f_out<<posIter->first<<" "<<posIter->second<<endl;
	}
	f_out<<m_new_word[0]<<" "<<endl;

	f_out<<"nonspam review probability:"<<endl;
	f_out<<probc1<<endl;
	f_out<<"nonspam word probability:"<<endl;
	f_out<<m_prob_feature[1].size()<<endl;

	map<string,double>::iterator negIter;
	for(negIter=m_prob_feature[1].begin();negIter!=m_prob_feature[1].end();negIter++)
	{
		f_out<<negIter->first<<" "<<negIter->second<<endl;
	}
	f_out<<m_new_word[1]<<" "<<endl;

	f_out.close();
}

double SelectiveNaiveBayes::getProb(string word, int spam)
{
	double res;
	if(spam==0)
	{
		map<string,double>::iterator iter;
		iter=m_probModel[0].find(word);
		if(iter==m_probModel[0].end())
		{
			res=1.0;
		}
		else
			res=m_probModel[0][word];
	}
	else if(spam==1)
	{
		map<string,double>::iterator iter;
		iter=m_probModel[1].find(word);
		if(iter==m_probModel[1].end())
		{
			res=1.0;
		}
		else
			res=m_probModel[1][word];
	}	
	return res;
}

void SelectiveNaiveBayes::testResult()
{
	readingSingleFile(m_filename);
	m_probModel.resize(2);
	m_probDocModel.resize(2);
	

	//read model file
	ifstream f_in("model.txt");
	string word;
	int n;
	double prob;

	//first, probabilities for spam review
	for(int i=0;i<3;i++)
		f_in>>word;
	f_in>>m_probDocModel[0];
	for(int i=0;i<3;i++)
		f_in>>word;
	f_in>>n;
	for(int i=0;i<n;i++)
	{
		f_in>>word>>prob;
		m_probModel[0][word]=prob;
	}
	f_in>>prob;
	m_new_word[0]=prob;

	//second, probabilities for nonspam review
	for(int i=0;i<3;i++)
		f_in>>word;
	f_in>>m_probDocModel[1];
	for(int i=0;i<3;i++)
		f_in>>word;
	f_in>>n;
	for(int i=0;i<n;i++)
	{
		f_in>>word>>prob;
		m_probModel[1][word]=prob;
	}
	f_in>>prob;
	m_new_word[1]=prob;

	m_prob_res.resize(2);
	for(int i=0;i<(int)m_prob_res.size();i++)
	{
		m_prob_res[i]=log10(m_probDocModel[i]);
	}
	map<string,int>::iterator itr;

	for(int i=0;i<m_input->m_classNum;i++)
	{
		for(itr=m_wordsForTest.begin();itr!=m_wordsForTest.end();itr++)
		{
			double x=getProb(itr->first,i);
			m_prob_res[i]+=log10(x);
		}
	}

	if(m_prob_res[0]>m_prob_res[1])
	{
		if(m_flag==0)
			m_res=true;
		else
			m_res=false;
	}
	else
	{
		if(m_flag==1)
			m_res=true;
		else
			m_res=false;
	}
}