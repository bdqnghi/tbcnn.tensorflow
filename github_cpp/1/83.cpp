#include <HidroBoostBreadthFirstSearchFactory.h>
#include <HidroBoostBreadthFirstSearch.h>

#include <TeException.h>


HidroBoostBreadthFirstSearchFactory::HidroBoostBreadthFirstSearchFactory()
: HidroBoostAlgorithmFactory(std::string("Breadth First Search"))
{
};      

HidroBoostBreadthFirstSearchFactory::~HidroBoostBreadthFirstSearchFactory()
{
};


HidroBoostAlgorithms* HidroBoostBreadthFirstSearchFactory::build (const HidroBoostParams& arg)
{
	HidroBoostAlgorithms* instancePtr = new HidroBoostBreadthFirstSearch();

	if( ! instancePtr )
	{
		throw TeException( FACTORY_PRODUCT_INSTATIATION_ERROR );
	}

	if(!instancePtr->reset(arg))
	{
		throw TeException( UNKNOWN_ERROR_TYPE );
	}

	return instancePtr;
}
