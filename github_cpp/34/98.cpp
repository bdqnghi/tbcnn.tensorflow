#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>

// for shuffling
#include "gsl/gsl_rng.h"
#include "gsl/gsl_randist.h"

//for distributions
#include "gsl/gsl_cdf.h"

using namespace std;

#define MIN(a,b) ((a) < (b) ? (a) : (b) )

const int experimentCount = 15;
const double smoothingEps = 0.00000000001;
const double trainPart = 0.5;

vector<bool> loadResponse(string fileName)
{
    vector<bool> ret;
    ifstream file;
    file.open(fileName.c_str(),ifstream::in);
    if (!file.good())
    {
        cout<<"error"<<endl;
    }
    cout<<"Loading response"<<endl;

    string word;
    bool temp;
    while(!file.eof())
    {
        file >> temp;
        ret.push_back(temp);
    }
    // In case of redundant last line. R package likes add such lines.
    ret.pop_back();

    file.close();
    cout<<"Loading response finished"<<endl;

    return ret;
}

void loadSamples(vector< vector <double> >& healphy,
                 vector< vector <double> >& cancer,
                 vector<bool>& resp,
                 string fileName)
{
    vector<double> healphyVec;
    vector<double> cancerVec;
    ifstream file;
    file.open(fileName.c_str(),ifstream::in);
    if (!file.good())
    {
        cout<<"error"<<endl;
    }
    cout<<"Loading samples"<<endl;
    
    double temp;
    string line;
    getline(file, line);
    istringstream iss(line);
    int count = 0;
    
    while(!iss.eof())
    {
        iss >> temp;
        if(resp[count])
            cancerVec.push_back(temp);
        else
            healphyVec.push_back(temp);
        count++;
    }
    
    cancer.push_back(cancerVec);
    healphy.push_back(healphyVec);

    while (getline(file, line))
    {
        healphyVec.clear();
        cancerVec.clear();
        istringstream iss(line);
        count = 0;
        while(!iss.eof())
        {
            iss >> temp;
            if(resp[count])
                cancerVec.push_back(temp);
            else
                healphyVec.push_back(temp);
            count++;
        }

        cancer.push_back(cancerVec);
        healphy.push_back(healphyVec);
        
        if(cancer.size() % 10000 == 0)
        {
            cout <<"progress: " << cancer.size()<<endl;
        }
    }
    cout<<"cancer.size() = "<<cancer.size()<<endl;
    file.close();
    cout<<"Loading samples finished"<<endl;
}

vector<double> mean(vector<vector<double> >& sample, vector<int>& ind)
{
    vector<double> ret;
    double sum = 0;
    vector<double> temp;
    for (int i = 0; i < sample.size(); i++)
    {
        sum = 0;
        for (int j = 0; j < ind.size(); j++)
        {
            sum += sample[i][ind[j]];
        }
        ret.push_back(sum/ind.size());
    }
    return ret;
}

vector<double> sd(vector<vector<double> >& sample, vector<int>& ind)
{
    vector<double> ret;
    double sum = 0;
    double sum2 = 0;
    int N;
    for (int i = 0; i < sample.size(); i++)
    {
        sum = 0;
        sum2 = 0;
        N = ind.size();
        for (int j = 0; j < N; j++)
        {
            sum += sample[i][ind[j]];
            sum2 += sample[i][ind[j]]*sample[i][ind[j]];
        }

        // ret.push_back(sqrt((sum2 - sum*sum/N)/(N-1)));
        ret.push_back(sqrt((sum2 - sum*sum/N)/(N)+smoothingEps));
    }
    return ret;
}

vector<int> get_sample(gsl_rng* randGenerator, int max)
{
    int* vec = new int[max];
    for (int i = 0; i < max; i++)
    {
        vec[i] = i;
    }
    gsl_ran_shuffle(randGenerator, (void*) vec, max,sizeof(*vec));
    vector<int> vecRet;
    for (int i = 0; i < max; i++)
    {
        vecRet.push_back(vec[i]);
    }
    delete [] vec;
    return vecRet;
}

struct SumErrorsStruct
{
    int healphyMis;
    int cancerMis;
    int healphyMisSquared;
    int cancerMisSquared;
    int totalMisSquared;
    int healphyMisTrain;
    int cancerMisTrain;
    SumErrorsStruct():
        healphyMis(0), cancerMis(0), healphyMisSquared(0),
        cancerMisSquared(0), totalMisSquared(0),
        healphyMisTrain(0), cancerMisTrain(0)
        {}
};

struct TrainModel
{
    vector<double> healphyMean;
    vector<double> healphySd;
    vector<double> cancerMean;
    vector<double> cancerSd;
    TrainModel(vector<double> _healphyMean,
               vector<double> _healphySd,
               vector<double> _cancerMean,
               vector<double> _cancerSd):
        healphyMean(_healphyMean),
        healphySd(_healphySd),
        cancerMean(_cancerMean),
        cancerSd(_cancerSd)
        {}
};

struct ResultStatistics
{
    double healphy_mean;
    double healphy_mean_train;
    double healphy_mean_sd;
    double cancer_mean;
    double cancer_mean_train;
    double cancer_mean_sd;
    int tc;
    double total_mean;
    double total_mean_sd;
    string cancerName;
    int experimentCount;
    int healphyTestSize;
    int cancerTestSize;
    void Export(string filename)
        {
            ofstream ofile;
            ofile.open(filename.c_str(), iostream::app);
            ofile<<cancerName<<" ";
            ofile<<experimentCount<<" ";
            ofile<<healphyTestSize<<" ";
            ofile<<healphy_mean<<" ";
            ofile<<healphy_mean_sd<<" ";
            ofile<<healphy_mean_train<<" ";
            ofile<<cancerTestSize<<" ";
            ofile<<cancer_mean<<" ";
            ofile<<cancer_mean_sd<<" ";
            ofile<<cancer_mean_train<<" ";
            ofile<<tc<<" ";
            ofile<<total_mean<<" ";
            ofile<<total_mean_sd<<" "<<endl;
            ofile.close();
        }
    static void MakeHeader(string filename)
        {
            ofstream ofile;
            ofile.open(filename.c_str(), iostream::out);
            ofile<<"CancerName"<<" ";
            ofile<<"N_Exp"<<" ";
            ofile<<"N_healphy"<<" ";
            ofile<<"Healphy_mis"<<" ";
            ofile<<"Healphy_mis_sd"<<" ";
            ofile<<"Healphy_mis_train"<<" ";
            ofile<<"N_cancer"<<" ";
            ofile<<"Cancer_mis"<<" ";
            ofile<<"Cancer_mis_sd"<<" ";
            ofile<<"Cancer_mis_train"<<" ";
            ofile<<"N_total"<<" ";
            ofile<<"Total_mis"<<" ";
            ofile<<"Total_mis_sd"<<" "<<endl;
            ofile.close();
        }
};
    
double GetProb(vector<vector<double> >& samples, vector<double>& means, vector<double>& sds,int idx, double subclassProb)
{
    double prob = 0;
    for (int j = 0; j < samples.size(); j++)
    {
        prob += log( gsl_ran_gaussian_pdf(samples[j][idx]-means[j],sds[j])  +smoothingEps);
    }
    prob += subclassProb;
    return prob;
}

void ProcessCancer(string cancerName,gsl_rng* randGenerator, string outFile)
{
    cout<<"Processing "<< cancerName<<" cancer"<<endl;
    // Loading data
    string filenameResp = cancerName + ".resp.csv";
    vector<bool> resp = loadResponse(filenameResp);
    cout<<"resp size = "<<resp.size()<<endl;

    string filenameSample = cancerName + ".sample.csv";
    vector<vector<double> > healphySample,
        cancerSample;
    loadSamples(healphySample, cancerSample, resp, filenameSample);
    cout<<"healphy sample size = "<<healphySample.size()<<endl;
    cout<<"cancer sample size = "<<cancerSample.size()<<endl;

    SumErrorsStruct sumErrs;
    int healphySize = healphySample[0].size(),
        cancerSize = cancerSample[0].size();
    int healphyTrainSize = healphySize*trainPart,
        cancerTrainSize = cancerSize*trainPart,
        healphyTestSize = healphySize - healphyTrainSize,
        cancerTestSize = cancerSize - cancerTrainSize;

    // Main loop
    for (int k = 0; k < experimentCount; k++)
    {
        cout<<"##################"<<" experiment index: "<<k<<endl;
        // Form train and test sets
        vector<int > healphyShuffle = get_sample(randGenerator, healphySize),
            cancerShuffle = get_sample(randGenerator, cancerSize);
        vector<int> healphyTrain(healphyShuffle.begin(),
                                 healphyShuffle.begin()+healphyTrainSize),
            healphyTest(healphyShuffle.begin()+healphyTrainSize,
                        healphyShuffle.end()),
            cancerTrain(cancerShuffle.begin(),
                        cancerShuffle.begin()+cancerTrainSize),
            cancerTest(cancerShuffle.begin()+cancerTrainSize,
                       cancerShuffle.end());
        cout<<"training model\n";
        TrainModel model(
            mean(healphySample,healphyTrain),
            sd(healphySample,healphyTrain),
            mean(cancerSample,cancerTrain),
            sd(cancerSample,cancerTrain)
            );
        cout<<"after training model\n";
        
        // Train complete at this point
        // Predicting
        time_t t = clock();
        int healphyMisLocal = 0;
        int cancerMisLocal = 0;
        double prob0 = 0,
            prob1 = 0,
            healphyClassProb = log(double(healphyTrainSize)/(healphyTrainSize+cancerTrainSize)+smoothingEps),
            cancerClassProb = log(double(cancerTrainSize)/(healphyTrainSize+cancerTrainSize)+smoothingEps);
        cout<<"healphy predicting"<<endl;
        for (int i = 0; i < healphyTestSize; i++)
        {
            prob0 = GetProb(healphySample,model.healphyMean, model.healphySd,healphyTest[i],healphyClassProb);
            prob1 = GetProb(healphySample,model.cancerMean, model.cancerSd,healphyTest[i],cancerClassProb);
            healphyMisLocal += prob0 < prob1;
            cout<<"prob1 - prob0 = "<< prob1-prob0<<endl;
        }
        sumErrs.healphyMis += healphyMisLocal;
        sumErrs.healphyMisSquared += healphyMisLocal * healphyMisLocal;
        cout<<"healphy predicting time = "<<double(clock() - t)/CLOCKS_PER_SEC<<endl;
        cout<<"sumErrs = "<<healphyMisLocal<<" out of "<<healphyTestSize<<endl;

        t = clock();
        cancerMisLocal = 0;
        cout<<"cancer predicting"<<endl;
        for (int i = 0; i < cancerTestSize; i++)
        {
            prob0 = GetProb(cancerSample,model.healphyMean, model.healphySd,cancerTest[i],healphyClassProb);
            prob1 = GetProb(cancerSample,model.cancerMean, model.cancerSd,cancerTest[i],cancerClassProb);
            cancerMisLocal += prob1 < prob0;
            cout<<"prob0 - prob1 = "<< prob0-prob1<<endl;
        }
        sumErrs.cancerMis += cancerMisLocal;
        sumErrs.cancerMisSquared += cancerMisLocal * cancerMisLocal;
        cout<<"cancer predicting time = "<<double(clock() - t)/CLOCKS_PER_SEC<<endl;
        cout<<"sumErrs = "<<cancerMisLocal<<" out of "<<cancerTestSize<<endl;
        sumErrs.totalMisSquared += (cancerMisLocal + healphyMisLocal)*(cancerMisLocal + healphyMisLocal);
        
        cout<<"healphy train predicting"<<endl;
        healphyMisLocal = 0;
        for (int i = 0; i < healphyTrainSize; i++)
        {
            prob0 = GetProb(healphySample,model.healphyMean, model.healphySd,healphyTrain[i],healphyClassProb);
            prob1 = GetProb(healphySample,model.cancerMean, model.cancerSd,healphyTrain[i],cancerClassProb);
            healphyMisLocal += prob0 < prob1;
        }
        sumErrs.healphyMisTrain += healphyMisLocal;
        cout<<"sumErrs = "<<healphyMisLocal<<" out of "<<healphyTestSize<<endl;

        cout<<"cancer train predicting"<<endl;
        cancerMisLocal = 0;
        for (int i = 0; i < cancerTrainSize; i++)
        {
            prob0 = GetProb(cancerSample,model.healphyMean, model.healphySd,cancerTrain[i],healphyClassProb);
            prob1 = GetProb(cancerSample,model.cancerMean, model.cancerSd,cancerTrain[i],cancerClassProb);
            cancerMisLocal += prob1 < prob0;
        }
        sumErrs.cancerMisTrain += cancerMisLocal;

        cout<<"sumErrs = "<<cancerMisLocal<<" out of "<<cancerTestSize<<endl;
    }
    
    cout<<"healphy errors:  "<<sumErrs.healphyMis<< " out of "<<healphyTestSize*experimentCount<<". "<<double(sumErrs.healphyMis)/(healphyTestSize*experimentCount)<<endl;
    cout<<"cancer errors:  "<<sumErrs.cancerMis<< " out of "<<cancerTestSize*experimentCount<<". "<<double(sumErrs.cancerMis)/(cancerTestSize*experimentCount)<<endl;

    // Calculating result statistics and saving it into ResultStatistics structure
    ResultStatistics resStat;
    
    resStat.healphy_mean = double(sumErrs.healphyMis)/(healphyTestSize*experimentCount);
    resStat.healphy_mean_train = double(sumErrs.healphyMisTrain)/(healphyTrainSize*experimentCount);
    resStat.healphy_mean_sd = sqrt(
        double(sumErrs.healphyMisSquared)/(healphyTestSize*
                                           healphyTestSize*
                                           experimentCount) -
        resStat.healphy_mean*resStat.healphy_mean);
    resStat.cancer_mean = double(sumErrs.cancerMis)/(cancerTestSize*experimentCount);
    resStat.cancer_mean_train = double(sumErrs.cancerMisTrain)/(cancerTrainSize*experimentCount);
    resStat.cancer_mean_sd = sqrt(
        double(sumErrs.cancerMisSquared)/(cancerTestSize*
                                          cancerTestSize*
                                          experimentCount) -
        resStat.cancer_mean*resStat.cancer_mean);
    resStat.tc= cancerTestSize + healphyTestSize;
    resStat.total_mean = double(sumErrs.cancerMis+sumErrs.healphyMis)/(resStat.tc*experimentCount);
    resStat.total_mean_sd = sqrt(
        double(sumErrs.totalMisSquared)/(resStat.tc*resStat.tc*
                                         experimentCount) -
        resStat.total_mean*resStat.total_mean);
    resStat.cancerName = cancerName;
    resStat.experimentCount = experimentCount;
    resStat.healphyTestSize = healphyTestSize;
    resStat.cancerTestSize = cancerTestSize;
    resStat.Export(outFile);
}

int main()
{
    gsl_rng* randGenerator= gsl_rng_alloc(gsl_rng_taus);
//    gsl_rng_set(randGenerator, time(NULL));
    gsl_rng_set(randGenerator, 0);
    
    string outFileSuffix("test_train_errs.txt");
    ResultStatistics::MakeHeader(outFileSuffix);
    
    vector<string> cancers;
    // cancers.push_back("BLCA");
    cancers.push_back("READ");
    // cancers.push_back("KIRP");
    // cancers.push_back("LIHC");
    // cancers.push_back("PRAD");
    // cancers.push_back("LUSC");
    // cancers.push_back("COAD");
    // cancers.push_back("LUAD");
    // cancers.push_back("HNSC");
    // cancers.push_back("THCA");
    // cancers.push_back("UCEC");
    // cancers.push_back("KIRC");
    // cancers.push_back("BRCA");
    for (int i = 0; i < cancers.size(); i++)
    {
//        ProcessCancer(cancers[i], randGenerator,cancers[i]+outFileSuffix);
        ProcessCancer(cancers[i], randGenerator, outFileSuffix);
    }
    cout<<"after experiments\n";
    
    gsl_rng_free(randGenerator);
    return 0;
}
