#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

unordered_map<char, vector<char>> ntwrk;
unordered_map<char, int> heuristic;
bool found = false;

void beamSearch(char start, char goal, int beamWidth) {
    vector<string> frontier = {string(1, start)};

    while (!frontier.empty()) {
        vector<string> newFrontier;

        for (size_t i = 0; i < frontier.size(); i++) {
            string path = frontier[i];
            char last = path.back();

            if (last == goal) {
                found = true;
                for (size_t k = 0; k < path.size(); k++) {
                    cout << path[k];
                    if (k != path.size() - 1) cout << " -> ";
                }
                cout << "\n";
            }

            for (size_t j = 0; j < ntwrk[last].size(); j++) {
                char next = ntwrk[last][j];
                if (path.find(next) == string::npos) {
                    newFrontier.push_back(path + next);
                }
            }
        }

        sort(newFrontier.begin(), newFrontier.end(),
             [](const string& a, const string& b) {
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
        if (ntwrk.find(v) == ntwrk.end())
            ntwrk[v] = vector<char>(); // ensure v exists
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
    int beamWidth;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;
    cout << "Enter beam width: ";
    cin >> beamWidth;

    beamSearch(start, goal, beamWidth);

    if (!found) cout << "No route exists.\n";
    return 0;
}
