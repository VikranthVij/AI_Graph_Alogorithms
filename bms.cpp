#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int nodeCount, edgeCount;
vector<vector<int>> graphAdj;
vector<int> curPath;
vector<int> visited;
map<char, int> nameToId;
vector<char> idToName;
int totalPaths = 0;

void bmsDFS(int u, int goal) {
    // Debug: show progress
    cout << "Visiting: " << idToName[u] << " | Path so far: ";
    for (int x : curPath) cout << idToName[x] << " ";
    cout << "\n";

    if (u == goal) {
        totalPaths++;
        cout << "Path " << totalPaths << ": ";
        for (int i = 0; i < curPath.size(); i++) {
            if (i > 0) cout << " ";
            cout << idToName[curPath[i]];
        }
        cout << "\n\n";
        return;
    }

    for (int v : graphAdj[u]) {
        if (!visited[v]) {
            visited[v] = 1;
            curPath.push_back(v);
            bmsDFS(v, goal);
            curPath.pop_back();
            visited[v] = 0;
        }
    }
}

int main() {
    cout << "Enter number of nodes and edges: ";
    cin >> nodeCount >> edgeCount;
    graphAdj.assign(nodeCount, {});

    idToName.resize(nodeCount);

    cout << "Enter node labels (e.g., A B C ...):\n";
    for (int i = 0; i < nodeCount; i++) {
        char label;
        cin >> label;
        nameToId[label] = i;
        idToName[i] = label;
    }

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edgeCount; i++) {
        char a, b;
        cin >> a >> b;
        int u = nameToId[a];
        int v = nameToId[b];
        graphAdj[u].push_back(v);
        graphAdj[v].push_back(u);
    }

    char srcLabel, destLabel;
    cout << "Enter source and goal: ";
    cin >> srcLabel >> destLabel;
    int src = nameToId[srcLabel];
    int dest = nameToId[destLabel];

    // Sort neighbors alphabetically by label
    for (int i = 0; i < nodeCount; i++) {
        sort(graphAdj[i].begin(), graphAdj[i].end(), [&](int a, int b) {
            return idToName[a] < idToName[b];
        });
    }

    cout << "\nAdjacency List:\n";
    for (int i = 0; i < nodeCount; i++) {
        cout << idToName[i] << ": ";
        for (int v : graphAdj[i]) cout << idToName[v] << " ";
        cout << "\n";
    }

    cout << "\nStarting British Museum Search...\n\n";

    visited.assign(nodeCount, 0);
    curPath.clear();
    curPath.push_back(src);
    visited[src] = 1;

    bmsDFS(src, dest);

    if (totalPaths == 0) {
        cout << "No path found from " << srcLabel << " to " << destLabel << "\n";
    } else {
        cout << "\nTotal paths found: " << totalPaths << "\n";
    }

    return 0;
}
