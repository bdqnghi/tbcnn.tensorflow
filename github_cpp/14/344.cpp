#include "LogisticRegression.h"

Sample::Sample (void)
{
	iClass = -1;
}

Sample::~Sample (void)
{
}

LogisticRegression::LogisticRegression(void)
{
}

LogisticRegression::~LogisticRegression(void)
{
}

bool LogisticRegression::ReadSampleFrmLine (string & sLine, Sample & theSample)
{
	istringstream isLine (sLine);
	if (!isLine)
		return false;

	// the class index
	isLine >> theSample.iClass;
	// the feature index vector
	copy (istream_iterator<int>(isLine), istream_iterator<int>(), back_inserter(theSample.FeaIdVec));

	return true;
}

double LogisticRegression::Sigmoid(double x)
{
	double dTmpOne = exp (x);
	double dTmpTwo = dTmpOne + 1;
	return dTmpOne / dTmpTwo;
}

double LogisticRegression::CalcFuncOutByFeaVec(vector<int> & FeaIdVec)
{
	double dX = 0.0;
	vector<int>::iterator p = FeaIdVec.begin();
	while (p != FeaIdVec.end())
	{
		if (*p < (int)ThetaVec.size())	// all input is evil
			dX += ThetaVec[*p];			// actually it is ThetaVec[*p] * 1.0
		p++;
	}
	double dY = Sigmoid (dX);
	return dY;
}


// the update formula is : theta_new = theta_old - dLearningRate * (dY - iClass) * dXi
// in which iClass is 0-1, and dXi is 0-1
void LogisticRegression::UpdateThetaVec(Sample & theSample, double dY, double dLearningRate)
{
	double dGradient = dY - theSample.iClass;
	double dDelta = dGradient * dLearningRate;

	vector<int>::iterator p = theSample.FeaIdVec.begin();
	while (p != theSample.FeaIdVec.end())
	{
		if (*p < (int)ThetaVec.size())
		{
			ThetaVec[*p] -= dDelta;
		}
		p++;
	}
}

// the sample format: classid featureId1 featureId2...
bool LogisticRegression::TrainSGDOnSampleFile (
			const char * sFileName, int iMaxFeatureNum,			// about the samples
			double dLearningRate = 0.05,						// about the learning
			int iMaxLoop = 1, double dMinImproveRatio = 0.01	// about the stop criteria
			)
{
	ifstream in (sFileName);
	if (!in)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	ThetaVec.clear();
	ThetaVec.resize (iMaxFeatureNum, 0.0);

	double dCost = 0.0;
	double dPreCost = 1.0;
	for (int iLoop = 0; iLoop < iMaxLoop; iLoop++)
	{
		int iSampleNum = 0;
		string sLine;
		while (getline (in, sLine))
		{
			Sample theSample;
			if (ReadSampleFrmLine (sLine, theSample))
			{
				double dY = CalcFuncOutByFeaVec (theSample.FeaIdVec);
				UpdateThetaVec (theSample, dY, dLearningRate); 

				// the cost function is : cost = -( iClass * log (dY) + (1.0 - iClass) * log(1.0 - dY) )
				// that is: cost = log(dY) when iClass is 1, otherwise cost = log(1.0 - dY) when iClass is 0
				if (theSample.iClass > 0.0)
					dCost -= log (dY);
				else
					dCost -= log (1.0 - dY);

				iSampleNum++;
			}
		}

		dCost /= iSampleNum;
		double dTmpRatio = (dPreCost - dCost) / dPreCost;

		// show info on screen
		cout << "In loop " << iLoop << ": current cost (" << dCost << ") previous cost (" << dPreCost << ") ratio (" << dTmpRatio << ") "<< endl;

		if (dTmpRatio < dMinImproveRatio)
			break;
		else
		{
			dPreCost = dCost;
			dCost = 0.0;
			//reset the current reading position of file
			in.clear();
			in.seekg (0, ios::beg);
		}
	}

	return true;
}

bool LogisticRegression::SaveLRModelTxt(const char *sFileName)
{
	if (ThetaVec.empty())
	{
		cerr << "The Theta vector is empty" << endl;
		return false;
	}

	ofstream out (sFileName);
	if (!out)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	out << (int)ThetaVec.size() << "\n";
	copy (ThetaVec.begin(), ThetaVec.end(), ostream_iterator<double>(out, "\n"));

	return true;
}

bool LogisticRegression::LoadLRModelTxt (const char * sFileName)
{
	ifstream in (sFileName);
	if (!in)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	ThetaVec.clear();

	int iNum = 0;
	in >> iNum;

	ThetaVec.resize (iNum, 0.0);
	for (int i=0; i<iNum; i++)
	{
		in >> ThetaVec[i];
	}

	return true;
}

int LogisticRegression::PredictOneSample (Sample & theSample)
{
	double dY = CalcFuncOutByFeaVec (theSample.FeaIdVec);
	if (dY > 0.5)
		return 1;
	else
		return 0;
}

bool LogisticRegression::PredictOnSampleFile(const char *sFileIn, const char *sFileOut, const char *sFileLog)
{
	ifstream in (sFileIn);
	ofstream out (sFileOut);
	ofstream log (sFileLog);
	if (!in || !out || !log)
	{
		cerr << "Can not open the files " << endl;
		return false;
	}

	int iSampleNum = 0;
	int iCorrectNum = 0;
	string sLine;
	while (getline (in, sLine))
	{
		Sample theSample;
		if (ReadSampleFrmLine (sLine, theSample))
		{
			int iClass = PredictOneSample (theSample);

			if (iClass == theSample.iClass)
				iCorrectNum++;

			out << iClass << " ";
			copy (theSample.FeaIdVec.begin(), theSample.FeaIdVec.end(), ostream_iterator<int>(out, " "));
			out << endl;
		}
		else
			out << "bad input" << endl;

		iSampleNum++;
	}

	log << "The total number of sample is : " << iSampleNum << endl;
	log << "The correct prediction number is : " << iCorrectNum << endl;
	log << "Precision : " << (double)iCorrectNum / iSampleNum << endl;

	cout << "Precision : " << (double)iCorrectNum / iSampleNum << endl;

	return true;
}

void ToDeleteLater (const char * sFileIn, const char * sFileOut, double dThreshold)
{
	ifstream in (sFileIn);
	ofstream out (sFileOut);

	vector<double> ParaVec;
	copy (istream_iterator<double>(in), istream_iterator<double>(), back_inserter(ParaVec));

	double iNum = 0;
	vector<double>::iterator p = ParaVec.begin();
	while (p != ParaVec.end())
	{
		double dTmp = abs(*p);
		if (dTmp < dThreshold)
		{
			out << 0 << endl;
			iNum++;
		}
		else
			out << *p << endl;
		p++;
	}
	cout << iNum << endl;

}


void LogisticRegression::Test (void)
{
	/*TrainSGDOnSampleFile ("..\\Data\\SamplesTrain.txt", 10, 0.01, 100, 0.05);
	SaveLRModelTxt ("Model\\Mod_001_100_005.txt");*/
	/*LoadLRModelTxt ("Model\\Mod_001_100_005.txt");
	PredictOnSampleFile ("..\\Data\\SamplesTest.txt", "Model\\Rslt_001_100_005.txt", "Model\\Log_001_100_005.txt");*/

	/*ToDeleteLater ("Model\\Mod_ala_001_100_001.txt", "Model\\Mod_ala_001_100_001_ex.txt", 0.2);
	LoadLRModelTxt ("Model\\Mod_ala_001_100_001_ex.txt");
	PredictOnSampleFile ("..\\Data\\svm_ala_test.txt", "Model\\Rslt_ala_001_100_001_ex.txt", "Model\\Log_ala_001_100_001_ex.txt");*/
}
