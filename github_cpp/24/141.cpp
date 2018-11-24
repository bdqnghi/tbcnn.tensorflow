/*
Assumes global variables:
distances[] - a unordered_map or array; key: T, value: int
parent[] - 
adjacency_matrix[][] = weight
Also assumes Heap class
*/
template <typename T>
int prim(vector<T> node_list, T source) {
	int treecost = 0;
	vector<pair<int, T>> v;
	for (int i = 0; i < node_list.size(); ++i) {
		T val = node_list[i];
		if (val == source) {
			distances[source] = 0;
			v.push_back(make_pair(0, source));
		}
		else {
			distances[val] = 2147483647;
			v.push_back(make_pair(distances[val], val));
		}
	}

	Heap<pair<int, T>> to_process(v);
	while (!to_process.empty()) {
		pair<int, T> node = to_process.extract_min();
		treecost += distances[node.second];
		for (T adj : node_list) {
			if (adjacency_matrix[node.second][adj] == 0)
				continue;
			int weight = adjacency_matrix[node.second][adj];
			if (to_process.contains(make_pair(distances[adj], adj)) && weight < distances[adj]) {
				to_process.decrease_key(make_pair(distances[adj], adj), make_pair(weight, adj));
				distances[adj] = weight;
				parent[adj] = node.second;
			}
		}
	}
	return treecost;
}