#include<bits/stdc++.h>
using namespace std;

void printPath(vector<vector<pair<int,int>>>& adj, vector<int>& parent,int source, int goal){
    while(goal != source){
        cout<<(char)(goal + 'A')<<"<-";
         goal = parent[goal];
    }
    cout<<(char)(source + 'A')<<endl;
}

int dijkstra(vector<vector<pair<int,int>>>& adj, int source, int goal){
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
            return distance;
        }

        for(pair<int,int> np: adj[node]){
            int adjNode = np.first, adjDistance = np.second;
            if(dist[adjNode] > dist[node] + adjDistance){
                dist[adjNode] = dist[node] + adjDistance;
                parent[adjNode] = node;
                pq.push({dist[adjNode], adjNode});
            }
            
        }
    }

    return INT_MAX;
}

int main(){
    vector<pair<pair<char,char>,int>> edges;
    int edgeCount = 10;
    edges.push_back({{'A','B'}, 5});
    edges.push_back({{'A','D'}, 3});
    edges.push_back({{'D','E'}, 2});
    edges.push_back({{'D','F'}, 2});
    edges.push_back({{'F','G'}, 3});
    edges.push_back({{'G','E'}, 4});
    edges.push_back({{'E','B'}, 4});
    edges.push_back({{'B','C'}, 1});
    edges.push_back({{'C','G'}, 8});
    edges.push_back({{'C','E'}, 6});


    vector<vector<pair<int,int>>> adj(7,vector<pair<int,int>>());

    for(pair<pair<int,int>,int> edge: edges){
        int u = edge.first.first - 'A', v = edge.first.second - 'A', w = edge.second;
        adj[u].push_back({v,w});
    }

    int source = 'A' - 'A';
    int goal = 'G' - 'A';
    cout<<endl<<endl<<dijkstra(adj, source, goal);
}