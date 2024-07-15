#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <map>
#include <limits.h> // For INT_MAX
using namespace std;

typedef pair<int, int> iPair;

class Graph {
    int V;
    vector<vector<iPair>> adj;
    map<char, int> charToIndex; // Map to convert character vertex labels to indices
    vector<char> indexToChar; // Vector to convert indices back to character vertex labels

public:
    Graph(int V);
    void addEdge(char u, char v, int w); // Modified to take characters
    void dijkstra(char src, char dest); // Modified to find shortest path to destination
    void printPath(vector<int>& pred, int destIndex); // Function to print the path
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
    indexToChar.resize(V); // Resize the indexToChar vector
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

void Graph::dijkstra(char src, char dest) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> dist(V, INT_MAX);
    vector<int> pred(V, -1); // Predecessor array
    int srcIndex = charToIndex[src];
    int destIndex = charToIndex[dest];

    pq.push(make_pair(0, srcIndex));
    dist[srcIndex] = 0;

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

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
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

int main() {
    int V = 9; // Number of vertices in the graph
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

    // Find shortest path from 'A' to 'G'
    g.dijkstra('A', 'G');

    return 0;
}
