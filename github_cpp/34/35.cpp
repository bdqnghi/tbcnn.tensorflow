//============================================================================
// Name        : naive_bayes.cpp
// Author      : rnakade
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <limits>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

#define max_number_of_words_per_file 10000

set<string> vocabulary;
set<string> stop_words;

int total_files = 0;
const int NUM_CLASSES = 20;

vector<string> class_names;
vector<string> class_names_test;

struct dir_class{
	vector<string> dir_names;
	vector<string> files;
	vector<string> words;
	map<string, float> p_t_c_bernoulli;
	map<string, float> p_t_c_bernoulli_smoothed;
	map<string, float> p_t_c_multinomial;
	map<string, float> p_t_c_multinomial_smoothed;
	float p_class;
} class_features[20], class_features_test[20];

struct classification{

	int bernoulli;
	int bernoulli_smoothed;
	int multinomial;
	int multinomial_smoothed;
};

int bernoulli_confusion[NUM_CLASSES][NUM_CLASSES];
int bernoulli_smoothed_confusion[NUM_CLASSES][NUM_CLASSES];
int multinomial_confusion[NUM_CLASSES][NUM_CLASSES];
int multinomial_smoothed_confusion[NUM_CLASSES][NUM_CLASSES];

void train(string dir);
void test(string dir);
int getdir (string dir, vector<string> &files);
int get_files (string dir, vector<string> &files);
void init_confusion_matrices();
void test_class(dir_class, int);
classification classify(string);
void print_confusion_matrix(string title, int[NUM_CLASSES][NUM_CLASSES]);
int read_training_words_from_class_files(dir_class&);
void print_map(map<string, float>);
void print_array(float[], int length);
void read_stop_words(string);
int read_vocabulary();

int main()
{
	//string train_dir = string("/Users/rnakade/Downloads/20news-bydate/20news-bydate-train/");
	//string test_dir = string("/Users/rnakade/Downloads/20news-bydate/20news-bydate-test/");
	string train_dir = string("/home/mkevinr/Desktop/20news-bydate/20news-bydate-train/");
	string test_dir = string("/home/mkevinr/Desktop/20news-bydate/20news-bydate-test/");
	//string train_dir = "test_documents/";
	string stop_words_file = "stop_words";
	read_stop_words(stop_words_file);
	train(train_dir);
	test(test_dir);
    return 0;
}

void read_stop_words(string file)
{
	ifstream ifs(file.c_str());
	string str;

	while (ifs >> str)
	{
		// Convert the string to lower case
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		stop_words.insert(str);
	}
}

void test(string dir)
{
	cout << "testing..." << endl;

	init_confusion_matrices();
	getdir(dir,class_names_test); // get list of sub directories

	//store file names for each class
	for(int i = 0; i<class_names_test.size(); i++)
		get_files(dir + class_names_test[i] , class_features_test[i].files);

	for(int i = 0; i < NUM_CLASSES; i++)
	{
		cout << "  class " << i << "/" << NUM_CLASSES << "..." << endl;
		test_class(class_features_test[i], i);
	}


	print_confusion_matrix("Bernoulli", bernoulli_confusion);
	cout << endl;
	print_confusion_matrix("Bernoulli Smoothed", bernoulli_smoothed_confusion);
	cout << endl;
	print_confusion_matrix("Multinomial", multinomial_confusion);
	cout << endl;
	print_confusion_matrix("Multinomial Smoothed", multinomial_smoothed_confusion);


}

void init_confusion_matrices()
{
	for(int i = 0; i < NUM_CLASSES; i++)
	{
		for(int j = 0; j < NUM_CLASSES; j++)
		{
			bernoulli_confusion[i][j] = 0;
			bernoulli_smoothed_confusion[i][j] = 0;
			multinomial_confusion[i][j] = 0;
			multinomial_smoothed_confusion[i][j] = 0;
		}
	}
}

void test_class(dir_class curr_class, int index)
{
	classification c;
	for(int i = 0; i < curr_class.files.size(); i++)
	{
		c = classify(curr_class.files[i]);
		bernoulli_confusion[index][c.bernoulli]++;
		bernoulli_smoothed_confusion[index][c.bernoulli_smoothed]++;
		multinomial_confusion[index][c.multinomial]++;
		multinomial_smoothed_confusion[index][c.multinomial_smoothed]++;
	}
}

classification classify(string file)
{
	classification return_classification;
	ifstream ifs(file.c_str());
	string str;
	float bernoulli_class_scores[NUM_CLASSES];
	float bernoulli_smoothed_class_scores[NUM_CLASSES];
	float multinomial_class_scores[NUM_CLASSES];
	float multinomial_smoothed_class_scores[NUM_CLASSES];


	for(int i = 0; i < NUM_CLASSES; i++)
	{
		bernoulli_class_scores[i] = class_features[i].p_class;
		bernoulli_smoothed_class_scores[i] = log10(class_features[i].p_class);
		multinomial_class_scores[i] = class_features[i].p_class;
		multinomial_smoothed_class_scores[i] = log10(class_features[i].p_class);
	}

	int word_count = 0;
	while (ifs >> str)
	{
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		if(stop_words.count(str) > 0)
		{
			continue;
		}
		if(vocabulary.count(str) > 0)
		{
			for(int i = 0; i < NUM_CLASSES; i++)
			{
				bernoulli_class_scores[i] *= class_features[i].p_t_c_bernoulli[str];
				bernoulli_smoothed_class_scores[i] += class_features[i].p_t_c_bernoulli_smoothed[str];
				multinomial_class_scores[i] *= class_features[i].p_t_c_multinomial[str];
				multinomial_smoothed_class_scores[i] += class_features[i].p_t_c_multinomial_smoothed[str];
			}
		}
		word_count++;
	}

	float bernoulli_max_score = -1000000.0;//numeric_limits<float>::lowest();
	float bernoulli_smoothed_max_score = -1000000.0;//numeric_limits<float>::lowest();
	float multinomial_max_score = -1000000.0;//numeric_limits<float>::lowest();
	float multinomial_smoothed_max_score = -1000000.0;//numeric_limits<float>::lowest();
	for(int i = 0; i < NUM_CLASSES; i++)
	{
		if(bernoulli_class_scores[i] > bernoulli_max_score)
		{
			bernoulli_max_score = bernoulli_class_scores[i];
			return_classification.bernoulli = i;
		}

		if(bernoulli_smoothed_class_scores[i] > bernoulli_smoothed_max_score)
		{
			bernoulli_smoothed_max_score = bernoulli_smoothed_class_scores[i];
			return_classification.bernoulli_smoothed = i;
		}

		if(multinomial_class_scores[i] > multinomial_max_score)
		{
			multinomial_max_score = multinomial_class_scores[i];
			return_classification.multinomial = i;
		}

		if(multinomial_smoothed_class_scores[i] > multinomial_smoothed_max_score)
		{
			multinomial_smoothed_max_score = multinomial_smoothed_class_scores[i];
			return_classification.multinomial_smoothed = i;
		}
	}

	return return_classification;
}

void print_map(map<string, float> m)
{
	map<string, float>::iterator iter;
	for(iter = m.begin(); iter != m.end(); iter++)
	{
		cout << iter->first << ": " << iter->second << endl;
	}
}

void print_map(map<string, int> m)
{
	map<string, int>::iterator iter;
	for(iter = m.begin(); iter != m.end(); iter++)
	{
		cout << iter->first << ": " << iter->second << endl;
	}
}

void print_array(float array[], int length)
{
	cout << array[0];
	for(int i = 1; i < length; i++)
	{
		cout << "," << array[i];
	}
	cout << endl;
}

void print_confusion_matrix(string title, int matrix[NUM_CLASSES][NUM_CLASSES])
{
	cout << title << endl;
	for(int i = 0; i < class_names.size(); i++)
	{
		cout << "," << class_names[i];
	}
	cout << endl;
	for(int i = 0; i < NUM_CLASSES; i++)
	{
		cout << class_names[i];
		for(int j = 0; j < NUM_CLASSES; j++)
		{
			cout << "," << matrix[i][j];
		}
		cout << endl;
	}

	int num_correct = 0;
	int num_false = 0;
	for(int i = 0; i < NUM_CLASSES; i++)
	{
		for(int j = 0; j < NUM_CLASSES; j++)
		{
			if(i == j)
			{
				num_correct += matrix[i][j];
			}
			else
			{
				num_false += matrix[i][j];
			}
		}
	}

	float accuracy = (float) num_correct / (num_false + num_correct);

	cout << "accuracy: " << accuracy << endl;
}


//train phase
void train(string dir)
{
	cout << "training..." << endl;

	getdir(dir,class_names); // get list of sub directories

	//store file names for each class
	for(int i = 0; i<class_names.size(); i++)
		get_files(dir + class_names[i] , class_features[i].files);

	//calculate probability for each class
	total_files = 0;
	for(int i = 0; i<class_names.size(); i++)
		total_files += (class_features[i].files.size());

	for(int i = 0; i < NUM_CLASSES; i++)
	{
		class_features[i].p_class = (float) class_features[i].files.size() / total_files;
	}

	read_vocabulary();

	for(int i = 0; i<class_names.size(); i++)
	{
		cout << "  class " << i << "/" << NUM_CLASSES << "..." << endl;
		read_training_words_from_class_files(class_features[i]);
	}
}

int read_vocabulary()
{
	cout << "  reading in vocabulary..." << endl;
	for(int i = 0; i < NUM_CLASSES; i++)
	{
		for(int j = 0; j < class_features[i].files.size(); j++)
		{
			ifstream ifs(class_features[i].files[j].c_str());
			string str;
			while (ifs >> str)
			{
				// Converts the string to lower case.
				transform(str.begin(), str.end(), str.begin(), ::tolower);
				if(stop_words.count(str) > 0)
				{
					continue;
				}
				vocabulary.insert(str);
			}

			ifs.close();
		}
	}
	return 0;
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    string file_name;
    while ((dirp = readdir(dp)) != NULL) {
    	file_name = string(dirp->d_name);
    	if(!(file_name == "." || file_name == ".."))
    	{
    		files.push_back(file_name);
    	}
    }
    closedir(dp);
    return 0;
}

int get_files(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    string file_name;
    while ((dirp = readdir(dp)) != NULL) {
    	file_name = string(dirp->d_name);
    	if(!(file_name == "." || file_name == ".."))
    	{
    		files.push_back(dir + "/" +file_name);
    	}
    }
    closedir(dp);
    return 0;
}

void init_term_counts_and_document_counts(map<string, int>& term_counts, map<string, int>& document_counts)
{
	set<string>::iterator iter;
	for(iter = vocabulary.begin(); iter != vocabulary.end(); iter++)
	{
		term_counts[*iter] = 0;
		document_counts[*iter] = 0;
	}
}

int read_training_words_from_class_files(dir_class& curr_class)
{
	vector<string> files = curr_class.files;
	vector<string> words = curr_class.words;
	// The count for each term across all documents in this class.
	map<string, int> term_counts;
	// Each term present in the current document. No duplicates.
	set<string> document_terms;
	// The number of documents in this class that contain each term.
	map<string, int> document_counts;
	init_term_counts_and_document_counts(term_counts, document_counts);
	// The total number of words contained in documents of this class.
	int num_words = 0;
	for(int i = 0; i < files.size(); i++)
	{
		document_terms.clear();
		ifstream ifs(files[i].c_str());
		string str;
		while (ifs >> str)
		{
			// Converts the string to lower case.
			transform(str.begin(), str.end(), str.begin(), ::tolower);
			if(stop_words.count(str) > 0)
			{
				continue;
			}
		    words.push_back(str);
	    	term_counts[str] += 1;

		    document_terms.insert(str);
		    num_words++;
		}

		set<string>::iterator iter;
		for(iter = document_terms.begin(); iter != document_terms.end(); ++iter)
		{
			document_counts[*iter] += 1;
		}

		ifs.close();
	}


	map<string, float> p_t_c_bernoulli;
	map<string, float> p_t_c_bernoulli_smoothed;
	map<string, int>::iterator iter;
	for(iter = document_counts.begin(); iter != document_counts.end(); iter++)
	{
		p_t_c_bernoulli[iter->first] = (float) iter->second / curr_class.files.size();
		p_t_c_bernoulli_smoothed[iter->first] = log10((float) (iter->second + 1) / (curr_class.files.size() + 1));
	}
	curr_class.p_t_c_bernoulli = p_t_c_bernoulli;
	curr_class.p_t_c_bernoulli_smoothed = p_t_c_bernoulli_smoothed;

	map<string, float> p_t_c_multinomial;
	map<string, float> p_t_c_multinomial_smoothed;
	for (iter = term_counts.begin(); iter != term_counts.end(); ++iter)
    {
    	p_t_c_multinomial[iter->first] = (float) iter->second / num_words;
    	p_t_c_multinomial_smoothed[iter->first] = log10((float) (iter->second + 1)/ (num_words + 1));
    }
	curr_class.p_t_c_multinomial = p_t_c_multinomial;
	curr_class.p_t_c_multinomial_smoothed = p_t_c_multinomial_smoothed;

	return 0;
}
