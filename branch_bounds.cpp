#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

// Graph representation
struct Edge {
    string to;
    int cost;
};

struct Node {
    vector<Edge> edges;
};

map<string, Node> graph;

// Branch and Bound search
pair<vector<string>, int> branchAndBound(const string& start, const string& goal) {
    typedef pair<int, vector<string>> PathState; // cost, path
    priority_queue<PathState, vector<PathState>, greater<PathState>> pq;

    pq.push({0, {start}});
    int bestCost = numeric_limits<int>::max();
    vector<string> bestPath;

    while (!pq.empty()) {
        auto [cost, path] = pq.top();
        pq.pop();

        string curr = path.back();

        if (curr == goal) {
            if (cost < bestCost) {
                bestCost = cost;
                bestPath = path;
            }
            continue;
        }

        for (auto &edge : graph[curr].edges) {
            if (find(path.begin(), path.end(), edge.to) == path.end()) {
                if (cost + edge.cost < bestCost) {
                    vector<string> newPath = path;
                    newPath.push_back(edge.to);
                    pq.push({cost + edge.cost, newPath});
                }
            }
        }
    }

    return {bestPath, bestCost};
}

int main() {
    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges in format: from to cost\n";
    for (int i = 0; i < e; i++) {
        string u, v;
        int cost;
        cin >> u >> v >> cost;
        graph[u].edges.push_back({v, cost});
    }

    string start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    auto result = branchAndBound(start, goal);

    if (result.second == numeric_limits<int>::max()) {
        cout << "\nNo path found from " << start << " to " << goal << "\n";
    } else {
        cout << "\nBest path: ";
        for (size_t i = 0; i < result.first.size(); i++) {
            cout << result.first[i];
            if (i + 1 < result.first.size()) cout << " -> ";
        }
        cout << "\nCost: " << result.second << endl;
    }

    return 0;
}
