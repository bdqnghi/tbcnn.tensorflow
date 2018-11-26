#include <algorithm>
#include <iostream>
#include "fordfulkerson.h"
#include "dfs.h"

std::pair<double, Graph>
ford_fulkerson_core( Graph &g, Node &s, Node &t, std::function<Path(Graph &, Node &, Node &)> search_func )
{
    Graph residual( g );
    double max_flow = 0.0;

    Path path;
    while( !( path = search_func( residual, s, t ) ).empty() )
    {
        const auto &it = std::min_element( path.begin(), path.end(), EdgeComperator() );
        std::cout << std::endl
                  << "Found augmenting path:" << std::endl;
        print_path( path );
        const double min_weight = ( *it )->second;
        max_flow += min_weight;
        for( Edge *edge : path )
        {
            edge->second -= min_weight;
        }
    }
    return std::pair<double, Graph>( max_flow, residual );
}

std::pair<double, Graph> ford_fulkerson( Graph &g, Node &s, Node &t )
{
    return ford_fulkerson_core( g, s, t, dfs_recursive );
}
