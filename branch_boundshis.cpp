#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

unordered_map<char, vector<pair<char, int>>> ntwrk;
unordered_map<char, int> heuristic;
bool found = false;

struct Node {
    int cost;
    string path;
    vector<char> visited;
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

void branchAndBoundHistory(char start, char goal) {
    priority_queue<Node, vector<Node>, greater<>> pq;
    pq.push({heuristic[start], string(1, start), {start}});

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        char last = current.path.back();

        // Print traversal history
        cout << "Visiting: " << last << " (Estimated Cost: " << current.cost << ")\n";

        if (last == goal) {
            found = true;
            cout << "Path found: ";
            for (size_t i = 0; i < current.path.size(); i++) {
                cout << current.path[i];
                if (i != current.path.size() - 1) cout << " -> ";
            }
            cout << " | Total Estimated Cost: " << current.cost << "\n\n";
            continue;
        }

        int actualCostSoFar = 0;
        for (size_t i = 0; i < current.path.size() - 1; i++) {
            char u = current.path[i];
            char v = current.path[i + 1];
            for (auto& [n, c] : ntwrk[u]) {
                if (n == v) {
                    actualCostSoFar += c;
                    break;
                }
            }
        }

        for (auto& [next, c] : ntwrk[last]) {
            if (find(current.visited.begin(), current.visited.end(), next) == current.visited.end()) {
                vector<char> newVisited = current.visited;
                newVisited.push_back(next);
                int newCost = actualCostSoFar + c + heuristic[next];
                pq.push({newCost, current.path + next, newVisited});
            }
        }
    }
}

int main() {
    int nodes, edges;
    cout << "Enter number of nodes: ";
    cin >> nodes;
    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges in format: from to cost\n";
    for (int i = 0; i < edges; i++) {
        char u, v;
        int c;
        cin >> u >> v >> c;
        ntwrk[u].push_back({v, c});
        if (!ntwrk.count(v)) ntwrk[v] = {}; // Ensure every node exists in map
    }

    cout << "Enter heuristic values (node value):\n";
    for (int i = 0; i < nodes; i++) {
        char node;
        int h;
        cin >> node >> h;
        heuristic[node] = h;
    }

    char start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    branchAndBoundHistory(start, goal);

    if (!found) cout << "No route exists.\n";
    return 0;
}
