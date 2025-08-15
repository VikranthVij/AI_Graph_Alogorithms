#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> adj;
map<char, int> nameToId;
vector<char> idToName;

void bfs(int src, int dst) {
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<int> q;

    visited[src] = true;
    q.push(src);

    cout << "\nStarting BFS (lexicographical order):\n\n";

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << "Visiting: " << idToName[u] << "\n";

        if (u == dst) {
            cout << "\nGoal found! Path: ";
            vector<int> path;
            for (int cur = dst; cur != -1; cur = parent[cur]) {
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());
            for (int i = 0; i < path.size(); i++) {
                if (i > 0) cout << " ";
                cout << idToName[path[i]];
            }
            cout << "\n";
            return;
        }

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    cout << "\nNo path found from " << idToName[src] << " to " << idToName[dst] << "\n";
}

int main() {
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;
    adj.assign(n, {});
    idToName.resize(n);

    cout << "Enter node labels (e.g., A B C ...):\n";
    for (int i = 0; i < n; i++) {
        char label;
        cin >> label;
        nameToId[label] = i;
        idToName[i] = label;
    }

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < m; i++) {
        char a, b;
        cin >> a >> b;
        int u = nameToId[a];
        int v = nameToId[b];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    char srcLabel, dstLabel;
    cout << "Enter source and goal: ";
    cin >> srcLabel >> dstLabel;
    int src = nameToId[srcLabel];
    int dst = nameToId[dstLabel];

    // Sort adjacency for lexicographical BFS
    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end(), [&](int a, int b) {
            return idToName[a] < idToName[b];
        });
    }

    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        cout << idToName[i] << ": ";
        for (int v : adj[i]) cout << idToName[v] << " ";
        cout << "\n";
    }

    bfs(src, dst);

    return 0;
}
