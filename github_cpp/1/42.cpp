








#include <boost/config.hpp>

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>

#include <boost/graph/visitors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_utility.hpp>



template <class ParentDecorator>
struct print_parent {
  print_parent(const ParentDecorator& p_) : p(p_) { }
  template <class Vertex>
  void operator()(const Vertex& v) const {
    std::cout << "parent[" << v << "] = " <<  p[v]  << std::endl;
  }
  ParentDecorator p;
};


template <class NewGraph, class Tag>
struct graph_copier 
  : public boost::base_visitor<graph_copier<NewGraph, Tag> >
{
  typedef Tag event_filter;

  graph_copier(NewGraph& graph) : new_g(graph) { }

  template <class Edge, class Graph>
  void operator()(Edge e, Graph& g) {
    boost::add_edge(boost::source(e, g), boost::target(e, g), new_g);
  }
private:
  NewGraph& new_g;
};

template <class NewGraph, class Tag>
inline graph_copier<NewGraph, Tag>
copy_graph(NewGraph& g, Tag) {
  return graph_copier<NewGraph, Tag>(g);
}

int main(int , char* []) 
{
  typedef boost::adjacency_list< 
    boost::mapS, boost::vecS, boost::bidirectionalS,
    boost::property<boost::vertex_color_t, boost::default_color_type,
        boost::property<boost::vertex_degree_t, int,
          boost::property<boost::vertex_in_degree_t, int,
    boost::property<boost::vertex_out_degree_t, int> > > >
  > Graph;
  
  Graph G(5);
  boost::add_edge(0, 2, G);
  boost::add_edge(1, 1, G);
  boost::add_edge(1, 3, G);
  boost::add_edge(1, 4, G);
  boost::add_edge(2, 1, G);
  boost::add_edge(2, 3, G);
  boost::add_edge(2, 4, G);
  boost::add_edge(3, 1, G);
  boost::add_edge(3, 4, G);
  boost::add_edge(4, 0, G);
  boost::add_edge(4, 1, G);

  typedef Graph::vertex_descriptor Vertex;

  Graph G_copy(5);
  
  
  std::vector<Vertex> p(boost::num_vertices(G));
  
  
  typedef std::vector<Vertex>::value_type* Piter;

  
  
  
  boost::graph_traits<Graph>::vertices_size_type d[5];
  std::fill_n(d, 5, 0);

  
  Vertex s = *(boost::vertices(G).first);
  p[s] = s;
  boost::breadth_first_search
    (G, s, 
     boost::visitor(boost::make_bfs_visitor
     (std::make_pair(boost::record_distances(d, boost::on_tree_edge()),
                     std::make_pair
                     (boost::record_predecessors(&p[0], 
                                                 boost::on_tree_edge()),
                      copy_graph(G_copy, boost::on_examine_edge())))) ));

  boost::print_graph(G);
  boost::print_graph(G_copy);

  if (boost::num_vertices(G) < 11) {
    std::cout << "distances: ";
#ifdef BOOST_OLD_STREAM_ITERATORS
    std::copy(d, d + 5, std::ostream_iterator<int, char>(std::cout, " "));
#else
    std::copy(d, d + 5, std::ostream_iterator<int>(std::cout, " "));
#endif
    std::cout << std::endl;

    std::for_each(boost::vertices(G).first, boost::vertices(G).second, 
                  print_parent<Piter>(&p[0]));
  }

  return 0;
}
