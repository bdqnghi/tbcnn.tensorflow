#include <bfws.hxx>

#include <strips_state.hxx>
#include <aptk/string_conversions.hxx>

#include <iostream>
#include <fstream>


using	aptk::agnostic::Fwd_Search_Problem;


BFWS::BFWS()
	: STRIPS_Problem(), m_log_filename( "de.log"), m_plan_filename( "plan.ipc" ), m_M(32), m_max_novelty(2) {
}

BFWS::BFWS( std::string domain_file, std::string instance_file )
	: STRIPS_Problem( domain_file, instance_file ), m_log_filename( "bfws.log" ), m_plan_filename( "plan.ipc" ), m_M(32), m_max_novelty(2) {
}

BFWS::~BFWS() {
}


void
BFWS::setup() {
    // NIR: Call superclass method, then do you own thing here
    STRIPS_Problem::setup();
    std::cout << "PDDL problem description loaded: " << std::endl;
    std::cout << "\tDomain: " << instance()->domain_name() << std::endl;
    std::cout << "\tProblem: " << instance()->problem_name() << std::endl;
    std::cout << "\t#Actions: " << instance()->num_actions() << std::endl;
    std::cout << "\t#Fluents: " << instance()->num_fluents() << std::endl;
}


template <typename Search_Engine>
void BFWS::bfws_options( Fwd_Search_Problem&	search_prob, Search_Engine& bfs_engine, unsigned max_novelty, Landmarks_Graph& graph){

	bfs_engine.set_max_novelty( max_novelty );
	bfs_engine.set_use_novelty( true );
	bfs_engine.rel_fl_h().ignore_rp_h_value(true);

	//NIR: engine doesn't own the pointer, need to free at the end
	Land_Graph_Man* lgm = new Land_Graph_Man( search_prob, &graph);
	bfs_engine.use_land_graph_manager( lgm );

	//NIR: Approximate the domain of #r counter, so we can initialize the novelty table, making sure we've got
	//     space for novelty > 1 tuples 
	H_Add_Rp_Fwd hadd( search_prob );
	float h_init=0;
	const aptk::State* s_0 = search_prob.init();
	hadd.eval( *s_0, h_init );
	
	bfs_engine.set_arity( max_novelty, graph.num_landmarks()*h_init );	


	

}


template <typename Search_Engine>
float BFWS::do_search( Search_Engine& engine, aptk::STRIPS_Problem& plan_prob, std::ofstream& plan_stream, bool &found_plan ){

	std::ofstream	details( "execution.details" );	
	engine.start();

	std::vector< aptk::Action_Idx > plan;
	float				cost = -1;

	float ref = aptk::time_used();
	float t0 = aptk::time_used();

	unsigned expanded_0 = engine.expanded();
	unsigned generated_0 = engine.generated();

	found_plan = engine.find_solution( cost, plan );
	
	if ( found_plan  ) {
		details << "Plan found with cost: " << cost << std::endl;
		for ( unsigned k = 0; k < plan.size(); k++ ) {
			details << k+1 << ". ";
			const aptk::Action& a = *(plan_prob.actions()[ plan[k] ]);
			details << a.signature();
			details << std::endl;
			plan_stream << a.signature() << std::endl;
		}
		float tf = aptk::time_used();
		unsigned expanded_f = engine.expanded();
		unsigned generated_f = engine.generated();
		details << "Time: " << tf - t0 << std::endl;
		details << "Generated: " << generated_f - generated_0 << std::endl;
		details << "Expanded: " << expanded_f - expanded_0 << std::endl;
		t0 = tf;
		expanded_0 = expanded_f;
		generated_0 = generated_f;
		plan.clear();

		float total_time = aptk::time_used() - ref;
		std::cout << "Total time: " << total_time << std::endl;
		std::cout << "Nodes generated during search: " << engine.generated() << std::endl;
		std::cout << "Nodes expanded during search: " << engine.expanded() << std::endl;
		std::cout << "Plan found with cost: " << cost << std::endl;
		details.close();
		return total_time;
	}
	else{
		float tf = aptk::time_used();
		unsigned expanded_f = engine.expanded();
		unsigned generated_f = engine.generated();
		details << "Time: " << tf - t0 << std::endl;
		details << "Generated: " << generated_f - generated_0 << std::endl;
		details << "Expanded: " << expanded_f - expanded_0 << std::endl;
		t0 = tf;
		expanded_0 = expanded_f;
		generated_0 = generated_f;

	 	float total_time = aptk::time_used() - ref;	
		std::cout << "Total time: " << total_time << std::endl;
		std::cout << "Nodes generated during search: " << engine.generated() << std::endl;
		std::cout << "Nodes expanded during search: " << engine.expanded() << std::endl;
		std::cout << "Plan found with cost: NOTFOUND" << std::endl;
		details.close();
		return total_time;
	}				      

}

void
BFWS::solve() {

	aptk::STRIPS_Problem* prob = instance();
	
	Fwd_Search_Problem  search_prob( prob );
	
	std::ofstream	plan_stream;
	plan_stream.open( m_plan_filename );
    
	prob->compute_edeletes();	

	Gen_Lms_Fwd    gen_lms( search_prob );
	Landmarks_Graph graph( *prob );

	gen_lms.set_only_goals( true );
	//gen_lms.set_goal_ordering( false );
	
	gen_lms.compute_lm_graph_set_additive( graph );
	
	std::cout << "Goals found: " << graph.num_landmarks() << std::endl;
	std::cout << "Goals_Edges found: " << graph.num_landmarks_and_edges() << std::endl;

	//graph.print( std::cout );       


	bool found_plan = false;
	
	
	if(m_search_alg.compare("BFWS-f5-landmarks") == 0 ){
		
		std::cout << "Starting search with BFWS-f5-landmarks..." << std::endl;
			
		k_BFWS bfs_engine( search_prob );	
		
		/**
		 * Use landmark count instead of goal count
		 */
		Gen_Lms_Fwd    gen_lms( search_prob );
		gen_lms.set_only_goals( false );
		Landmarks_Graph graph1( *prob );
		gen_lms.compute_lm_graph_set_additive( graph1 );

		bfws_options( search_prob, bfs_engine, m_max_novelty, graph1 );
				
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

		plan_stream.close();

		return;
	}
	else 	if( m_search_alg.compare("BFWS-goalcount-only") == 0 ){
		
		std::cout << "Starting search with BFWS(w_(#G), #G)..." << std::endl;
			
		k_BFWS bfs_engine( search_prob );		      
		
		bfws_options( search_prob, bfs_engine, m_max_novelty, graph );
				
		//Do not use #rp
		bfs_engine.set_use_rp(false);
		
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

	}
	else 	if(m_search_alg.compare("BFWS-f5") == 0 ){
		
		std::cout << "Starting search with BFWS-f5..." << std::endl;
			
		k_BFWS bfs_engine( search_prob );	

		bfws_options( search_prob, bfs_engine, m_max_novelty, graph );
		
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

	}
	else 	if( m_search_alg.compare("BFWS-f5-initstate-relevant") == 0 ){
		
		std::cout << "Starting search with BFWS-f5... R computed once from s0" << std::endl;
			
		k_BFWS bfs_engine( search_prob );
		
		bfws_options( search_prob, bfs_engine, m_max_novelty, graph );
		
		bfs_engine.set_use_rp_from_init_only( true );
		
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

	}
	else 	if( m_search_alg.compare("k-BFWS") == 0 ){
		
		std::cout << "Starting search with k-BFWS..." << std::endl;
			
		k_BFWS bfs_engine( search_prob );	
		
		bfws_options( search_prob, bfs_engine, m_max_novelty, graph );

		bfs_engine.set_use_novelty_pruning( true );
		
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

		plan_stream.close();
		
		return;
	}
	else 	if( m_search_alg.compare("k-M-BFWS") == 0 ){
		
		std::cout << "Starting search with k-M-BFWS..." << std::endl;     

		k_BFWS_M bfs_engine( search_prob );	

		bfws_options( search_prob, bfs_engine, m_max_novelty, graph );

		bfs_engine.set_use_novelty_pruning( true );
		bfs_engine.set_M( m_M );
		
		std::cout << "New M-Value: " << m_M << std::endl;
			
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
			
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

		plan_stream.close();
		
		return;
	}
	else 	if( m_search_alg.compare("k-M-C-BFWS") == 0 ){
		
		std::cout << "Starting search with k-M-C-BFWS..." << std::endl;
		
		k_BFWS_Consistency_M bfs_engine( search_prob );	

		bfws_options( search_prob, bfs_engine, m_max_novelty, graph );
		
		bfs_engine.set_use_novelty_pruning( true );
		bfs_engine.set_M( m_M );
	
		std::cout << "New M-Value: " << m_M << std::endl;
			
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
			
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;
		
		plan_stream.close();
		
		return;
	}
	else 	if( m_search_alg.compare("k-C-BFWS") == 0 ){
		
		std::cout << "Starting search with k-C-BFWS..." << std::endl;
			
		k_BFWS_Consistency bfs_engine( search_prob );	

		bfws_options( search_prob, bfs_engine, m_max_novelty, graph );

		bfs_engine.set_use_novelty_pruning( true );	       

		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

		plan_stream.close();
		
		return;
	}else 	if( m_search_alg.compare("1-C-BFWS") == 0 ){
		
		std::cout << "Starting search with 1-C-BFWS..." << std::endl;
			
		k_BFWS_Consistency bfs_engine( search_prob );	

		bfws_options( search_prob, bfs_engine, 1, graph );

		bfs_engine.set_use_novelty_pruning( true );
		
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

		plan_stream.close();
		
		return;
	}
	else if( m_search_alg.compare("1-BFWS") == 0 ){
	        std::cout << "Starting search with 1-BFWS..." << std::endl;
	
		k_BFWS bfs_engine( search_prob );	

		bfws_options( search_prob, bfs_engine, 1, graph );

		bfs_engine.set_use_novelty_pruning( true );
		
		float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
		std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;

		return;
        }
 

	


    //Fast First Consistency
    if( m_search_alg.compare("DUAL-C-BFWS") == 0 and !found_plan)	{
	    std::cout << "Starting search with 1-C-BFWS..." << std::endl;
	
	    k_BFWS_Consistency bfs_engine( search_prob );	
	   
	    bfws_options( search_prob, bfs_engine, 1, graph );

	    bfs_engine.set_use_novelty_pruning( true );
	    	
	    float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
		
	    std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;
    }
    //Fast First (FOR AAAI-17)
    if( m_search_alg.compare("DUAL-BFWS") == 0 and !found_plan)	{
            std::cout << "Starting search with 1-BFWS..." << std::endl;
	
	    k_BFWS bfs_engine( search_prob );	
	    
	    bfws_options( search_prob, bfs_engine, 1, graph );

	    bfs_engine.set_use_novelty_pruning( true );
	    
	    float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
	    
	    std::cout << "Fast-BFS search completed in " << bfs_t << " secs" << std::endl;
    }
	
	
    if(!found_plan && (m_search_alg.compare("DUAL-BFWS") == 0 or m_search_alg.compare("DUAL-C-BFWS") == 0 ) ){
	    std::cout << "Starting search with BFWS(novel,land,h_ff)..." << std::endl;

	    BFWS_w_hlm_hadd bfs_engine( search_prob );	
	    bfs_engine.h4().ignore_rp_h_value(true);

	    /**
	     * Use landmark count instead of goal count
	     */
	    Gen_Lms_Fwd    gen_lms( search_prob );
	    gen_lms.set_only_goals( false );	   
	    Landmarks_Graph graph1( *prob );
	    gen_lms.compute_lm_graph_set_additive( graph1 );
	 
	    Land_Graph_Man lgm( search_prob, &graph1);
	    bfs_engine.use_land_graph_manager( &lgm );

	    std::cout << "Landmarks found: " << graph1.num_landmarks() << std::endl;
	    std::cout << "Landmarks_Edges found: " << graph1.num_landmarks_and_edges() << std::endl;

	    bfs_engine.set_arity( m_max_novelty, graph1.num_landmarks_and_edges() );
	    bfs_engine.set_arity_2( m_max_novelty,  1 );

	    found_plan = false;
	    float bfs_t = do_search( bfs_engine, *prob, plan_stream, found_plan );
			
	    std::cout << "BFS search completed in " << bfs_t << " secs" << std::endl;	
	
    }	
	
	
	
	
	
    plan_stream.close();


	    
    
}

