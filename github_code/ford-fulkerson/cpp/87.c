#pragma once
#include "stdafx.h"
#include "Navigation.h"

int sizeMenu() {
	int menu_choice = menu(MENU_X, MENU_Y, "Select number of vertices", 5, "\t100", "\t200", "\t300", "\t400","\t500");
	return (int) 100 * menu_choice;
}

float densityMenu() {
	int menu_choice = menu(MENU_X, MENU_Y, "Select density of a graph", 4, "\t25%", "\t50%", "\t75%", "\t99%");
	switch (menu_choice) {
	case 1: return 0.25f;
	case 2: return 0.5f;
	case 3: return 0.75f;
	case 4: return 0.99f;
	}
	return 0;
}

Algorithms algorithmsMenu() {
	// This should return a pointer to a graph function that should be run;
	int structure_choice = menu(MENU_X, MENU_Y, "Select method of representation", 2, "Adjacency Matrix", "Adjacency List");
	system("cls");
	int algorithm_choice = menu(MENU_X, MENU_Y, "Select an algorithm to run", 6, "SP - Dijkstra", "SP - Bellman-Ford", "MST - Prim", "MST - Kruskal", "MF - Ford-Fulkerson (BFS)", "MF - Ford-Fulkerson (DFS)");
	system("cls");
	if (structure_choice == 2)
		algorithm_choice += 6;
	switch (algorithm_choice) {
	case 1:		return { sp_d_m, "Matrix", "Dijkstra" };
	case 2:		return { sp_bf_m, "Matrix", "BellmanFord" };
	case 3:		return { mst_p_m, "Matrix", "Prim" };
	case 4:		return { mst_k_m, "Matrix", "Kruskal" };
	case 5:		return { mf_bfs_m, "Matrix", "Ford-Fulkerson (BFS)" };
	case 6:		return { mf_dfs_m, "Matrix", "Ford-Fulkerson (DFS)" };
	case 7:		return { sp_d_l, "List", "Dijkstra" };
	case 8:		return { sp_bf_l, "List", "BellmanFord" };
	case 9:		return { mst_p_l, "List", "Prim" };
	case 10:	return { mst_k_l, "List", "Kruskal" };
	case 11:	return { mf_bfs_l, "List", "Ford-Fulkerson (BFS)" };
	case 12:	return { mf_dfs_l, "List", "Ford-Fulkerson (DFS)" };
	}
	std::cin.sync();
}

void manualMenu() {
	Sleep(100);
	std::string file_path = inputPrompt("Enter path of a file with graph");
	Graph * graph = new Graph;
	graph->setManualMode(true);
	graph->setSourceFilePath(file_path);
	graph->loadGraphFromFile(file_path);
	// Graph is loaded and ready for testing
	while (graph->getStatus()) {
		int menu_choice = menu(MENU_X, MENU_Y, "General Menu", 4, "Run algorithms", "Generate graph", "View Graph", "Return");
		switch (menu_choice) {
		case 1: manualTest(graph); break;
		case 2: break;					// Unimplemented modificationMenu
		case 3: viewMenu(graph); break;
		case 4: delete graph; return;
		}
	}
	delete graph;
}

void manualTest(Graph* graph) {
	// Select an algorithm to run
	alg_pt algorithm = algorithmsMenu().pt;
	// If we want to run Prim's Algorithm, first we must convert the graph to an undirected one
	if (!graph->getUndirected() && algorithm == mst_p_l || algorithm == mst_p_m )
		graph->setUndirected();
	// If we want to run other algortihms, we reload the graph, to get it's directed form
	if (graph->getUndirected() && !(algorithm == mst_p_l || algorithm == mst_p_m)) {
		std::string file_path = graph->getSourceFilePath();
		delete graph;
		graph = new Graph();
		graph->setManualMode(true);
		graph->setSourceFilePath(file_path);
		graph->loadGraphFromFile(file_path);
	}

	// Run the algorithm
	(graph->*algorithm)();
	if (graph->getUndirected())
		std::cout << "Graph was converted to an undirected graph !!!\n\n";
	std::cout << graph->getAlgorithmOutput() << "\n\n";
	system("Pause");
	system("cls");
	return;
}

void viewMenu(Graph* g) {
	// This function displays a graph in list/matrix form (selected by the user) and then returns to the manualMenu
	while (true) {
		int menu_choice = menu(MENU_X, MENU_Y, "Select representation of a graph", 3, "Adjacency Matrix", "Adjacency List", "Return");
		system("cls");
		switch (menu_choice) {
		case 1: {
			std::cout << "Adjacency Matrix of the graph:\n" << g->MatrixToString();
			system("pause");
			break;
		}
		case 2: {
			std::cout << "Adjacency List of the graph:\n" << g->ListToString();
			system("pause");
			break;
		}
		case 3: return;
		}
	}
	return;
}

void modificationMenu(Graph* g) {
	// THIS FUNCTION IS OF A SECONDARY PRIORITY
	// This function should allow for modification of vertices, edges etc.
}

void performTimeTest() {
	// This function should perform a test on a graph using selected algorithm and then display/save test data
	typedef std::chrono::high_resolution_clock clock;
	clock::time_point start_time, end_time;
	std::chrono::duration<double, std::milli> duration;
	double * results;
	Graph * graph;
	Algorithms algorithm = algorithmsMenu();
	alg_pt algo_pt = algorithm.pt;

	// run the test 100 times
	int ammount = 100;
	// Get test parameters - algorithm + representation, size, density
	
	int size = sizeMenu();
	float density = densityMenu();
	system("cls");
	// Test Starts here
	results = new double[ammount]();
	for (int i = 0; i < ammount; ++i) {
		gotoXY(0, 0);
		printf("Performing a test...");
		// Display progress
		gotoXY(0, 1);
		printf("%02d %%", (i * 100 / ammount));
		// Generate a random graph
		graph = new Graph;
		graph->generateGraph(size, density);
		if (algo_pt == mst_p_m || algo_pt == mst_p_l)
			graph->setUndirected();
		// Time measurment
		start_time = clock::now();
		(*graph.*algo_pt)();
		end_time = clock::now();

		duration = end_time - start_time;
		results[i] += duration.count();
		double current_result = results[i];
		delete graph;
	}
	system("cls");
	std::cout << generateResults(results, ammount, algorithm, size, density);
	delete[] results;
	system("pause");
}

std::string generateResults(double* results, int& ammount, Algorithms& algorithm, int& size, float& density) {
	
	sys_clock::time_point p = sys_clock::now();
	std::time_t t = sys_clock::to_time_t(p);
	std::string time_stamp = std::ctime(&t);
	std::string container_name = algorithm.container_name;
	std::string algorithm_name = algorithm.algorithm_name;
	
	double mean_time = 0;
	int good_res_count = 0;
	std::stringstream ss;

	ss << "################################################################################\n\n";
	ss << "Date of measurment :\t" << time_stamp;
	ss << "Container          :\t" << container_name << "\n";
	ss << "Algorithm Name     :\t" << algorithm_name << "\n";
	ss << "Graph Size         :\t" << size << "\n";
	ss << "Density            :\t" << density << "\n";
	ss << "Measurment count   :\t" << ammount << "\n\n";
	ss << "--------------------------------------------------------------------------------\n";

	for (int i = 0; i < ammount; ++i) {
		ss << "Pomiar " << i + 1 << ":\t\t" << results[i] << "\t\tms\n";
		mean_time += results[i];
	}
	ss << "--------------------------------------------------------------------------------\n";
	ss << "Srednia z pomiarow:\t" << mean_time / ammount << "\t\tms\n\n";
	ss << "################################################################################\n";
	std::string output = ss.str();
	saveResultsToFile(output, time_stamp, algorithm, size, density);
	return output;
}

void saveResultsToFile(std::string& results, std::string& time_stamp, Algorithms& algorithm, int& size, float& density) {
	
	std::string prefix("TestResults/");
	std::string container_name(algorithm.container_name);
	std::string algorithm_name(algorithm.algorithm_name);
	std::string density_str(std::to_string(density));
	density_str.erase(density_str.find_last_not_of('0') + 1, std::string::npos);

	std::string file_name = algorithm_name + "__" + container_name + "__" +  std::to_string(size) + "__" + density_str + ".txt";
	std::ofstream out;
	out.open(file_name, std::ios::app);
	out << results;
	out.close();
}
	



