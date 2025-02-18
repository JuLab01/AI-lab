#include<bits/stdc++.h>
using namespace std;


void dfs(vector<vector<int>>& adj, int source, int goal){
    unordered_map<int, bool> visited;
    bool isGoalFound = false;
    vector<int> path;

    function<void(vector<vector<int>>&, int, int)> dfs_implementation = [&](vector<vector<int>>& adj, int source, int goal){
        if(source == goal){
            path.push_back(goal);
            isGoalFound = true;
            cout<<endl<<source<<" ";
            cout<<"goal is found"<<endl;
            return;
        }

        

        cout<<source<<" ";
        visited[source] = true;

        if(!isGoalFound){
            path.push_back(source);
        }

        for(int i: adj[source]){
            if(visited[i]) continue;
            dfs_implementation(adj, i, goal);
        }

        if(!isGoalFound){
            path.pop_back();
        }
    };


    dfs_implementation(adj, source, goal);


    cout<<"\n\n\n";
    for(int i = 0;i<path.size()-1;i++){
        cout<<path[i]<<"->";
    }
    cout<<goal<<endl;
}

void bfs(vector<vector<int>>& adj, int source, int goal){
    queue<int> q;
    unordered_map<int, bool> visited;
    vector<int> path;

    q.push(source);
    visited[source] = true;
    while(!q.empty()){
        int node = q.front();
        q.pop();

        cout<<node<<" ";
        visited[node] = true;
        if(node == goal){
            cout<<endl<<node<<" ";
            cout<<"goal is found"<<endl;
            break;
        }

        for(int adjNode: adj[node]){
            if(visited[adjNode]) continue;
            q.push(adjNode);
        }
    }


}

void itterative_dfs(vector<vector<int>>& adj, int source, int goal){
    stack<int> q;
    unordered_map<int, bool> visited;
    vector<int> path;

    q.push(source);
    visited[source] = true;
    while(!q.empty()){
        int node = q.top();
        q.pop();

        cout<<node<<" ";
        visited[node] = true;
        if(node == goal){
            cout<<endl<<node<<" ";
            cout<<"goal is found"<<endl;
            break;
        }

        for(reverse_iterator<std::vector<int>::iterator> it = adj[node].rbegin(); it != adj[node].rend(); ++it){
            int adjNode = *it;
            if(visited[adjNode]) continue;
            q.push(adjNode);
        }
    }
}



int main(){

    vector<pair<int,int>> edges;


    function<void()> inputEdges = [&](){
    
        int edgeCount = 0;
        cout<<"Enter the number of edges: ";
        cin>>edgeCount;
        for(int i = 0; i < edgeCount; i++){
            int u, v;
            cin>>u>>v;
            edges.push_back({u,v});
        }

    };

    edges.push_back({1,8});
    edges.push_back({1,5});
    edges.push_back({1,2});
    edges.push_back({2,9});
    edges.push_back({8,6});
    edges.push_back({8,4});
    edges.push_back({8,3});
    edges.push_back({6,10});
    edges.push_back({6,7});
    

    vector<vector<int>> adjacencyList(11,vector<int>());

    for(pair<int,int> edge: edges){
        int u = edge.first;
        int v = edge.second;
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }


    // for(int i = 0; i < adjacencyList.size(); i++){
    //     for(int j = 0; j < adjacencyList[i].size(); j++){
    //         cout<<adjacencyList[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    itterative_dfs(adjacencyList, 1, 3);

    

    return 0;
}