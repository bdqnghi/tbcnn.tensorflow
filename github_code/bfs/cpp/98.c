#include "breadthfirstsearch.h"

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

typedef boost::chrono::high_resolution_clock Clock;
typedef boost::chrono::milliseconds Miliseconds;
typedef Clock::time_point TimePoint;
typedef Clock::duration Duration;

//#define DEBUG

static inline bool inList(std::set<int> s, int v)
{
	for(int i : s)
		if(i==v)
			return true;
	return false;
}

BreadthFirstSearch::BreadthFirstSearch() : GraphSearch()
{
	//std::set<int> o = {1,11};
	//setObstacles(o);
	//printObstacles();
    std::cout << "solving.. \nstart_index : " << start_index << "\ngoal_index : " << goal_index << '\n';
    if(std::get<0>(solve())){
        std::cout << "solved!\n";
        printSolution();
    }
    else
        std::cout << "solution not found\n";
}

BreadthFirstSearch::BreadthFirstSearch(int x, int y) : GraphSearch(x,y)
{
    /*
    std::cout << "solving.. \nstart_index : " << start_index << "\ngoal_index : " << goal_index << '\n';
    if(solve()){
        std::cout << "solved!\n";
        printSolution();
    }
    else
        std::cout << "solution not found\n";
        */
}

std::tuple<int, double> BreadthFirstSearch::solve()
{
    TimePoint t = Clock::now();
    Duration d = t.time_since_epoch();
    Miliseconds start_ms = boost::chrono::duration_cast<Miliseconds>(d);
    Miliseconds end_ms;
    Miliseconds dt;

    int x;
	while(!q.empty())
		q.pop();
#ifdef DEBUG
    std::pair<int,int> d_idx;
#endif
    GraphIterator v_it, v_end;
    q.push(start_index);
    (*g)[vertex(start_index,*g)].state = Alive;
    parent_map[start_index] = -1;
    for(int i : visitedList)
        (*g)[i].state = Unvisited;
    visitedList.clear();
    while(!q.empty()) {
        x = q.front();
        if(x == goal_index) {
			markSolutions();
			s = true;
            need_update = false;
            t = Clock::now();
            d = t.time_since_epoch();
            end_ms = boost::chrono::duration_cast<Miliseconds>(d);
            dt = end_ms - start_ms;
            return std::make_tuple(1,dt.count()/1000.0);
		}
#ifdef DEBUG
        d_idx = to_double_index(x);
        std::cout << "adjacent vertices of " << x << " (" << d_idx.first << "," << d_idx.second << ") : ";
#endif
        for(boost::tie(v_it, v_end) = boost::adjacent_vertices(vertex(x,*g),*g);
            v_it != v_end; ++v_it) {
#ifdef DEBUG
            std::cout << *v_it << " ";
#endif
			auto l = obstacles.find(*v_it);
            if(l == obstacles.end()) {
#ifdef DEBUG
                std::cout << "free ";
#endif
				if((*g)[*v_it].state == Unvisited) {
#ifdef DEBUG
                    std::cout << "unvisited ";
#endif
					(*g)[*v_it].state =  Alive;
					parent_map[*v_it] = x;
                    visitedList.insert(*v_it);
					q.push(*v_it);
				}
                else {
					(*g)[*v_it].state = Dead;
#ifdef DEBUG
                    std::cout << "visited ";
#endif
                }
            }
#ifdef DEBUG
            else {
                std::cout << "obstacle ";
            }
#endif
        }
#ifdef DEBUG
        std::cout << '\n';
#endif
        q.pop();
#ifdef USE_DELAY
        if(en_delay)
            boost::this_thread::sleep_for(boost::chrono::milliseconds(delay_ms));
#endif
    }
    need_update = false;
    t = Clock::now();
    d = t.time_since_epoch();
    end_ms = boost::chrono::duration_cast<Miliseconds>(d);
    dt = end_ms - start_ms;
    s = false;
    return std::make_tuple(0,dt.count()/1000.0);
}

std::string BreadthFirstSearch::string(int i, int option)
{
	std::pair<int,int> p = to_double_index(i);
	std::string s("(");
	s += std::to_string(p.first);
	s += ",";
	s += std::to_string(p.second);
	s += ")";
	//s << std::to_string(p.first);
	//s.insert(std::to_string(p.first));
	//s << ",";
	//s.insert(std::string(","));
	//s << std::to_string(p.second);
	//s.insert(std::to_string(p.second));
	//s << ")";
	//s.insert(std::string(")"));
	return s;
}
