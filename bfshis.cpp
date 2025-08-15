#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
using namespace std;

void BFSHis(char start, char goal, unordered_map<char, vector<char>> &graph) {
    unordered_map<char, bool> visited;
    unordered_map<char, char> parent;

    for (auto &node : graph) {
        visited[node.first] = false;
        parent[node.first] = '\0';
    }

    queue<char> q;
    visited[start] = true;
    q.push(start);
    bool found = false;

    cout << "Traversal: ";

    while (!q.empty()) {
        int levelSize = q.size();
        vector<char> currentLevel;

        for (int i = 0; i < levelSize; i++) {
            currentLevel.push_back(q.front());
            q.pop();
        }

        sort(currentLevel.begin(), currentLevel.end()); // lexicographic order

        for (auto &node : currentLevel) {
            cout << node << " ";

            if (node == goal) {
                found = true;
                break;
            }

            for (auto &nbr : graph[node]) {
                if (!visited[nbr]) {
                    visited[nbr] = true;
                    parent[nbr] = node;
                    q.push(nbr);
                }
            }
        }

        if (found) break;
    }

    if (found) {
        stack<char> path;
        for (char v = goal; v != '\0'; v = parent[v]) {
            path.push(v);
        }

        cout << "\nPath from " << start << " to " << goal << ": ";
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nNo path found from " << start << " to " << goal << endl;
    }
}

int main() {
    unordered_map<char, vector<char>> graph;
    int edges;
    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (e.g., S A for S->A):\n";
    for (int i = 0; i < edges; i++) {
        char u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected graph
    }

    char start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    BFSHis(start, goal, graph);
    return 0;
}
