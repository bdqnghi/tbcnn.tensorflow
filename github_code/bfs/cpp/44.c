#include "_lemon_bfs.h"

// Rice
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <rice/Class.hpp>
#include <rice/Object.hpp>

// Lemon
#include <lemon/list_graph.h>
#include <lemon/bfs.h>

using namespace lemon;
using namespace Rice;

namespace {	
	static Bfs<ListDigraph> create(const ListDigraph &graph) {		
    	Bfs<ListDigraph> bfs(graph);
    	return bfs;
	}
}

void register_bfs(Rice::Module rb_mlemon) {  

    typedef void (Bfs<ListDigraph>::*bfs_ldg_start)();
    typedef void (Bfs<ListDigraph>::*bfs_ldg_start_node)(ListDigraph::Node); 

    typedef ListDigraph::Node (Bfs<ListDigraph>::*bfs_ldg_process_node)();

    typedef void (Bfs<ListDigraph>::*bfs_ldg_run)();
    typedef void (Bfs<ListDigraph>::*bfs_ldg_run_node)(ListDigraph::Node); 
    typedef bool (Bfs<ListDigraph>::*bfs_ldg_run_node_node)(ListDigraph::Node, ListDigraph::Node);    

    define_class_under< Bfs<ListDigraph> >(rb_mlemon, "Bfs")    	
        .define_singleton_method("create", create)    	
        .define_method("init", &Bfs<ListDigraph>::init)
        .define_method("add_source", &Bfs<ListDigraph>::addSource)
        .define_method("next_node", &Bfs<ListDigraph>::nextNode)
        .define_method("empty_queue", &Bfs<ListDigraph>::emptyQueue)
        .define_method("queue_size", &Bfs<ListDigraph>::queueSize)
        .define_method("start", bfs_ldg_start(&Bfs<ListDigraph>::start))
        .define_method("start_node", bfs_ldg_start_node(&Bfs<ListDigraph>::start))	
        .define_method("run", bfs_ldg_run(&Bfs<ListDigraph>::run))
        .define_method("run_node", bfs_ldg_run_node(&Bfs<ListDigraph>::run))
        .define_method("run_between", bfs_ldg_run_node_node(&Bfs<ListDigraph>::run))   
        .define_method("process_next_node", bfs_ldg_process_node(&Bfs<ListDigraph>::processNextNode ))   
    ;     
}
