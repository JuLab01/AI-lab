#include <bits/stdc++.h>
using namespace std;

void printPath(vector<vector<pair<int,int>>>& adj, vector<int>& parent,int source, int goal){
    stack<int> st;
    while(goal != source){
        st.push(goal);
         goal = parent[goal];
    }
    cout<<(char)(source + 'A')<<"->";
    while(st.size()!=1){
        cout<<(char)(st.top() + 'A')<<"->";
        st.pop();
    }

    cout<<(char)(st.top() + 'A')<<endl;

}


int A_star(vector<vector<pair<int,int>>>& adj, unordered_map<int,pair<int,int>>& mp, int source, int goal){
    function<int(int)> heuristic = [&](int node){return abs(mp[node].first - mp[goal].first) + abs(mp[node].second - mp[goal].second);};
    
    int n = adj.size();
    vector<int> dist(n,INT_MAX);
    vector<int> parent(n,-1);
    dist[source] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,source});

    while(!pq.empty()){
        pair<int,int> p = pq.top(); pq.pop();
        int node = p.second, distance = p.first;

        if(node == goal) {
            printPath(adj, parent, source, goal);
            return dist[node];
        }

        for(pair<int,int> np: adj[node]){
            int adjNode = np.first, adjDistance = np.second;
            if(dist[adjNode] > dist[node] + adjDistance){
                dist[adjNode] = dist[node] + adjDistance;
                parent[adjNode] = node;
                pq.push({dist[adjNode] + heuristic(adjNode) - heuristic(source), adjNode});
            }
            
        }   
    }

    return INT_MAX;
    
}

int main()
{
    vector<pair<pair<int, int>,int>> edges;
    unordered_map<int,pair<int,int>> mp;
    mp['A' - 'A'] = {-9,-9};
    mp['B' - 'A'] = {-2,-6};
    mp['C' - 'A'] = {7,-8};
    mp['D' - 'A'] = {-5,3};
    mp['E' - 'A'] = {0,-1};
    mp['F' - 'A'] = {8,-1};
    mp['G' - 'A'] = {3,3};
    mp['H' - 'A'] = {9,9};

    edges.push_back({{'A' - 'A','B' - 'A'}, 8});
    edges.push_back({{'B' - 'A','D' - 'A'}, 12});
    edges.push_back({{'B' - 'A','E' - 'A'}, 6});
    edges.push_back({{'B' - 'A','C' - 'A'}, 10});
    edges.push_back({{'E' - 'A','G' - 'A'}, 70});
    edges.push_back({{'E' - 'A','C' - 'A'}, 10});
    edges.push_back({{'C' - 'A','F' - 'A'}, 9});
    edges.push_back({{'G' - 'A','F' - 'A'}, 7});
    edges.push_back({{'G' - 'A','H' - 'A'}, 15});
    edges.push_back({{'H' - 'A','F' - 'A'}, 12});

    vector<vector<pair<int,int>>> adj(10,vector<pair<int,int>>()); // {node, path_length}
    for(pair<pair<int,int>,int> edge: edges){
        int u = edge.first.first, v = edge.first.second, w = edge.second;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }


    A_star(adj, mp, 'A' - 'A', 'H' - 'A');





}

