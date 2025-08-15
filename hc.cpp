#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int hillClimb(int start, int goal,
              vector<vector<pair<int,int>>> &graph,
              vector<int> &heuristic,
              vector<char> &idToChar) {
    int current = start;
    vector<int> path = {current};

    cout << "Starting at: " << idToChar[current]
         << " (Heuristic: " << heuristic[current] << ")\n";

    while (current != goal) {
        int bestNeighbor = -1;
        int bestHeuristic = heuristic[current];

        cout << "Checking neighbors of " << idToChar[current] << ":\n";
        for (auto &edge : graph[current]) {
            int next = edge.first;
            cout << "  " << idToChar[next]
                 << " (Heuristic: " << heuristic[next] << ")\n";
            if (heuristic[next] < bestHeuristic) {
                bestHeuristic = heuristic[next];
                bestNeighbor = next;
            }
        }

        if (bestNeighbor == -1) { // No better neighbor
            cout << "No neighbor has a better heuristic. Stuck at local optimum.\n";
            break;
        }

        current = bestNeighbor;
        path.push_back(current);
        cout << "Moving to: " << idToChar[current]
             << " (Heuristic: " << heuristic[current] << ")\n";
    }

    cout << "\nPath taken: ";
    for (int node : path) cout << idToChar[node] << " ";
    cout << "\n";

    if (current == goal) {
        cout << "✅ Goal reached successfully!\n";
    } else {
        cout << "❌ Goal not reached.\n";
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    unordered_map<char, int> charToId;
    vector<char> idToChar(n);
    vector<vector<pair<int,int>>> graph(n);

    cout << "Enter node labels:\n";
    for (int i = 0; i < n; i++) {
        char label;
        cin >> label;
        charToId[label] = i;
        idToChar[i] = label;
    }

    cout << "Enter " << m << " edges (u v cost):\n";
    for (int i = 0; i < m; i++) {
        char cu, cv;
        int cost;
        cin >> cu >> cv >> cost;
        int u = charToId[cu];
        int v = charToId[cv];
        graph[u].push_back({v, cost});
        // hill climbing doesn't require undirected necessarily, but you can uncomment for undirected:
        // graph[v].push_back({u, cost});
    }

    vector<int> heuristic(n);
    cout << "Enter heuristic values for each node:\n";
    for (int i = 0; i < n; i++) {
        cout << idToChar[i] << ": ";
        cin >> heuristic[i];
    }

    char sLabel, gLabel;
    cout << "Enter start and goal nodes: ";
    cin >> sLabel >> gLabel;
    int start = charToId[sLabel];
    int goal = charToId[gLabel];

    cout << "\n--- Hill Climbing Search ---\n";
    hillClimb(start, goal, graph, heuristic, idToChar);

    return 0;
}
