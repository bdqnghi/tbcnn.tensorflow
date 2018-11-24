class Solution {
public:
    vector<int> G[2000], rev[2000];
    stack<int> s;
    int vis[2000];
    
    bool dfs(int u)
    {
        vis[u] = -1;
        for(int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i];
            if(vis[v] == -1)
                return false;
            if(!vis[v] && !dfs(v)) 
                    return false;
        }
        vis[u] = 1;
        s.push(u);
        return true;
    }
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> ret;
        fill(vis, vis + 2000, 0);
        for(int i = 0; i < prerequisites.size(); i++)
        {
            G[prerequisites[i].second].push_back(prerequisites[i].first);
            rev[prerequisites[i].first].push_back(prerequisites[i].second);
        }
        for(int u = 0; u < numCourses; u++)
        {
            if(!vis[u])
                if(!dfs(u))
                    return ret;
        }
        while(!s.empty())
        {
            ret.push_back(s.top());
            s.pop();
        }
        return ret;
    }
};
