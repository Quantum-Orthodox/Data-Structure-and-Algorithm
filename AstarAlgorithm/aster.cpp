#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <limits.h> // For INT_MAX
using namespace std;

typedef pair<int, int> iPair;

class Graph {
    int V;
    vector<vector<iPair>> adj;
    map<char, int> charToIndex; // Map to convert character vertex labels to indices
    vector<char> indexToChar; // Vector to convert indices back to character vertex labels
    vector<pair<int, int>> coords; // Vector to store coordinates

public:
    Graph(int V);
    void addEdge(char u, char v, int w); // Modified to take characters
    void setCoord(char node, int x, int y); // Function to set coordinates
    void aStar(char src, char dest); // A* algorithm
    void printPath(vector<int>& pred, int destIndex); // Function to print the path
    double heuristic(int u, int v); // Heuristic function
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
    indexToChar.resize(V); // Resize the indexToChar vector
    coords.resize(V); // Resize the coords vector
}

void Graph::addEdge(char u, char v, int w) {
    if (charToIndex.find(u) == charToIndex.end()) {
        charToIndex[u] = charToIndex.size(); // Assign a new index for new characters
        indexToChar[charToIndex[u]] = u; // Assign the character to the indexToChar vector
    }
    if (charToIndex.find(v) == charToIndex.end()) {
        charToIndex[v] = charToIndex.size(); // Assign a new index for new characters
        indexToChar[charToIndex[v]] = v; // Assign the character to the indexToChar vector
    }

    int uIndex = charToIndex[u];
    int vIndex = charToIndex[v];

    adj[uIndex].push_back(make_pair(vIndex, w));
    // For undirected graph, add this line:
    adj[vIndex].push_back(make_pair(uIndex, w));
}

void Graph::setCoord(char node, int x, int y) {
    if (charToIndex.find(node) == charToIndex.end()) {
        charToIndex[node] = charToIndex.size(); // Assign a new index for new characters
        indexToChar[charToIndex[node]] = node; // Assign the character to the indexToChar vector
    }
    int index = charToIndex[node];
    coords[index] = make_pair(x, y);
}

double Graph::heuristic(int u, int v) {
    int x1 = coords[u].first, y1 = coords[u].second;
    int x2 = coords[v].first, y2 = coords[v].second;
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void Graph::aStar(char src, char dest) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    vector<double> dist(V, INT_MAX);
    vector<int> pred(V, -1); // Predecessor array
    int srcIndex = charToIndex[src];
    int destIndex = charToIndex[dest];

    pq.push(make_pair(0.0, srcIndex));
    dist[srcIndex] = 0.0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // If the destination vertex is extracted from pq, stop early
        if (u == destIndex) {
            break;
        }

        for (auto &neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            double newDist = dist[u] + weight;
            double priority = newDist + heuristic(v, destIndex);

            if (dist[v] > newDist) {
                dist[v] = newDist;
                pq.push(make_pair(priority, v));
                pred[v] = u; // Update predecessor
            }
        }
    }

    // Print the shortest distance to the destination vertex
    cout << "Shortest distance from " << src << " to " << dest << " is: " << dist[destIndex] << endl;

    // Print the path
    cout << "Path: ";
    printPath(pred, destIndex);
    cout << endl;
}

void Graph::printPath(vector<int>& pred, int destIndex) {
    if (pred[destIndex] == -1) {
        cout << indexToChar[destIndex];
        return;
    }
    printPath(pred, pred[destIndex]);
    cout << " -> " << indexToChar[destIndex];
}

// Example usage
int main() {
    const int V = 9; // Number of vertices in the graph
    Graph g(V);

    // Add edges to the graph using characters
    g.addEdge('A', 'B', 4);
    g.addEdge('B', 'H', 8);
    g.addEdge('A', 'C', 8);
    g.addEdge('B', 'C', 11);
    g.addEdge('C', 'D', 7);
    g.addEdge('C', 'I', 2);
    g.addEdge('C', 'F', 4);
    g.addEdge('D', 'E', 9);
    g.addEdge('D', 'F', 14);
    g.addEdge('E', 'F', 10);
    g.addEdge('F', 'G', 2);
    g.addEdge('G', 'H', 1);
    g.addEdge('G', 'I', 6);
    g.addEdge('H', 'I', 7);

    // Set coordinates for each node
    g.setCoord('A', 0, 0);
    g.setCoord('B', 1, 2);
    g.setCoord('C', 3, 1);
    g.setCoord('D', 4, 3);
    g.setCoord('E', 6, 4);
    g.setCoord('F', 5, 2);
    g.setCoord('G', 7, 3);
    g.setCoord('H', 5, 6);
    g.setCoord('I', 8, 1);

      // Find shortest path from 'A' to 'G'
    g.aStar('A', 'G');

    return 0;
}