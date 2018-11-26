#include "../core/planner9.hpp"
#include "../core/costs.hpp"

//#include "../problems/jug-pouring.hpp"
//#include "../problems/basic.hpp"
#include "../problems/rescue-numeric.hpp"
//#include "../problems/tower-of-hanoi.hpp"
//#include "../problems/robots.hpp"
//#include "problems/rover.hpp"

#include <boost/progress.hpp>

using namespace std;

int main(int argc, char* argv[]) {
	size_t maxRunCount(1);
	std::ostream* dump(0);
	
	if (argc > 1) {
		maxRunCount = atoi(argv[1]);
	}
	if (argc > 2) {
		dump = &std::cout;
	}

	// FIXME: remove debug here
	//dump = &std::cerr;
	
	MyProblem problem;
	std::cout << Scope::setScope(problem.scope);
	std::cout << "initial state: "<< problem.state << std::endl;
	std::cout << "initial network: " << problem.network << std::endl;
	
	for(size_t i = 0; i < maxRunCount; ++i) {
		boost::progress_timer t;
		
		AlternativesCost alternativesCost;
		
		SimplePlanner9 planner(problem, &alternativesCost, dump);
		boost::optional<Plan> plan = planner.plan();
		if(plan) {
			std::cout << "plan:\n" << *plan << std::endl;
		} else {
			std::cout << "no plan." << std::endl;
		}
	}
	
	return 0;
}
