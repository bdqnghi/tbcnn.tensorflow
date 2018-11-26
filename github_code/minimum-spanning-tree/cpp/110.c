#include "../include/MinimumSpanningTree.h"

MinimumSpanningTree::MinimumSpanningTree()
	:	matrix(NULL),
		nearNode(NULL),
		minDist(NULL),
		memSizeX(NULL),
		msTree(NULL)
{ }

MinimumSpanningTree::~MinimumSpanningTree() {
	this->discardMembers();
}

std::string MinimumSpanningTree::getName() const {
	return "MinimumSpanningTree";
}

void MinimumSpanningTree::scaleAndSetSizes(float sizeX, float sizeY, float sizeZ) {
    this->sizeX = (int) (sizeX * 1400.0);
}

void MinimumSpanningTree::discardMembers() {
    if (this->matrix) clReleaseMemObject(this->matrix);
    if (this->nearNode) clReleaseMemObject(this->nearNode);
    if (this->minDist) clReleaseMemObject(this->minDist);
    if (this->memSizeX) clReleaseMemObject(this->memSizeX);
    if (this->msTree) delete this->msTree;
}

void MinimumSpanningTree::initializeMembers() {
	int error = 0;

    this->matrix = clCreateBuffer(this->context, CL_MEM_READ_WRITE, sizeof(float) * this->sizeX * this->sizeX, NULL, NULL);
    this->nearNode = clCreateBuffer(this->context, CL_MEM_READ_WRITE, sizeof(int) * this->sizeX, NULL, NULL);
    this->minDist = clCreateBuffer(this->context, CL_MEM_READ_WRITE, sizeof(float) * this->sizeX, NULL, NULL);
    this->memSizeX = clCreateBuffer(this->context,  CL_MEM_READ_WRITE, sizeof(size_t), NULL, NULL);
	this->msTree = new int[this->sizeX * 2];

    float *matrixArray = new float[this->sizeX * this->sizeX];
	this->fillInData(matrixArray);
	
	for (cl_uint i=0; i<this->deviceCount; i++) {
		error  = clEnqueueWriteBuffer(this->commands[i], this->matrix, CL_TRUE, 0, sizeof(float) * this->sizeX * this->sizeX, matrixArray, 0, NULL, NULL);
		error |= clEnqueueWriteBuffer(this->commands[i], this->memSizeX, CL_TRUE, 0, sizeof(size_t), &this->sizeX, 0, NULL, NULL);
		if (error != CL_SUCCESS)
			this->exitWith("Error: Failed to write to source array for " + this->getName() + "!\n", 1);
	}

	delete matrixArray;
}

void MinimumSpanningTree::fillInData(float *matrixArray) const {
	int x, y;

	for (int pos = 0; pos < this->sizeX * this->sizeX; pos++)
		matrixArray[pos] = FLT_MAX;

	for (int i = 0; i < 5 * this->sizeX; i++) 	{
		x = rand() % this->sizeX;
		y = rand() % this->sizeX;

		if (x != y) 		{
			matrixArray[x * this->sizeX + y] = this->randomFloat();
			matrixArray[y * this->sizeX + x] = matrixArray[x * this->sizeX + y];
		}
	}
}

void MinimumSpanningTree::performAlgorithm() {
	int error = 0;
	size_t local = 0;
	size_t global = 0;

	for (cl_uint i=0; i<this->deviceCount; i++) {
		error  = clSetKernelArg(this->kernel[i], 0, sizeof(cl_mem), &this->matrix);
		error |= clSetKernelArg(this->kernel[i], 1, sizeof(cl_mem), &this->nearNode);
		error |= clSetKernelArg(this->kernel[i], 2, sizeof(cl_mem), &this->minDist);
		error |= clSetKernelArg(this->kernel[i], 3, sizeof(cl_mem), &this->memSizeX);
		if (error != CL_SUCCESS)
			this->exitWith("Error: Failed to set kernel arguments for " + this->getName() + "!", error);
	}

	for (cl_uint i=0; i<this->deviceCount; i++) {
		error = clGetKernelWorkGroupInfo(this->kernel[i], this->device_ids[i], CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &local, NULL);
		if (error != CL_SUCCESS)
			this->exitWith("Error: Failed to retrieve kernel work group info for " + this->getName() + "!", error);
	}

	global = this->globalWorkSize(local, this->sizeX);
	
	enqueueAndFinish(this->kernel, this->commands, &global, &local, 1);

	this->addNodes();
}

const char *MinimumSpanningTree::algorithm() const {
	return "										\n "\
		"__kernel void algorithm(					\n "\
		"	__global float *matrix,					\n "\
		"	__global int *nearNode,					\n "\
		"	__global float *minDist,				\n "\
		"	__global size_t *sizeX)					\n "\
		"{											\n "\
		"	size_t id = get_global_id(0);			\n "\
		"											\n "\
		"	if(id < *sizeX)							\n "\
		"	{										\n "\
		"		nearNode[id] = 0;					\n "\
		"		minDist[id] = matrix[id * *sizeX];	\n "\
		"	}										\n "\
		"}											";
}

void MinimumSpanningTree::addNodes() {
	int error, nearestNode;
    float *matrixArray = new float[this->sizeX * this->sizeX];
    int *nearNodeArray = new int[this->sizeX];
    float *minDistArray = new float[this->sizeX];
	float min;

	for (cl_uint i=0; i<this->deviceCount; i++) {
		error = clEnqueueReadBuffer(this->commands[i], this->matrix, CL_TRUE, 0, sizeof(float) * this->sizeX * this->sizeX, matrixArray, 0, NULL, NULL);
		error |= clEnqueueReadBuffer(this->commands[i], this->nearNode, CL_TRUE, 0, sizeof(int) * this->sizeX, nearNodeArray, 0, NULL, NULL);
		error |= clEnqueueReadBuffer(this->commands[i], this->minDist, CL_TRUE, 0, sizeof(float) * this->sizeX, minDistArray, 0, NULL, NULL);
		if (error != CL_SUCCESS)
			this->exitWith("Error: Failed to read output array for " + this->getName() + "!\n", 1);
	}

	for (int x = 0; x < this->sizeX; x++) 	{
		nearestNode = this->nearestNode(minDistArray);
		min = minDistArray[nearestNode];

		this->msTree[x] = nearNodeArray[nearestNode];
		this->msTree[x + this->sizeX] = nearestNode;
		minDistArray[nearestNode] = -1;

		this->updateDistance(matrixArray, nearNodeArray, minDistArray, nearestNode);
	}

	delete matrixArray;
	delete nearNodeArray;
	delete minDistArray;
}

const int MinimumSpanningTree::nearestNode(float const* const& minDist) const {
	float min = FLT_MAX;
	int nearestNode = 0;

	for (int x = 1; x < this->sizeX; x++)
		if (0 <= minDist[x] && minDist[x] < min) {
			min = minDist[x];
			nearestNode = x;
		}

	return nearestNode;
}

void MinimumSpanningTree::updateDistance(float const* const& matrix, int *&nearNode, float *&minDist, const int nearestNode) const {
	for (int x = 1; x < this->sizeX; x++)
		if (matrix[x * this->sizeX + nearestNode] < minDist[x]) {
			minDist[x] = matrix[x * this->sizeX + nearestNode];
			nearNode[x] = nearestNode;
		}
}

const bool MinimumSpanningTree::isValid() const {
	return true;
}