#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<char, vector<char>> network;
bool foundPath = false;

void dfsPaths(string path, char goal) {
    char current = path.back();

    if (current == goal) {
        foundPath = true;
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\n";
        return;
    }

    for (char next : network[current]) {
        if (path.find(next) == string::npos) {
            dfsPaths(path + next, goal);
        }
    }
}

int main() {
    // New hardcoded network
    network['P'] = {'Q', 'R'};
    network['Q'] = {'S', 'T'};
    network['R'] = {'T', 'U'};
    network['S'] = {'V'};
    network['T'] = {'V', 'W'};
    network['U'] = {'W'};
    network['V'] = {};
    network['W'] = {};

    char start = 'P';
    char goal = 'W';

    cout << "All paths from " << start << " to " << goal << ":\n";
    dfsPaths(string(1, start), goal);

    if (!foundPath) cout << "No route exists.\n";

    return 0;
}
