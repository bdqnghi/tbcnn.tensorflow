/**
 * Implement table as column store
 * to improve performance of naive bayes
 *
 * Test data is already discretized...
 *
 * @todo fix zero probability problem
 *
 */

#include <iostream>
#include <vector>
#include <typeinfo>


using std::cout;
using std::endl;
using std::vector;


enum Age 
{
    UNDER30,
    BTW30AND40,
    OVER40,
    AGE_FEATURES
};

enum Income
{
    LOW,
    MEDIUM,
    HIGH,
    INCOME_FEATURES
};

enum Student
{
    STUDENT_NO,
    STUDENT_YES,
    STUDENT_FEATURES
};

enum CreditRating
{
    FAIR,
    EXCELLENT,
    CREDITRATING_FEATURES
};

enum Computer
{
    COMPUTER_NO,
    COMPUTER_YES,
    COMPUTER_FEATURES
};



struct Table
{
    vector<int> column_age;
    vector<int> column_income;
    vector<int> column_student;
    vector<int> column_credit_rating;
    vector<int> column_computer;

    void insert(Age age, Income insert, Student student, CreditRating credit_rating, Computer computer);
};


void Table::insert(Age age, Income income, Student student, CreditRating credit_rating, Computer computer)
{
    column_age.push_back(age);
    column_income.push_back(income);
    column_student.push_back(student);
    column_credit_rating.push_back(credit_rating);
    column_computer.push_back(computer);
};


void init_table(Table *table)
{
    table->insert(UNDER30, HIGH, STUDENT_NO, FAIR, COMPUTER_NO);
    table->insert(UNDER30, HIGH, STUDENT_NO, EXCELLENT, COMPUTER_NO);
    table->insert(BTW30AND40, HIGH, STUDENT_NO, FAIR, COMPUTER_YES);
    table->insert(OVER40, MEDIUM, STUDENT_NO, FAIR, COMPUTER_YES);
    table->insert(OVER40, LOW, STUDENT_YES, FAIR, COMPUTER_YES);

    table->insert(OVER40, LOW, STUDENT_YES, EXCELLENT, COMPUTER_NO);
    table->insert(BTW30AND40, LOW, STUDENT_YES, EXCELLENT, COMPUTER_YES);
    table->insert(UNDER30, MEDIUM, STUDENT_NO, FAIR, COMPUTER_NO);
    table->insert(UNDER30, LOW, STUDENT_YES, FAIR, COMPUTER_YES);
    table->insert(OVER40, MEDIUM, STUDENT_YES, FAIR, COMPUTER_YES);

    //table->insert(UNDER30, MEDIUM, STUDENT_YES, EXCELLENT, COMPUTER_YES);
    //table->insert(BTW30AND40, MEDIUM, STUDENT_NO, EXCELLENT, COMPUTER_YES);
    //table->insert(BTW30AND40, HIGH, STUDENT_YES, FAIR, COMPUTER_YES);
    //table->insert(OVER40, MEDIUM, STUDENT_NO, EXCELLENT, COMPUTER_NO);
}


void compute_probability(double *probabilty, vector<int> column, int number_of_features)
{

    vector<int> cummulated_features(number_of_features, 0);

    for (auto element : column)
    {
        cummulated_features[element]++;    
    }

    for (int i=0;i<number_of_features;++i) 
    {
        probabilty[i] = (double)cummulated_features[i] / column.size();
    }
}


template<int size_a, int size_b>
void compute_dependent_probability(double (&probabilty)[size_a][size_b], vector<int> column, vector<int> dependent_column, int number_of_features, int number_of_dependent_features)
{
    vector<vector<int> > cummulated_features(number_of_features, vector<int> (number_of_dependent_features,0));;
    vector<int> cummulated_dependent_features(number_of_dependent_features, 0);


    for (int i=0; i<column.size(); ++i)
    {
        cummulated_features[column[i]][dependent_column[i]]++;
        cummulated_dependent_features[dependent_column[i]]++;
    }

    for (int i=0; i<number_of_features; ++i) 
    {
        for (int j=0; j<number_of_dependent_features; ++j) 
        {
            probabilty[i][j] = (double)cummulated_features[i][j]/cummulated_dependent_features[j];
        }
    }
}

double probabilty_computer[COMPUTER_FEATURES];
double probabilty_age[AGE_FEATURES][COMPUTER_FEATURES];
double probability_income[INCOME_FEATURES][COMPUTER_FEATURES];
double probability_student[STUDENT_FEATURES][COMPUTER_FEATURES];
double probability_credit_rating[CREDITRATING_FEATURES][COMPUTER_FEATURES];


void train(Table table)
{
    // train
    compute_probability(probabilty_computer, table.column_computer, COMPUTER_FEATURES);

    compute_dependent_probability(probabilty_age, table.column_age, table.column_computer, AGE_FEATURES, COMPUTER_FEATURES);

    compute_dependent_probability(probability_income, table.column_income, table.column_computer, INCOME_FEATURES, COMPUTER_FEATURES);

    compute_dependent_probability(probability_student, table.column_student, table.column_computer, STUDENT_FEATURES, COMPUTER_FEATURES);

    compute_dependent_probability(probability_credit_rating, table.column_credit_rating, table.column_computer, CREDITRATING_FEATURES, COMPUTER_FEATURES);
}


void classify(double *result_probability, Age age, Income income, Student student, CreditRating rating)
{
    for (int i=0; i<COMPUTER_FEATURES; ++i)
    {
       result_probability[i] = probabilty_computer[i] * probabilty_age[age][i]
                                * probability_income[income][i] * probability_student[student][i]
                                * probability_credit_rating[rating][i];
    }
}


void print_classify_result(double *result_probability)
{
    cout << "The result is ... " << endl;
    cout << "Probability for computer is ..." << result_probability[COMPUTER_YES] << endl;
    cout << "Probability for no computer is ..." << result_probability[COMPUTER_NO] << endl;
}


int main() 
{
    Table table;
    init_table(&table);

    train(table);

    // train debug output 
    cout << "[debug]" << endl;
    cout << probabilty_computer[COMPUTER_YES];
    cout << probabilty_computer[COMPUTER_NO] << endl;

    cout << probabilty_age[UNDER30][COMPUTER_YES] << " ";
    cout << probabilty_age[UNDER30][COMPUTER_NO] << endl;

    cout << probability_income[MEDIUM][COMPUTER_YES] << " ";
    cout << probability_income[MEDIUM][COMPUTER_NO] << endl;

    cout << probability_student[STUDENT_YES][COMPUTER_YES] << " ";
    cout << probability_student[STUDENT_YES][COMPUTER_NO] << endl;

    cout << probability_credit_rating[FAIR][COMPUTER_YES] << " ";
    cout << probability_credit_rating[FAIR][COMPUTER_NO] << endl;

    cout << "zero prob" << endl;
    cout << probabilty_age[BTW30AND40][COMPUTER_YES] << endl;
    cout << probabilty_age[BTW30AND40][COMPUTER_NO] << endl;

    // classify
    double result_probability[COMPUTER_FEATURES] = {0};
    classify(result_probability, UNDER30, MEDIUM, STUDENT_YES, FAIR);
    print_classify_result(result_probability);


    result_probability[COMPUTER_FEATURES] = {0};
    classify(result_probability, BTW30AND40, MEDIUM, STUDENT_YES, FAIR);
    print_classify_result(result_probability);

    result_probability[COMPUTER_FEATURES] = {0};
    classify(result_probability, UNDER30, LOW, STUDENT_YES, EXCELLENT);
    print_classify_result(result_probability);

    result_probability[COMPUTER_FEATURES] = {0};
    classify(result_probability, OVER40, MEDIUM, STUDENT_YES, FAIR);
    print_classify_result(result_probability);

    result_probability[COMPUTER_FEATURES] = {0};
    classify(result_probability, UNDER30, MEDIUM, STUDENT_NO, FAIR);
    print_classify_result(result_probability);

    result_probability[COMPUTER_FEATURES] = {0};
    classify(result_probability, OVER40, LOW, STUDENT_YES, EXCELLENT);
    print_classify_result(result_probability);
}
