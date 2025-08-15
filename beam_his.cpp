#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

unordered_map<char, vector<char>> ntwrk;
unordered_map<char, int> heuristic;
bool found = false;

void beamSearchWithHistory(char start, char goal, int beamWidth) {
    vector<string> frontier = {string(1, start)};
    unordered_set<char> visited;

    cout << "\nTraversal Order (Beam Search):\n";

    while (!frontier.empty()) {
        vector<string> newFrontier;

        for (auto &path : frontier) {
            char last = path.back();
            visited.insert(last);

            cout << last << " (Heuristic: " << heuristic[last] << ")\n";

            if (last == goal) {
                found = true;
                cout << "\nBest path found: ";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << path[i];
                    if (i != path.size() - 1) cout << " -> ";
                }
                cout << "\n";
            }

            for (char next : ntwrk[last]) {
                if (!visited.count(next) && path.find(next) == string::npos) {
                    newFrontier.push_back(path + next);
                }
            }
        }

        sort(newFrontier.begin(), newFrontier.end(),
             [&](const string &a, const string &b) {
                 return heuristic[a.back()] < heuristic[b.back()];
             });

        if ((int)newFrontier.size() > beamWidth)
            newFrontier.resize(beamWidth);

        frontier = newFrontier;
    }
}

int main() {
    int edges;
    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges in format: from to\n";
    for (int i = 0; i < edges; i++) {
        char u, v;
        cin >> u >> v;
        ntwrk[u].push_back(v);
        if (!ntwrk.count(v)) ntwrk[v] = {};
    }

    int nodes;
    cout << "Enter number of nodes: ";
    cin >> nodes;

    cout << "Enter heuristic values (node h-value):\n";
    for (int i = 0; i < nodes; i++) {
        char node;
        int h;
        cin >> node >> h;
        heuristic[node] = h;
    }

    char start, goal;
    int beamWidth;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;
    cout << "Enter beam width: ";
    cin >> beamWidth;

    beamSearchWithHistory(start, goal, beamWidth);

    if (!found) cout << "\nNo route exists.\n";
    return 0;
}
