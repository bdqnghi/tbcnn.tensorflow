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
	iClassNum = -1;
	iFeatureNum = -1;
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

bool LogisticRegression::LoadAllSamples (const char * sFileName, vector<Sample> & SampleVec)
{
	ifstream in (sFileName);
	if (!in)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	SampleVec.clear();

	string sLine;
	while (getline (in, sLine))
	{
		Sample theSample;
		if (ReadSampleFrmLine (sLine, theSample))
			SampleVec.push_back (theSample);
	}

	return true;
}

bool LogisticRegression::ScaleAllSampleValTxt (const char * sFileIn, int iFeatureNum, const char * sFileOut)
{
	ifstream in (sFileIn);
	ofstream out (sFileOut);
	if (!in || !out)
	{
		cerr << "Can not open the file" << endl;
		return false;
	}

	// load all of the samples
	vector<Sample> SampleVec;
	if (!LoadAllSamples (sFileIn, SampleVec))
		return false;

	// get the max value of each feature
	vector<double> FeaMaxValVec (iFeatureNum, 0.0); 
	vector<Sample>::iterator p = SampleVec.begin();
	while (p != SampleVec.end())
	{
		vector<FeaValNode>::iterator pFea = p->FeaValNodeVec.begin();
		while (pFea != p->FeaValNodeVec.end())
		{
			if (pFea->iFeatureId < iFeatureNum 
				&& pFea->dValue > FeaMaxValVec[pFea->iFeatureId])
				FeaMaxValVec[pFea->iFeatureId] = pFea->dValue;
			pFea++;
		}
		p++;
	}

	// smoothing FeaMaxValVec to avoid zero value
	vector<double>::iterator pFeaMax = FeaMaxValVec.begin();
	while (pFeaMax != FeaMaxValVec.end())
	{
		*pFeaMax += SMOOTHFATOR;
		pFeaMax++;
	}

	// scale the samples
	p = SampleVec.begin();
	while (p != SampleVec.end())
	{
		vector<FeaValNode>::iterator pFea = p->FeaValNodeVec.begin();
		while (pFea != p->FeaValNodeVec.end())
		{
			if (pFea->iFeatureId < iFeatureNum)
				pFea->dValue /= FeaMaxValVec[pFea->iFeatureId];
			pFea++;
		}
		p++;
	}

	// dump the result
	p = SampleVec.begin();
	while (p != SampleVec.end())
	{
		out << p->iClass << " ";
		vector<FeaValNode>::iterator pFea = p->FeaValNodeVec.begin();
		while (pFea != p->FeaValNodeVec.end())
		{
			out << pFea->iFeatureId << ":" << pFea->dValue << " ";
			pFea++;
		}
		out << "\n";
		p++;
	}


	return true;
}

bool LogisticRegression::InitThetaMatrix (int iClassNum, int iFeatureNum)
{
	if (iClassNum <= 0 || iFeatureNum <= 0)
		return false;

	this->iClassNum = iClassNum;
	this->iFeatureNum = iFeatureNum;

	// There are K classes to classify. We only need to tell K-1 classes. 
	// The rest belong to the Kth class.
	ThetaMatrix.resize (iClassNum - 1);
	for (int i=0; i<iClassNum-1; i++)
	{
		ThetaMatrix[i].resize (iFeatureNum, 0.0);
	}

	return true;
}

// it returns the value of f(x) = exp (W*X) for iClassIndex < K, otherwise 1.0 for iClassIndex == K
double LogisticRegression::CalcFuncOutByFeaVec(vector<FeaValNode> & FeaValNodeVec, int iClassIndex)
{
	if (iClassIndex >= iClassNum || iClassIndex <0)		// wrong situation
		return 0.0;

	if (iClassIndex == (iClassNum-1) )	// the default class (here is the class with max index)
		return 1.0;

	double dX = 0.0;
	vector<FeaValNode>::iterator p = FeaValNodeVec.begin();
	while (p != FeaValNodeVec.end())
	{
		if (p->iFeatureId < (int)ThetaMatrix.at(iClassIndex).size())	// all input is evil
			dX += ThetaMatrix[iClassIndex][p->iFeatureId] * p->dValue;			
		p++;
	}

	double dY = exp (dX);
	return dY;
}

// the class probability is calculated by : 
// f(x) = exp (W*X) / {1.0 + sum_exp (W*X)} as long as iClassIndex < K
// f(x) = 1.0 / {1.0 + sum_exp (W*X)} as long as iClassIndex == K
int LogisticRegression::CalcFuncOutByFeaVecForAllClass (vector<FeaValNode> & FeaValNodeVec, vector<double> & ClassProbVec)
{
	ClassProbVec.clear();
	ClassProbVec.resize (iClassNum, 0.0);

	double dSum = 1.0;
	for (int i=0; i<iClassNum; i++)
	{
		ClassProbVec.at(i) = CalcFuncOutByFeaVec (FeaValNodeVec, i);
		dSum += ClassProbVec.at(i);
	}

	double dMaxProb = 0.0;
	int iClassMaxProb = -1;
	for (int i=0; i<iClassNum; i++)
	{
		ClassProbVec.at(i) /= dSum;
		if (ClassProbVec.at(i) > dMaxProb)
		{
			iClassMaxProb = i;
			dMaxProb = ClassProbVec.at(i);
		}
	}

	return iClassMaxProb;
}

// the update formula is : theta_new = theta_old - dLearningRate * (dY - iClass) * dXi
double LogisticRegression::UpdateThetaMatrix (Sample & theSample, vector<double> & ClassProbVec, double dLearningRate)
{
	double dCost = 0.0;
	for (int i=0; i<iClassNum-1; i++)
	{
		if (i == theSample.iClass)
		{
			vector<FeaValNode>::iterator p = theSample.FeaValNodeVec.begin();
			while (p != theSample.FeaValNodeVec.end())
			{
				if (p->iFeatureId < (int)ThetaMatrix[i].size())
				{
					double dGradient = (ClassProbVec[i] - 1.0) * p->dValue;
					double dDelta = dGradient * dLearningRate;
					ThetaMatrix[i][p->iFeatureId] -= dDelta;
				}
				p++;
			}
			// cost = log(dY) when the sample class is the predicted class, otherwise cost = log(1.0 - dY)
			dCost -= log (ClassProbVec[i]);
		}
		else
		{
			vector<FeaValNode>::iterator p = theSample.FeaValNodeVec.begin();
			while (p != theSample.FeaValNodeVec.end())
			{
				if (p->iFeatureId < (int)ThetaMatrix[i].size())
				{
					double dGradient = ClassProbVec[i] * p->dValue;
					double dDelta = dGradient * dLearningRate;
					ThetaMatrix[i][p->iFeatureId] -= dDelta;
				}
				p++;
			}
			// cost = log(dY) when the sample class is the predicted class, otherwise cost = log(1.0 - dY)
			dCost -= log (1.0 - ClassProbVec[i]);
		}
	}

	return dCost;
}


// the sample format: classid feature1_value feature2_value...
bool LogisticRegression::TrainSGDOnSampleFile (
			const char * sFileName, int iClassNum, int iFeatureNum,		// about the samples
			double dLearningRate = 0.05,								// about the learning
			int iMaxLoop = 1, double dMinImproveRatio = 0.01			// about the stop criteria
			)
{
	ifstream in (sFileName);
	if (!in)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	if (!InitThetaMatrix (iClassNum, iFeatureNum))
		return false;

	double dCost = 0.0;
	double dPreCost = 100.0;
	for (int iLoop = 0; iLoop < iMaxLoop; iLoop++)
	{
		int iSampleNum = 0;
		int iErrNum = 0;
		string sLine;
		while (getline (in, sLine))
		{
			Sample theSample;
			if (ReadSampleFrmLine (sLine, theSample))
			{
				vector<double> ClassProbVec;
				int iPredClassIndex = CalcFuncOutByFeaVecForAllClass (theSample.FeaValNodeVec, ClassProbVec);
				if (iPredClassIndex != theSample.iClass)
					iErrNum++;

				dCost += UpdateThetaMatrix (theSample, ClassProbVec, dLearningRate); 
				iSampleNum++;
			}
		}

		dCost /= iSampleNum;
		double dTmpRatio = (dPreCost - dCost) / dPreCost;
		double dTmpErrRate = (double)iErrNum / iSampleNum;

		// show info on screen
		cout << "In loop " << iLoop << ": current cost (" << dCost << ") previous cost (" << dPreCost << ") ratio (" << dTmpRatio << ") "<< endl;
		cout << "And Error rate : " << dTmpErrRate << endl;

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

bool LogisticRegression::TrainSGDOnSampleFileEx (
			const char * sFileName, int iClassNum, int iFeatureNum,		// about the samples
			double dLearningRate = 0.05,								// about the learning
			int iMaxLoop = 1, double dMinImproveRatio = 0.01			// about the stop criteria
			)
{
	ifstream in (sFileName);
	if (!in)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	if (!InitThetaMatrix (iClassNum, iFeatureNum))
		return false;

	double dCost = 0.0;
	double dPreCost = 100.0;
	for (int iLoop = 0; iLoop < iMaxLoop; iLoop++)
	{
		int iSampleNum = 0;
		int iErrNum = 0;
		string sLine;
		while (getline (in, sLine))
		{
			Sample theSample;
			if (ReadSampleFrmLine (sLine, theSample))
			{
				vector<double> ClassProbVec;
				int iPredClassIndex = CalcFuncOutByFeaVecForAllClass (theSample.FeaValNodeVec, ClassProbVec);
				if (iPredClassIndex != theSample.iClass)
					iErrNum++;

				dCost += UpdateThetaMatrix (theSample, ClassProbVec, dLearningRate); 
				iSampleNum++;
			}
		}

		dCost /= iSampleNum;
		double dTmpRatio = (dPreCost - dCost) / dPreCost;
		double dTmpErrRate = (double)iErrNum / iSampleNum;

		// show info on screen
		cout << "In loop " << iLoop << ": current cost (" << dCost << ") previous cost (" << dPreCost << ") ratio (" << dTmpRatio << ") "<< endl;
		cout << "And Error rate : " << dTmpErrRate << endl;

		if (dTmpRatio < dMinImproveRatio)
			break;
		else
		{
			dLearningRate /= (iLoop + 2.0);
			dPreCost = dCost;
			dCost = 0.0;
			//reset the current reading position of file
			in.clear();
			in.seekg (0, ios::beg);
		}
	}

	return true;
}

// the sample format: classid feature1_value feature2_value...
bool LogisticRegression::TrainSGDOnSampleFileEx2 (
			const char * sFileName, int iClassNum, int iFeatureNum,		// about the samples
			double dLearningRate = 0.05,								// about the learning
			int iMaxLoop = 1, double dMinImproveRatio = 0.01			// about the stop criteria
			)
{
	ifstream in (sFileName);
	if (!in)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	if (!InitThetaMatrix (iClassNum, iFeatureNum))
		return false;

	vector<Sample> SampleVec;
	if (!LoadAllSamples (sFileName, SampleVec))
		return false;

	double dCost = 0.0;
	double dPreCost = 100.0;
	for (int iLoop = 0; iLoop < iMaxLoop; iLoop++)
	{
		srand((unsigned)time(NULL));
		int iErrNum = 0;
		int iSampleNum = (int)SampleVec.size();
		for (int i=0; i<iSampleNum; i++)
		{
			double dRandomFloat = (double)rand() / RAND_MAX;
			int iSampleIndex = (int)(dRandomFloat * iSampleNum);

			vector<double> ClassProbVec;
			int iPredClassIndex = CalcFuncOutByFeaVecForAllClass (SampleVec[iSampleIndex].FeaValNodeVec, ClassProbVec);
			if (iPredClassIndex != SampleVec[iSampleIndex].iClass)
				iErrNum++;

			dCost += UpdateThetaMatrix (SampleVec[iSampleIndex], ClassProbVec, dLearningRate); 
		}

		dCost /= iSampleNum;
		double dTmpRatio = (dPreCost - dCost) / dPreCost;
		double dTmpErrRate = (double)iErrNum / iSampleNum;

		// show info on screen
		cout << "In loop " << iLoop << ": current cost (" << dCost << ") previous cost (" << dPreCost << ") ratio (" << dTmpRatio << ") "<< endl;
		cout << "And Error rate : " << dTmpErrRate << endl;

		/*if (dTmpRatio < dMinImproveRatio)
			break;
		else*/
		if (dCost < 0.001)
			break;
		{
			dPreCost = dCost;
			dCost = 0.0;
		}
	}

	return true;
}

bool LogisticRegression::SaveLRModelTxt (const char *sFileName)
{
	if (ThetaMatrix.empty())
	{
		cerr << "The Theta matrix is empty" << endl;
		return false;
	}

	ofstream out (sFileName);
	if (!out)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	out << iClassNum << " " << iFeatureNum << endl;
	for (int i=0; i<iClassNum-1; i++)
	{
		copy (ThetaMatrix[i].begin(), ThetaMatrix[i].end(), ostream_iterator<double>(out, " "));
		out << "\n";
	}

	return true;
}

bool LogisticRegression::LoadLRModelTxt (const char *sFileName)
{
	ifstream in (sFileName);
	if (!in)
	{
		cerr << "Can not open the file of " << sFileName << endl;
		return false;
	}

	ThetaMatrix.clear();

	in >> iClassNum >> iFeatureNum;
	if (!InitThetaMatrix (iClassNum, iFeatureNum))
		return false;

	for (int i=0; i<iClassNum-1; i++)
		for (int j=0; j<iFeatureNum; j++)
			in >> ThetaMatrix[i][j];

	return true;
}

int LogisticRegression::PredictOneSample (Sample & theSample)
{
	vector<double> ClassProbVec;
	CalcFuncOutByFeaVecForAllClass (theSample.FeaValNodeVec, ClassProbVec);

	vector<double>::iterator p = max_element (ClassProbVec.begin(), ClassProbVec.end());
	int iClassIndex = (int)(p - ClassProbVec.begin());

	return iClassIndex;
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
	//TrainSGDOnSampleFile ("..\\Data\\SamplesMultClassesTrain.txt", 6, 25334, 0.01, 100, 0.05);
	//SaveLRModelTxt ("Model\\Mod_001_100_005.txt");*/
	/*LoadLRModelTxt ("Model\\Mod_001_100_005.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTest.txt", "Model\\Rslt_001_100_005.txt", "Model\\Log_001_100_005.txt");*/

	// ScaleAllSampleValTxt ("..\\Data\\SamplesMultClassesTrain.txt", 25334, "..\\Data\\SamplesMultClassesTrainScale.txt");
	// ScaleAllSampleValTxt ("..\\Data\\SamplesMultClassesTest.txt", 25334, "..\\Data\\SamplesMultClassesTestScale.txt");

	/*TrainSGDOnSampleFile ("..\\Data\\SamplesMultClassesTrainScale.txt", 6, 25334, 0.01, 200, 0.05);
	SaveLRModelTxt ("Model\\Mod_Scale_001_200_001.txt");
	LoadLRModelTxt ("Model\\Mod_Scale_001_200_001.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTestScale.txt", "Model\\Rslt_Scale_001_200_001.txt", "Model\\Log_Scale_001_200_001.txt");*/
	TrainSGDOnSampleFile ("..\\Data\\SamplesMultClassesTrainScale.txt", 6, 25334, 0.1, 200, 0.05);
	SaveLRModelTxt ("Model\\Mod_Scale_01_200_001.txt");
	LoadLRModelTxt ("Model\\Mod_Scale_01_200_001.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTestScale.txt", "Model\\Rslt_Scale_01_200_001.txt", "Model\\Log_Scale_01_200_001.txt");
	/*TrainSGDOnSampleFile ("..\\Data\\SamplesMultClassesTrainScale.txt", 6, 25334, 0.2, 200, 0.05);
	SaveLRModelTxt ("Model\\Mod_Scale_02_200_001.txt");
	LoadLRModelTxt ("Model\\Mod_Scale_02_200_001.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTestScale.txt", "Model\\Rslt_Scale_02_200_001.txt", "Model\\Log_Scale_02_200_001.txt");*/
	/*TrainSGDOnSampleFile ("..\\Data\\SamplesMultClassesTrainScale.txt", 6, 25334, 0.5, 200, 0.05);
	SaveLRModelTxt ("Model\\Mod_Scale_05_200_001.txt");
	LoadLRModelTxt ("Model\\Mod_Scale_05_200_001.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTestScale.txt", "Model\\Rslt_Scale_05_200_001.txt", "Model\\Log_Scale_05_200_001.txt");*/

	/*TrainSGDOnSampleFileEx ("..\\Data\\SamplesMultClassesTrainScale.txt", 6, 25334, 0.1, 200, 0.05);
	SaveLRModelTxt ("Model\\ModEx_Scale_01_200_001.txt");
	LoadLRModelTxt ("Model\\ModEx_Scale_01_200_001.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTestScale.txt", "Model\\RsltEx_Scale_01_200_001.txt", "Model\\LogEx_Scale_01_200_001.txt");*/
	/*TrainSGDOnSampleFileEx ("..\\Data\\SamplesMultClassesTrainScale.txt", 6, 25334, 0.01, 200, 0.05);
	SaveLRModelTxt ("Model\\ModEx_Scale_001_200_001.txt");
	LoadLRModelTxt ("Model\\ModEx_Scale_001_200_001.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTestScale.txt", "Model\\RsltEx_Scale_001_200_001.txt", "Model\\LogEx_Scale_001_200_001.txt");*/

	/*TrainSGDOnSampleFileEx2 ("..\\Data\\SamplesMultClassesTrainScale.txt", 6, 25334, 0.5, 200, 0.05);
	SaveLRModelTxt ("Model\\ModEx2_Scale_05_200_001.txt");
	LoadLRModelTxt ("Model\\ModEx2_Scale_05_200_001.txt");
	PredictOnSampleFile ("..\\Data\\SamplesMultClassesTestScale.txt", "Model\\RsltEx2_Scale_05_200_001.txt", "Model\\LogEx2_Scale_05_200_001.txt");*/
}

