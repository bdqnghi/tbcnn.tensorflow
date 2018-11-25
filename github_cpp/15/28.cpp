

#include "Preprocessor.hh"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "../Core/Configuration.hh"
#include "../Core/Log.hh"
#include "../Core/Parameter.hh"
#include "../Core/Types.hh"
#include "../Core/Utils.hh"
#include <Math/Random.hh>

#ifdef MODULE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#else
namespace cv {
	typedef u32 Mat; 
}
#endif

using namespace Features;


const Core::ParameterEnum Preprocessor::paramType_("type",
		"none, vector-subtraction, vector-division, matrix-multiplication",
		"none", "features.preprocessor");

Preprocessor::Preprocessor(const char* name) :
		name_(name),
		inputDimension_(0),
		outputDimension_(0),
		isInitialized_(false)
{}

void Preprocessor::initialize(u32 inputDimension) {
	inputDimension_ = inputDimension;
	isInitialized_ = true;
}

u32 Preprocessor::inputDimension() const {
	require(isInitialized_);
	return inputDimension_;
}

u32 Preprocessor::outputDimension() const {
	require(isInitialized_);
	return outputDimension_;
}

Preprocessor* Preprocessor::createPreprocessor(const char* name) {
	Preprocessor* p = 0;
	switch ( (Type) Core::Configuration::config(paramType_, name)) {
	case vectorSubtraction:
		Core::Log::os() << "Create vector-subtraction preprocessor as " << name << ".";
		p = new VectorSubtractionPreprocessor(name);
		break;
	case vectorDivision:
		Core::Log::os() << "Create vector-division preprocessor as " << name << ".";
		p = new VectorDivisionPreprocessor(name);
		break;
	case matrixMultiplication:
		Core::Log::os() << "Create matrix-multiplication preprocessor as " << name << ".";
		p = new MatrixMultiplicationPreprocessor(name);
		break;
	default:
		std::cerr << "Preprocessor::createPreprocessor: no type specified for preprocessor " << name << ". Abort." << std::endl;
		exit(1);
	}
	return p;
}


const Core::ParameterString VectorSubtractionPreprocessor::paramVectorFile_("vector", "", "features.preprocessor");

VectorSubtractionPreprocessor::VectorSubtractionPreprocessor(const char* name) :
		Precursor(name),
		vectorFile_(Core::Configuration::config(paramVectorFile_, name_))
{}

void VectorSubtractionPreprocessor::initialize(u32 inputDimension) {
	Precursor::initialize(inputDimension);
	require(!vectorFile_.empty());
	vector_.read(vectorFile_);
	require_eq(inputDimension_, vector_.nRows());
	outputDimension_ = inputDimension_;
}

void VectorSubtractionPreprocessor::work(const Math::Matrix<Float>& in, Math::Matrix<Float>& out) {
	require(isInitialized_);
	require_eq(inputDimension_, in.nRows());
	out.resize(outputDimension_, in.nColumns());
	out.copy(in);
	out.addToAllColumns(vector_, (Float)-1.0);
}


const Core::ParameterString VectorDivisionPreprocessor::paramVectorFile_("vector", "", "features.preprocessor");

VectorDivisionPreprocessor::VectorDivisionPreprocessor(const char* name) :
		Precursor(name),
		vectorFile_(Core::Configuration::config(paramVectorFile_, name_))
{}

void VectorDivisionPreprocessor::initialize(u32 inputDimension) {
	Precursor::initialize(inputDimension);
	require(!vectorFile_.empty());
	vector_.read(vectorFile_);
	require_eq(inputDimension_, vector_.nRows());
	outputDimension_ = inputDimension_;
}

void VectorDivisionPreprocessor::work(const Math::Matrix<Float>& in, Math::Matrix<Float>& out) {
	require(isInitialized_);
	require_eq(inputDimension_, in.nRows());
	out.resize(outputDimension_, in.nColumns());
	out.copy(in);
	out.divideRowsByScalars(vector_);
}


const Core::ParameterString MatrixMultiplicationPreprocessor::paramMatrixFile_("matrix", "", "features.preprocessor");

const Core::ParameterBool MatrixMultiplicationPreprocessor::paramTransposeMatrix_("transpose", true, "features.preprocessor");

MatrixMultiplicationPreprocessor::MatrixMultiplicationPreprocessor(const char* name) :
		Precursor(name),
		matrixFile_(Core::Configuration::config(paramMatrixFile_, name_)),
		transpose_(Core::Configuration::config(paramTransposeMatrix_, name_))
{}

void MatrixMultiplicationPreprocessor::initialize(u32 inputDimension) {
	Precursor::initialize(inputDimension);
	require(!matrixFile_.empty());
	matrix_.read(matrixFile_, transpose_);
	require_eq(inputDimension_, matrix_.nColumns());
	outputDimension_ = matrix_.nRows();
}

void MatrixMultiplicationPreprocessor::work(const Math::Matrix<Float>& in, Math::Matrix<Float>& out) {
	require(isInitialized_);
	require_eq(inputDimension_, in.nRows());
	out.resize(outputDimension_, in.nColumns());
	
	out.addMatrixProduct(matrix_, in, 0.0, 1.0, false, false);
}
