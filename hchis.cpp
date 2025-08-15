#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

int hillClimbWithHistory(int start, int goal,
                         vector<vector<pair<int,int>>> &graph,
                         vector<int> &heuristic,
                         vector<string> &nodeNames) {
    int current = start;
    vector<int> path = {current};
    vector<bool> visited(graph.size(), false);
    visited[current] = true;

    cout << "\nTraversal Order (Hill Climbing with History):\n";
    cout << nodeNames[current] << " (Heuristic: " << heuristic[current] << ")\n";

    while (current != goal) {
        int bestNeighbor = -1;
        int bestHeuristic = heuristic[current];

        for (auto &edge : graph[current]) {
            int next = edge.first;
            if (!visited[next] && heuristic[next] < bestHeuristic) {
                bestHeuristic = heuristic[next];
                bestNeighbor = next;
            }
        }

        if (bestNeighbor == -1) {
            cout << "No better unvisited neighbor found. Stopping.\n";
            break;
        }

        current = bestNeighbor;
        visited[current] = true;
        path.push_back(current);

        cout << nodeNames[current] << " (Heuristic: " << heuristic[current] << ")\n";
    }

    cout << "\nBest path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << nodeNames[path[i]];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n";

    if (current == goal) {
        cout << "Goal reached successfully!\n";
    } else {
        cout << "Goal not reached.\n";
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<string> nodeNames(n);
    cout << "Enter node names:\n";
    for (int i = 0; i < n; i++) {
        cin >> nodeNames[i];
    }

    vector<vector<pair<int,int>>> graph(n);
    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges (from to cost):\n";
    for (int i = 0; i < e; i++) {
        string from, to;
        int cost;
        cin >> from >> to >> cost;

        int u = -1, v = -1;
        for (int j = 0; j < n; j++) {
            if (nodeNames[j] == from) u = j;
            if (nodeNames[j] == to) v = j;
        }
        if (u != -1 && v != -1) {
            graph[u].push_back({v, cost});
        }
    }

    vector<int> heuristic(n);
    cout << "Enter heuristic values for each node:\n";
    for (int i = 0; i < n; i++) {
        cout << nodeNames[i] << ": ";
        cin >> heuristic[i];
    }

    string startName, goalName;
    cout << "Enter start node: ";
    cin >> startName;
    cout << "Enter goal node: ";
    cin >> goalName;

    int start = -1, goal = -1;
    for (int i = 0; i < n; i++) {
        if (nodeNames[i] == startName) start = i;
        if (nodeNames[i] == goalName) goal = i;
    }

    if (start == -1 || goal == -1) {
        cout << "Invalid start or goal node.\n";
        return 1;
    }

    hillClimbWithHistory(start, goal, graph, heuristic, nodeNames);

    return 0;
}
