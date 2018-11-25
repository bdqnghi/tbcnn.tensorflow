

#include <insertionSortParams.hpp>
#include <insertionSource.hpp>
#include <insertionOutput.hpp>
#include <jumpSort.hpp>

#ifdef INSERTION_SORT

class InsertionSortApp : public Application
{
private :
public:
	ActorExecutor * getActorExecutor(Actor *actor)
	{
		if(actor->function->compare("Source") == 0)
			return new IntSource(actor);
		else if((actor->function->compare("JumpSort0") == 0) || (actor->function->compare("JumpSort1") == 0)
				|| (actor->function->compare("JumpSort2") == 0) || (actor->function->compare("JumpSort3") == 0))
			return new JumpSort(actor);
		else if(actor->function->compare("Output") == 0)
			return new IntPrinter(actor);
		else
			return NULL;
	}

	void initApplication (ApplicationData *appData) {}
	void exitApplication (ApplicationData *appData) {}

};

Application * getApplication ()
{
	return new InsertionSortApp();
}

#endif 
