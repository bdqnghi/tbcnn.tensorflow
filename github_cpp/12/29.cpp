    #include <bits/stdc++.h>
     
    using namespace std;
     
    struct node {
        int weight;
        pair<int, int> edge;
    };
     
    struct ds {
        int val;
        int size;
    };
     
    bool comparator(const node& node1, const node& node2) {
        return node1.weight < node2.weight;
    }
     
    vector<ds> Arr;
     
    void initialize(int n) {
        for(int i = 0; i < n; ++i) {
            ds temp;
            temp.val = i;
            temp.size = 1;
     
            Arr.push_back(temp);
        }
    }
     
    int root(int i) {
        while(Arr.at(i).val != i) {
            Arr.at(i).val = Arr.at(Arr.at(i).val).val;
            i = Arr.at(i).val;
        }
     
        return i;
    }
     
    void WeightedUnion(int a, int b) {
        int r_a = root(a);
        int r_b = root(b);
     
        if(r_a == r_b) 
            return;
     
        if(Arr.at(r_a).size < Arr.at(r_b).size) {
            Arr.at(r_a).val = Arr.at(r_b).val;
            Arr.at(r_b).size +=  Arr.at(r_a).size;
        }
        else {
            Arr.at(r_b).val = Arr.at(r_a).val;
            Arr.at(r_a).size +=  Arr.at(r_b).size;
        }
        
    }
     
    int Find(int a, int b) {
        return root(a) == root(b);
    }
     
    int Kruskal(vector<node>& Graph) {
        int minCost = 0;
     
        for(auto& i : Graph) {
            
            if(!Find(i.edge.first, i.edge.second)) {
                WeightedUnion(i.edge.first, i.edge.second);
                minCost += i.weight;
            }    
        }
     
        return minCost;
    }
     
    int main() {
        int nodes, edges;
        cin>>nodes>>edges;
     
        vector<node> Graph(edges+1);
        initialize(nodes+1);
     
        for(int i = 1; i <= edges; ++i) {
            int x, y, w;
            cin>>x>>y>>w;
     
            Graph.at(i).weight = w;
            Graph.at(i).edge = make_pair(x, y);
        }
     
        sort(Graph.begin(), Graph.end(), comparator);
     
        cout<<Kruskal(Graph)<<endl;
        
        return 0;
    }