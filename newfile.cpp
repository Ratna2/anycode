#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool isCyclic(vector<vector<int>>& adjList, vector<bool>& visited, int node, int parent) {
    visited[node] = true;
    for (int neighbor : adjList[node]) {
        if (!visited[neighbor]) {
            if (isCyclic(adjList, visited, neighbor, node)) {
                return true;  // Found a cycle
            }
        } else if (neighbor != parent) {
            return true;  // Detected a back edge
        }
    }
    return false;
}

bool isTree(vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<bool> visited(n, false);

    // Check for cycles using DFS
    if (isCyclic(adjList, visited, 0, -1)) {
        return false;  // Graph contains a cycle
    }

    // Check if all nodes are connected
    unordered_set<int> components;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return false;  // There is an unconnected component
        }
        components.insert(i);
    }

    // Check if there is exactly one connected component
    return components.size() == 1;
}

int main() {
    vector<vector<int>> adjList = {{1, 2}, {0, 2}, {0, 1, 3}, {2, 4}, {3}};
    bool result = isTree(adjList);

    if (result) {
        cout << "The graph is a tree." << endl;
    } else {
        cout << "The graph is not a tree." << endl;
    }

    return 0;
}
