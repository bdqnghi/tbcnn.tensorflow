







#include <functional>
#include "tsort.hpp"







GRAPH_BEGIN








array_t tsort(const graph_t& G)
{
    index_t n = G.size();
    std::vector<vcolor> color(n, vcolor::white);
    array_t lst(n);

    
    std::function<bool(index_t)> dfs_visit = [&](index_t u) {
        color[u] = vcolor::gray;    
        for (auto&& e : G[u]) {     
            index_t w = e.dst;

            
            if (color[w] == vcolor::white && !dfs_visit(w)) {
                 return false;
            }
        }
        color[u] = vcolor::black;   
        lst.emplace_back(u);        
        return true;
    };


    
    for (index_t v = 0; v < n; ++v) {
        if (color[v] == vcolor::white && !dfs_visit(v)) {
            return { };
        };
    }
    reverse(lst.begin(), lst.end());  
    return lst;     
}







GRAPH_END
