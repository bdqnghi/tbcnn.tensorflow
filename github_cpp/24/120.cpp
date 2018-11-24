/**
 * Definition for a Connection.
 * class Connection {
 * public:
 *   string city1, city2;
 *   int cost;
 *   Connection(string& city1, string& city2, int cost) {
 *       this->city1 = city1;
 *       this->city2 = city2;
 *       this->cost = cost;
 * }
 */
class Solution {
public:
    /**
     * @param connections given a list of connections include two cities and cost
     * @return a list of connections from results
     */
    static bool cmp_cost(const Connection &a, const Connection &b) {
        return a.cost < b.cost;
    }
    static bool cmp_name(const Connection &a, const Connection &b) {
        if (a.city1 != b.city1) {
            return a.city1 < b.city1;
        }
        return a.city2 < b.city2;
    }
    static bool cmp(const Connection &a, const Connection &b) {
        if (a.cost != b.cost) {
            return a.cost < b.cost;
        }
        if (a.city1 != b.city1) {
            return a.city1 < b.city1;
        }
        return a.city2 < b.city2;
    }
     
    unordered_map<string, string> father;
    int treeNum;
     
    vector<Connection> lowestCost(vector<Connection>& connections) {
        // Write your code here
        treeNum = 0;
        
        //1 find how many cities
        for (auto &C : connections) {
            string city1 = C.city1;
            string city2 = C.city2;
            if (father.find(city1) == father.end()) {
                father[city1] = city1;
                ++treeNum;
            }
            if (father.find(city2) == father.end()) {
                father[city2] = city2;
                ++treeNum;
            }
        }
        
        //2 sort the input with the cost
        sort(connections.begin(), connections.end(), cmp);
        //sort(connections.begin(), connections.end(), cmp_name);
        
        //3 connect cities and count how many tree
        int costSum = 0;
        vector<Connection> result;
        
        for (int i = 0; i < connections.size(); ++i) {
            string a = connections[i].city1;
            string b = connections[i].city2;
            string fa = find(a);
            string fb = find(b);
            if (fa == fb) {
                continue;
            }
            Connect(a, b);
            result.push_back(connections[i]);
            if (treeNum == 1) {
                break;
            }
        }
        
        //output
        if (treeNum > 1) {
            result.clear();
            return result;
        }
        
        sort(result.begin(), result.end(), cmp);
        return result;
        
    }
    
private:
    string find(string &x) {
        if (father[x] == x) {
            return x;
        }
        return father[x] = find(father[x]);
    }
    
    void Connect (string &a, string &b) {
        string fa = find(a);
        string fb = find(b);
        if (fa != fb) {
            father[fa] = fb;
            --treeNum;
        }
    }
};
