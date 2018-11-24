#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

Dataset *train_dataset, *cv_dataset, *test_dataset;
double namda;
int count0, count1;

void read_dataset(int index)
{
	cout << "Start to read the dataset" << endl;
	for (int i = 0; i < 5; ++i) if (i != index)
	{
		string file = string("training0") + char(i + '0') + string(".data");
		cout << file << endl;
		train_dataset.read_data(file);
	}
	cout << "Training data reading done." << endl;
	cout << "Training dataset size is: " << train_dataset.size() << endl;
	string cv_file = string("training0") + char(index + '0') + string(".data");
	cv_dataset.read_data(cv_file);
	cout << "CV data reading done." << endl;
	cout << "Size of CV dataset is: " << cv_dataset.size() << endl;

	string test_file = "speeches.test.liblinear";
	test_dataset.read_data(test_file);
	cout << test_dataset.size() << endl;
	cout << "Test data reading done." << endl;
}

vector<vector<vector<int> > > count(Dataset dataset)
{
	vector<vector<vector<int> > > countNumber;
	vector<vector<int> > bigTemp;
	vector<int> smallTemp;
	smallTemp.push_back(0);
	smallTemp.push_back(0);
	bigTemp.push_back(smallTemp);
	bigTemp.push_back(smallTemp);
	for (int i = 0; i < dataset.size(); ++i)
	{
		Data data = dataset.pick(i);
		vector<pair<int, int> > x = data.get_vector();
		for (int j = 0; j < x.size(); ++j)
		{
			int index = x[j].first;
			while (countNumber.size() <= index)
				countNumber.push_back(bigTemp);
			countNumber[index][x[j].second][data.get_label()]++;
		}
		if (data.get_label() == 1)
			++count1;
		else
			++count0;
	}
	return countNumber;
}

double calcAccuracy(Dataset dataset)
{
	int whole = dataset.size();
	int correct = 0;
	for (int i = 0; i < whole; ++i)
	{
		Data data = dataset.pick(i);

	}
}

int main()
{
	vector<vector<vector<int> > > finalCountNumber;
	double best_accuracy = 0;
	for (int cross-validate = 0; cross-validate < 5; ++cross-validate)
	{
		cout << "The cv set this round is: " << cross-validate << endl;
		train_dataset = new Dataset();
		cv_dataset = new Dataset();
		test_dataset = new Dataset();
		count0 = count1 = 0;

		read_dataset(cross-validate);

		vector<vector<vector<int> > > countNumber = count(train_dataset);
		double train_accuracy = calcAccuracy(train_datset, countNumber);
		double cv_accuracy = calcAccuracy(cv_dataset, countNumber);

		cout <<  cross-validate << ' ' <<train_accuracy << ' ' << cv_accuracy << endl;

		if (cv_accuracy > best_accuracy)
		{
			best_accuracy = cv_accuracy;
			finalCountNumber = countNumber;
		}
	}

	double test_accuracy = calcAccuracy(test_dataset, finalCountNumber);
	cout << "final accuracy: " << test_accuracy << endl;
}
