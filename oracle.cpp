#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <string>
using namespace std;

string oracle(
    char start, char goal,
    unordered_map<char, vector<pair<char, int>>> &graph,
    unordered_map<char, int> &heuristic
) {
    typedef pair<int, string> PQItem;
    priority_queue<PQItem, vector<PQItem>, greater<PQItem>> pq;

    pq.push(make_pair(heuristic[start], string(1, start)));

    while (!pq.empty()) {
        PQItem current = pq.top();
        pq.pop();
        char lastNode = current.second.back();

        if (lastNode == goal)
            return current.second;

        int gCost = 0;
        for (size_t i = 0; i + 1 < current.second.size(); i++) {
            char u = current.second[i];
            char v = current.second[i + 1];
            for (size_t j = 0; j < graph[u].size(); j++) {
                if (graph[u][j].first == v) {
                    gCost += graph[u][j].second;
                    break;
                }
            }
        }

        for (size_t i = 0; i < graph[lastNode].size(); i++) {
            char nextNode = graph[lastNode][i].first;
            int edgeCost = graph[lastNode][i].second;

            if (current.second.find(nextNode) != string::npos) 
                continue;

            int gNew = gCost + edgeCost;
            int fNew = gNew + heuristic[nextNode];
            pq.push(make_pair(fNew, current.second + nextNode));
        }
    }
    return "";
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph;
    unordered_map<char, int> heuristic;

    int edges;
    cout << "Enter number of edges: ";
    cin >> edges;
    cout << "Enter edges in format: from to cost\n";
    for (int i = 0; i < edges; i++) {
        char u, v;
        int cost;
        cin >> u >> v >> cost;
        graph[u].push_back(make_pair(v, cost));
        if (graph.find(v) == graph.end())
            graph[v] = vector<pair<char, int>>(); // ensure v exists in map
    }

    int heurCount;
    cout << "Enter number of heuristic entries: ";
    cin >> heurCount;
    cout << "Enter heuristics in format: node value\n";
    for (int i = 0; i < heurCount; i++) {
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

    string path = oracle(start, goal, graph, heuristic);

    if (!path.empty())
        cout << "Route located: " << path << "\n";
    else
        cout << "No route available.\n";

    return 0;
}
