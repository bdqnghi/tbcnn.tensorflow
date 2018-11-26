#ifndef MINIMUMSPANNINGTREE
#define MINIMUMSPANNINGTREE

#include "ExampleBase.h"
#include <string>

class MinimumSpanningTree : public ExampleBase {

public:

	MinimumSpanningTree();

	~MinimumSpanningTree();

	virtual std::string getName() const;


protected:

    cl_mem matrix;
	cl_mem nearNode;
	cl_mem minDist;
	cl_mem memSizeX;
	int *msTree;

	static const float validationThreshold;

	void scaleAndSetSizes(float sizeX, float sizeY, float sizeZ);

	void discardMembers();

	void initializeMembers();

	void fillInData(float *matrixArray) const;

	void performAlgorithm();

	const char *algorithm() const;

	void addNodes();

	const int nearestNode(float const* const& minDist) const;

	void updateDistance(float const* const& matrix, int *&nearNode, float *&minDist, const int nearestNode) const;

	const bool isValid() const;
};

#endif