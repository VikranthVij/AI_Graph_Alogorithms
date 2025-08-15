#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <climits>
using namespace std;

struct Node {
    vector<pair<string, int>> edges; // neighbor, cost
    int h; // heuristic
};

map<string, Node> graph;

struct State {
    int f; // g + h
    int g; // cost so far
    string name;
    vector<string> path;
};

struct CompareState {
    bool operator()(State a, State b) {
        return a.f > b.f;
    }
};

pair<vector<string>, int> astar(string start, string goal) {
    priority_queue<State, vector<State>, CompareState> pq;
    set<string> visited;

    State first;
    first.name = start;
    first.g = 0;
    first.f = graph[start].h;
    first.path.push_back(start);
    pq.push(first);

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.name == goal) {
            return {cur.path, cur.g};
        }

        if (visited.find(cur.name) != visited.end()) {
            continue;
        }
        visited.insert(cur.name);

        for (int i = 0; i < graph[cur.name].edges.size(); i++) {
            string nb = graph[cur.name].edges[i].first;
            int cost = graph[cur.name].edges[i].second;

            if (visited.find(nb) == visited.end()) {
                State next;
                next.name = nb;
                next.g = cur.g + cost;
                next.f = next.g + graph[nb].h;
                next.path = cur.path;
                next.path.push_back(nb);
                pq.push(next);
            }
        }
    }

    return {{}, INT_MAX};
}

int main() {
    // Hardcoded graph
    graph["A"].edges = {{"B", 1}, {"C", 3}};
    graph["A"].h = 4;

    graph["B"].edges = {{"A", 1}, {"D", 2}, {"E", 5}};
    graph["B"].h = 2;

    graph["C"].edges = {{"A", 3}, {"F", 4}};
    graph["C"].h = 3;

    graph["D"].edges = {{"B", 2}, {"G", 6}};
    graph["D"].h = 0;

    graph["E"].edges = {{"B", 5}, {"G", 2}};
    graph["E"].h = 0;

    graph["F"].edges = {{"C", 4}, {"G", 1}};
    graph["F"].h = 0;

    graph["G"].edges = {{"D", 6}, {"E", 2}, {"F", 1}};
    graph["G"].h = 0;

    auto result = astar("A", "G");

    cout << "Path: ";
    for (int i = 0; i < result.first.size(); i++) {
        cout << result.first[i] << " ";
    }
    cout << "\nCost: " << result.second << "\n";

    return 0;
}
