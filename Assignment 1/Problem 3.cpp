#include<bits/stdc++.h>
using namespace std;

void iterative_deepening_dfs(vector<vector<int>>& adj, int source, int goal) {
    int n = adj.size();
    int mxDepth;
    vector<int> visited(n, false);
    bool goalFound = false;
    function<void(vector<vector<int>>&, int, int, int)> dfs = [&](vector<vector<int>>& adj, int node, int goal, int depth) {
        if (goalFound) return;
        if (depth > mxDepth) return;

        cout << char(node + 'A') << " ";
        if (node == goal) {
            goalFound = true;
            return;
        }

        for (int adjNode : adj[node]) {
            if (visited[adjNode]) continue;
            visited[adjNode] = true;
            dfs(adj, adjNode, goal, depth + 1);
        }
    };

    for (int d = 0; d <= 3; d++) {
        mxDepth = d;
        goalFound = false;
        visited = vector<int>(n, false);
        visited[source] = true;
        dfs(adj, source, goal, 0);
        cout << endl << endl;
    }
}

int main() {
    vector<pair<int, int>> edges;

    

    edges.push_back({'A', 'B'});
    edges.push_back({'A', 'C'});
    edges.push_back({'B', 'D'});
    edges.push_back({'B', 'E'});
    edges.push_back({'C', 'F'});
    edges.push_back({'C', 'G'});
    edges.push_back({'C', 'H'});
    edges.push_back({'D', 'I'});
    edges.push_back({'D', 'J'});
    edges.push_back({'E', 'K'});
    edges.push_back({'E', 'L'});
    edges.push_back({'E', 'M'});
    edges.push_back({'F', 'N'});
    edges.push_back({'H', 'O'});
    edges.push_back({'H', 'P'});

    vector<vector<int>> adjacencyList(100, vector<int>());

    for (pair<int, int> edge : edges) {
        int u = edge.first - 'A';
        int v = edge.second - 'A';
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    iterative_deepening_dfs(adjacencyList, 0, 13);

    return 0;
}
