#include "LogisticRegression.h"

FeaValNode::FeaValNode (void)
{
	iFeatureId = -1;
	dValue = 0.0;
}

FeaValNode::~FeaValNode (void)
{
}

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

// the input format is: iClassId featureid1:featurevalue1 featureid2:featurevalue2 ... 
bool LogisticRegression::ReadSampleFrmLine (string & sLine, Sample & theSample)
{
	istringstream isLine (sLine);
	if (!isLine)
		return false;

	// the class index
	isLine >> theSample.iClass;

	// the feature and its value
	string sItem;
	while (isLine >> sItem )
	{
		FeaValNode theNode;
		string::size_type iPos = sItem.find (':');
		theNode.iFeatureId = atoi (sItem.substr(0, iPos).c_str());
		theNode.dValue = atof (sItem.substr (iPos+1).c_str());
		theSample.FeaValNodeVec.push_back (theNode);
	}

	return true;
}

double LogisticRegression::Sigmoid(double x)
{
	double dTmpOne = exp (x);
	double dTmpTwo = dTmpOne + 1;
	return dTmpOne / dTmpTwo;
}

double LogisticRegression::CalcFuncOutByFeaVec(vector<FeaValNode> & FeaValNodeVec)
{
	double dX = 0.0;
	vector<FeaValNode>::iterator p = FeaValNodeVec.begin();
	while (p != FeaValNodeVec.end())
	{
		if (p->iFeatureId < (int)ThetaVec.size())	// all input is evil
			dX += ThetaVec[p->iFeatureId] * p->dValue;			
		p++;
	}
	double dY = Sigmoid (dX);
	return dY;
}

// the update formula is : theta_new = theta_old - dLearningRate * (dY - iClass) * dXi
void LogisticRegression::UpdateThetaVec(Sample & theSample, double dY, double dLearningRate)
{
	vector<FeaValNode>::iterator p = theSample.FeaValNodeVec.begin();
	while (p != theSample.FeaValNodeVec.end())
	{
		if (p->iFeatureId < (int)ThetaVec.size())
		{
			double dGradient = (dY - theSample.iClass) * p->dValue;
			double dDelta = dGradient * dLearningRate;
			ThetaVec[p->iFeatureId] -= dDelta;
		}
		p++;
	}
}

// the sample format: classid feature1_value feature2_value...
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
				double dY = CalcFuncOutByFeaVec (theSample.FeaValNodeVec);
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
	double dY = CalcFuncOutByFeaVec (theSample.FeaValNodeVec);
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
			vector<FeaValNode>::iterator p = theSample.FeaValNodeVec.begin();
			while (p != theSample.FeaValNodeVec.end())
			{
				out << p->dValue << " ";
				p++;
			}
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

void LogisticRegression::Test (void)
{
	/*TrainSGDOnSampleFile ("..\\Data\\australian_scale_train.txt", 15, 0.01, 100, 0.05);
	SaveLRModelTxt ("Model\\Mod_001_100_005_scale.txt");
	LoadLRModelTxt ("Model\\Mod_001_100_005_scale.txt");
	PredictOnSampleFile ("..\\Data\\australian_scale_test.txt", "Model\\Rslt_001_100_005_scale.txt", "Model\\Log_001_100_005_scale.txt");*/

	/*TrainSGDOnSampleFile ("..\\Data\\australian_train.txt", 15, 0.01, 100, 0.05);
	SaveLRModelTxt ("Model\\Mod_001_100_005.txt");*/
}

