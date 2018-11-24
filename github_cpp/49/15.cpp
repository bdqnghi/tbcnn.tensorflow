#include "stdafx.h"

#include "LinearRegression.h"
#include "gstd_matlab/src/MatlabMgr.h"
#include "gstd/src/Linalg.h"
#include "gstd/src/Stat.h"
#include "gstd/src/Timer.h"
#include "DpDoublesGenerators.h"
#include "RegressionGenerators.h"
#include "Data/src/Converters.h"
#include "Converters.h"

using namespace msii810161816::gstd::Linalg;

namespace msii810161816
{
	namespace ml
	{
		LinearRegression::LinearRegression() 
		{
			if (!mgr.instIsOpen())
				mgr.instOpen();
			pushedCols = 0;
			pushedRows = 0;
		}

		LinearRegression::~LinearRegression() {}

		void LinearRegression::initparameter() {} //not used
		
		void LinearRegression::fit()
		{                    
			std::vector<double> inMatrix;
			std::vector<double> outMatrix;
			int d = 0;
			for (int i = 0; i != maxDataPoint; i++)
			{
				gstd::trial<DpRegression> point = client.get(false)->get(i);
				gstd::check(point.success, "cannot find data points");
				if (i == 0)
					d = point.result.input.size();
				inMatrix.insert(inMatrix.end(), point.result.input.begin(), point.result.input.end());
				outMatrix.push_back(point.result.output);
			}

			gstd::check(maxDataPoint >= d, "cannot run unregularized linear model on undercomplete data!");

			if (d == 0)
			{
				gstd::vector::empty(parameter);
			}
			else
			{
                            	mgr.create(maxDataPoint, d, inMatrix, "X");
				mgr.create(maxDataPoint, 1, outMatrix, "Y");                                
				mgr.exec("res = X\\Y;");                                
				std::tuple<int, int, std::vector<double> > res = mgr.get("res");
				gstd::check(std::get<0>(res) == d, "incorrect output dimension");
				gstd::check(std::get<1>(res) == 1, "incorrect output dimension");
				parameter = std::get<2>(res);
			}			

			if (safe)
			{
                std::vector<double> pred = mmult(maxDataPoint, d, 1, inMatrix, parameter);
				std::vector<double> errorVector = msub(outMatrix, pred);
				std::vector<double> residual = mmult(1, maxDataPoint, d, errorVector, inMatrix);
				gstd::check(mequals(residual, std::vector<double>(d, 0), 1e-8, false), "gradient check failed");
			}

			if (doc)
			{
				gstd::Printer::c("Target model is (snippet): ");
				gstd::Printer::vc(gstd::vector::sub(target, 0, 100, true));
				gstd::Printer::c("parameter is (snippet): ");
				gstd::Printer::vc(gstd::vector::sub(parameter, 0, 100, true));
			}
		}

		void LinearRegression::fitWithOptions()
		{
			std::vector<double> inMatrix;
			std::vector<double> outMatrix;
			int d = 0;
			for (int i = 0; i != maxDataPoint; i++)
			{
				gstd::trial<DpRegression> point = client.get(false)->get(i);
				gstd::check(point.success, "cannot find data points");
				if (i == 0)
					d = point.result.input.size();
				inMatrix.insert(inMatrix.end(), point.result.input.begin(), point.result.input.end());
				outMatrix.push_back(point.result.output);
			}

			gstd::check(maxDataPoint >= d, "cannot run unregularized linear model on undercomplete data!");

			if (d == 0)
			{
				gstd::vector::empty(parameter);
				gstd::vector::empty(pvalues);
			}
			else
			{
				mgr.create(maxDataPoint, d, inMatrix, "X");
				mgr.create(maxDataPoint, 1, outMatrix, "Y");

				mgr.exec("res = LinearModel.fit(X, Y, 'intercept', false);");
				mgr.exec("res = table2array(res.Coefficients);");

				int ressize1, ressize2;
				std::vector<double> res;

				std::tie(ressize1, ressize2, res) = mgr.get("res");

				gstd::check(ressize1 == d, "incorrect output dimension");
				gstd::check(ressize2 == 4, "incorrect output dimension");

				parameter = gstd::Linalg::submatrix(d, 4, res, 0, 0, -1, 1);
				pvalues = gstd::Linalg::submatrix(d, 4, res, 0, 3, -1, 1);
			}

			if (safe)
			{
				std::vector<double> pred = mmult(maxDataPoint, d, 1, inMatrix, parameter);
				std::vector<double> errorVector = msub(outMatrix, pred);
				std::vector<double> residual = mmult(1, maxDataPoint, d, errorVector, inMatrix);
				gstd::check(mequals(residual, std::vector<double>(d, 0), 1e-8, false), "gradient check failed");
			}

			if (doc)
			{
				gstd::Printer::c("Target model is (snippet): ");
				gstd::Printer::vc(gstd::vector::sub(target, 0, 100, true));
				gstd::Printer::c("parameter is (snippet): ");
				gstd::Printer::vc(gstd::vector::sub(parameter, 0, 100, true));
			}
		}

		void LinearRegression::push()
		{
			std::vector<double> inMatrix;
			std::vector<double> outMatrix;
			int d = 0;
			for (int i = 0; i != maxDataPoint; i++)
			{
				gstd::trial<DpRegression> point = client.get(false)->get(i);
				gstd::check(point.success, "cannot find data points");
				if (i == 0)
					d = point.result.input.size();
				inMatrix.insert(inMatrix.end(), point.result.input.begin(), point.result.input.end());
				outMatrix.push_back(point.result.output);
			}

			if (d > 0)
			{
				mgr.create(maxDataPoint, d, inMatrix, "X");
				mgr.create(maxDataPoint, 1, outMatrix, "Y");
			}

			pushedRows = maxDataPoint;
			pushedCols = d;
		}

		void LinearRegression::fitSubset(std::vector<int> rowSubSet, std::vector<int> colSubSet)
		{
			int numRows = rowSubSet.size();
			int numCols = colSubSet.size();
						
			if (numCols == 0)
			{
				gstd::vector::empty(parameter);
				return;
			}				

			gstd::check(numRows >= numCols, "cannot fit undercomplete l2 model");
			for (int i = 0; i < numRows; i++)
				gstd::check(rowSubSet[i] < pushedRows, "cannot run on rows that were not pushed");
			for (int i = 0; i < numCols; i++)
				gstd::check(colSubSet[i] < pushedCols, "cannot run on cols that were not pushed");

			mgr.create(1, numRows, gstd::vector::itod(rowSubSet), "rowInds");
			mgr.create(1, numCols, gstd::vector::itod(colSubSet), "colInds");
                        mgr.exec("rowInds = rowInds + 1;colInds = colInds + 1;subX = X(rowInds,colInds);subY = Y(rowInds);res = subX\\subY;");
			std::tuple<int, int, std::vector<double> > res = mgr.get("res");

			gstd::check(std::get<0>(res) == numCols, "incorrect output dimension");
			gstd::check(std::get<1>(res) == 1, "incorrect output dimension");

			parameter = std::get<2>(res);

			if (safe)
			{
				std::vector<double> fullInMatrix, fullOutMatrix, inMatrix, outMatrix;
				int inRows, inCols, outRows, outCols;
				std::tie(inRows, inCols, fullInMatrix) = mgr.get("X");
				std::tie(outRows, outCols, fullOutMatrix) = mgr.get("Y");
				gstd::check(inRows == pushedRows, "safety check for fitsubset failed");
				gstd::check(outRows == pushedRows, "safety check for fitsubset failed");
				gstd::check(inCols == pushedCols, "safety check for fitsubset failed");
				gstd::check(outCols == 1, "safety check for fitsubset failed");
				for (int i = 0; i < numRows; i++)
				{
					for (int j = 0; j < numCols; j++)
					{
						inMatrix.push_back(fullInMatrix[rowSubSet[i] * pushedCols + colSubSet[j]]);
					}
					outMatrix.push_back(fullOutMatrix[rowSubSet[i]]);
				}
				std::vector<double> pred = mmult(numRows, numCols, 1, inMatrix, parameter);
				std::vector<double> errorVector = msub(outMatrix, pred);
				std::vector<double> residual = mmult(1, numRows, numCols, errorVector, inMatrix);
				gstd::check(mequals(residual, std::vector<double>(numCols, 0), 1e-8, false), "gradient check failed");
			}

			if (doc)
			{
				gstd::Printer::c("Target model is (snippet): ");
				gstd::Printer::vc(gstd::vector::sub(target, 0, 100, true));
				gstd::Printer::c("parameter is (snippet): ");
				gstd::Printer::vc(gstd::vector::sub(parameter, 0, 100, true));
			}

		}

		double LinearRegression::apply(data::DpDoubles input)
		{
			gstd::check(parameter.size() == input.content.size(), "input of incorrect size");
			double res = 0;
			int size = parameter.size();
			for (int i = 0; i < size; i++)
				res += input.content[i] * parameter[i];
			return res;
		}

		std::pair<double, double> LinearRegression::test(DpRegression input)
		{
			data::DpDoubles point;
			point.content = input.input;
			double res = apply(point);
			double diff = res - input.output;
			double error = 0.5*diff*diff;
			return std::pair<double, double>(res, error);
		}

		//Base package
		void LinearRegression::setInputs()
		{
			//make choices
			int d = 20;
			int N = 10000;
			double noisestd = 1;
			target.resize(d);
			//generate data
			GaussianGenerator<data::DataHeader>* gen = new GaussianGenerator<data::DataHeader>;
			gen->setInputsBlockwise(4, 5, 1, 0.5, 0);
			//create model
			LinearLassoGenerator<data::DataHeader>* las = new LinearLassoGenerator<data::DataHeader>;
			for (int i = 0; i < d; i++)
			{
				double draw = gstd::stat::randnorm(4);
				target[i] = draw;
				las->targetModel[i] = draw;
			}
			las->noiseStd = noisestd;
			las->storedata = true;
			las->inServer.set(gen, true);
			//finish
			client.set(las, true);
			maxDataPoint = N;
		}
		bool LinearRegression::test()
		{
			LinearRegression obj;
			obj.setInputs();
			obj.safe = true;
			try
			{
				obj.fit();
			}
			catch (std::exception e)
			{
				obj.reportFailure("safety checks for 'fit'");
				return false;
			}		
			if (!mequals(obj.parameter, obj.target, 0.1, false))
			{
				obj.reportFailure("'fit'");
				return false;
			}
			try
			{
				obj.fitWithOptions();
			}
			catch (std::exception e)
			{
				obj.reportFailure("safety checks for 'fit'");
				return false;
			}
			if (!mequals(obj.parameter, obj.target, 0.1, false) || obj.pvalues.size() != obj.parameter.size())
			{
				obj.reportFailure("'fitWithOptions'");
				return false;
			}
			int d = obj.parameter.size();
			for (int i = 0; i < d; i++)
			{
				if (obj.pvalues[i] < 0 || obj.pvalues[i] >= 1)
				{
					obj.reportFailure("'fitWithOptions'");
					return false;
				}
			}
			std::vector<int> rows = { 103, 42, 52, 36, 45 };
			std::vector<int> cols = { 3, 7 };
			try
			{
				gstd::Printer::c("expecting error message ...");
				obj.fitSubset(rows, cols);
				obj.reportFailure("prelim to 'fitSubset'");
				return false;
			}
			catch (std::exception e){}
			obj.push();
			try
			{
				gstd::Printer::c("expecting error message ...");
				obj.fitSubset(rows, { 40 });
				obj.reportFailure("prelim to 'fitSubset'");
				return false;
			}
			catch (std::exception e){}
			try
			{
				obj.fitSubset(rows, cols);
			}
			catch (std::exception e)
			{
				obj.reportFailure("safety checks in 'fitSubset'");
				return false;
			}
			std::vector<double> res = obj.parameter;
			data::IndexMapper<DpRegression, data::DataHeader> mapper;
			mapper.indexmap = rows;
			DpRegressionComponentMapper<data::DataHeader> cMapper;
			cMapper.componentMap = cols;
			gstd::Pointer<data::Server<DpRegression, data::DataHeader> > point;
			point.set(obj.client.get(true), true);
			obj.client.set(&cMapper, false);
			mapper.inServer.set(point.get(false),false);
			cMapper.inServer.set(&mapper,false);
			obj.maxDataPoint = rows.size();
			obj.fit();
			std::vector<double> target = obj.parameter;
			if (!gstd::Linalg::mequals(res, target, 1e-6, false))
			{
				obj.reportFailure("'fitSubset'");
				return false;
			}
			obj.parameter = { 1, 2, 3, 4 };
			data::DpDoubles p1;
			p1.content = { 2, 3, 4, 5 };
			DpRegression p2;
			p2.input = p1.content;
			p2.output = 43;
			double applyres = obj.apply(p1);
			std::pair<double, double> testres = obj.test(p2);
			if (!gstd::Double::equals(applyres, 40) || !gstd::Double::equals(testres.first, 40) || !gstd::Double::equals(testres.second, 4.5))
			{
				obj.reportFailure("'apply/test'");
				return false;
			}
			return true;
		}
		gstd::TypeName LinearRegression::getTypeName()
		{
			return gstd::TypeNameGetter<LinearRegression>::get();
		}
		std::string LinearRegression::toString()
		{
			std::stringstream res;
			res << "This is a ml::LinearRegression" << std::endl;
			res << ModelTyped<DpRegression, data::DataHeader>::toString();
			return res.str();
		}
	}
}

