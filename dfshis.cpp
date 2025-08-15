#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int charToIndex(char c) {
    return c - 'a'; // 'a' -> 0, 'b' -> 1, etc.
}

void DFSHis(vector<vector<int>>& adj, int start, int goal) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    stack<int> s;
    s.push(start);
    visited[start] = true;

    bool found = false;
    cout << "Traversal: " << char('a' + start) << " ";

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (node == goal) {
            found = true;
            break;
        }

        vector<int> children;
        for (int j = 0; j < n; j++) {
            if (adj[node][j] == 1 && !visited[j]) {
                children.push_back(j);
            }
        }

        sort(children.rbegin(), children.rend());

        for (int c : children) {
            if (!visited[c]) {
                visited[c] = true;
                parent[c] = node;
                s.push(c);
                cout << char('a' + c) << " ";
            }
        }
    }

    if (found) {
        stack<int> path;
        for (int v = goal; v != -1; v = parent[v]) {
            path.push(v);
        }

        cout << "\nPath from " << char('a' + start) << " to " << char('a' + goal) << ": ";
        while (!path.empty()) {
            cout << char('a' + path.top()) << " ";
            path.pop();
        }
        cout << endl;
    } else {
        cout << "\nNo path found.\n";
    }
}

int main() {
    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n, 0));

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges (a b):\n";
    for (int i = 0; i < e; i++) {
        char u, v;
        cin >> u >> v;
        int ui = charToIndex(u);
        int vi = charToIndex(v);
        adj[ui][vi] = 1;
        adj[vi][ui] = 1;
    }

    char startChar, goalChar;
    cout << "Enter start node: ";
    cin >> startChar;
    cout << "Enter goal node: ";
    cin >> goalChar;

    DFSHis(adj, charToIndex(startChar), charToIndex(goalChar));

    return 0;
}
