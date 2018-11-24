#include "NaiveBayes.h"


NaiveBayes::NaiveBayes()
{}

NaiveBayes::NaiveBayes(int featureNum) : muPositive(featureNum, 0.0f), muNegative(featureNum, 0.0f),
	sigmaPositive(featureNum, 1.0f), sigmaNegative(featureNum, 1.0f)
{}

void NaiveBayes::init(std::vector<float>& msp, std::vector<float>& msn, std::vector<float>& ssp, std::vector<float>& ssn)
{
	muPositive = msp;
	muNegative = msn;
	sigmaPositive = ssp;
	sigmaNegative = ssn;
}

bool NaiveBayes::update(cv::Mat& mu, cv::Mat& sigma, int y, float ln)
{
	if (muPositive.empty())
	{
		int fn = mu.rows;
		muPositive = std::vector<float>(fn, 0.f);
		muNegative = std::vector<float>(fn, 0.f);
		sigmaPositive = std::vector<float>(fn, 1.f);
		sigmaNegative = std::vector<float>(fn, 1.f);
	}
	rollBackmuPos = muPositive;
	rollBacksigmaPos = sigmaPositive;
	rollBackmuNeg = muNegative;
	rollBacksigmaNeg = sigmaNegative;

	int featureNum = muPositive.size();
	if (y == NEGATIVE)
	{
		for (int i = 0; i < featureNum; ++i)
		{
			sigmaNegative[i] = (float)sqrt(ln*sigmaNegative[i]*sigmaNegative[i] + 
				(1.-ln)*sigma.at<float>(i,0)*sigma.at<float>(i,0)+ln*(1.-ln)*(muNegative[i]-mu.at<float>(i,0))*(muNegative[i]-mu.at<float>(i,0)));
			muNegative[i] = ln*muNegative[i] + (1.-ln)*mu.at<float>(i,0);
		}
	}
	else
	{
		for (int i = 0; i < featureNum; ++i)
		{
			sigmaPositive[i] = (float)sqrt(ln*sigmaPositive[i]*sigmaPositive[i] + 
				(1.-ln)*sigma.at<float>(i,0)*sigma.at<float>(i,0)+ln*(1.-ln)*(muPositive[i]-mu.at<float>(i,0))*(muPositive[i]-mu.at<float>(i,0)));
			muPositive[i] = ln*muPositive[i] + (1.-ln)*mu.at<float>(i,0);
		}
	}
	return true;
}

void NaiveBayes::rollBack()
{
	muPositive = rollBackmuPos;
	sigmaPositive = rollBacksigmaPos;
	muNegative = rollBackmuNeg;
	sigmaNegative = rollBacksigmaNeg;
}

int NaiveBayes::classify(Representation& x, float* score/* = nullptr*/)
{
	float sumRatio = 0.0f;
	cv::Mat feature = x._x.getMat();
	CV_Assert(feature.type() == CV_32F);

	int r = feature.rows, c = feature.cols;
	if (r == 1) feature = feature.t();

	int featureNum = muPositive.size();
	float pos, neg;
	for (int i = 0; i < featureNum; ++i)
	{
		pos = exp((feature.at<float>(i,0)-muPositive[i])*(feature.at<float>(i,0)-muPositive[i]) / 
			-(2.f*sigmaPositive[i]*sigmaPositive[i]+1e-30)) / (sigmaPositive[i]+1e-30);
		neg = exp((feature.at<float>(i,0)-muNegative[i])*(feature.at<float>(i,0)-muNegative[i]) / 
			-(2.f*sigmaNegative[i]*sigmaNegative[i]+1e-30)) / (sigmaNegative[i]+1e-30);
		sumRatio += log(pos+1e-30) - log(neg+1e-30);
	}
	if (score != nullptr) *score = sumRatio;
	if (sumRatio > 0.f) 
		return POSITIVE;
	return NEGATIVE;
}