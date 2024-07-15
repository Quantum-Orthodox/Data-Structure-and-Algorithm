// (O(V log V) on each enqueue):
// class MinBinaryHeap {
//   constructor(options) {
//     this.elements = [];
//     this.priority = options.priority;
//   }

//   enqueue(element) {
//     this.elements.push(element);
//     this.elements.sort((a, b) => this.priority(a) - this.priority(b));
//   }

//   dequeue() {
//     return this.elements.shift();
//   }

//   isEmpty() {
//     return this.elements.length === 0;
//   }
// }

// O(log V) operations for both enqueue and dequeue:
class MinBinaryHeap {
  constructor() {
    this.heap = [];
  }

  enqueue(element) {
    this.heap.push(element);
    this.bubbleUp(this.heap.length - 1);
  }

  dequeue() {
    const min = this.heap[0];
    const last = this.heap.pop();
    if (this.heap.length > 0) {
      this.heap[0] = last;
      this.sinkDown(0);
    }
    return min;
  }

  isEmpty() {
    return this.heap.length === 0;
  }

  bubbleUp(index) {
    let current = index;
    while (current > 0) {
      const parent = Math.floor((current - 1) / 2);
      if (this.heap[parent][0] <= this.heap[current][0]) break;
      [this.heap[parent], this.heap[current]] = [
        this.heap[current],
        this.heap[parent],
      ];
      current = parent;
    }
  }

  sinkDown(index) {
    let current = index;
    const length = this.heap.length;
    while (true) {
      let leftChild = 2 * current + 1;
      let rightChild = 2 * current + 2;
      let smallest = current;
      if (
        leftChild < length &&
        this.heap[leftChild][0] < this.heap[smallest][0]
      ) {
        smallest = leftChild;
      }
      if (
        rightChild < length &&
        this.heap[rightChild][0] < this.heap[smallest][0]
      ) {
        smallest = rightChild;
      }
      if (smallest === current) break;
      [this.heap[current], this.heap[smallest]] = [
        this.heap[smallest],
        this.heap[current],
      ];
      current = smallest;
    }
  }
}

class Graph {
  constructor(V) {
    this.V = V;
    this.adj = Array.from({ length: V }, () => []);
    this.charToIndex = new Map(); // Map to convert character vertex labels to indices
    this.indexToChar = Array(V).fill(null); // Array to convert indices back to character vertex labels
  }

  addEdge(u, v, w) {
    if (!this.charToIndex.has(u)) {
      this.charToIndex.set(u, this.charToIndex.size);
      this.indexToChar[this.charToIndex.get(u)] = u;
    }
    if (!this.charToIndex.has(v)) {
      this.charToIndex.set(v, this.charToIndex.size);
      this.indexToChar[this.charToIndex.get(v)] = v;
    }

    const uIndex = this.charToIndex.get(u);
    const vIndex = this.charToIndex.get(v);

    this.adj[uIndex].push({ node: vIndex, weight: w });
    // For undirected graph, add this line:
    this.adj[vIndex].push({ node: uIndex, weight: w });
  }

  dijkstra(src, dest) {
    const pq = new MinBinaryHeap({ priority: (x) => x[0] });
    const dist = Array(this.V).fill(Infinity);
    const pred = Array(this.V).fill(-1); // Predecessor array
    const srcIndex = this.charToIndex.get(src);
    const destIndex = this.charToIndex.get(dest);

    pq.enqueue([0, srcIndex]);
    dist[srcIndex] = 0;

    while (!pq.isEmpty()) {
      const [distance, u] = pq.dequeue();

      // If the destination vertex is extracted from pq, stop early
      if (u === destIndex) {
        break;
      }

      for (const neighbor of this.adj[u]) {
        const { node: v, weight } = neighbor;

        if (dist[v] > dist[u] + weight) {
          dist[v] = dist[u] + weight;
          pq.enqueue([dist[v], v]);
          pred[v] = u; // Update predecessor
        }
      }
    }

    // Print the shortest distance to the destination vertex
    console.log(
      `Shortest distance from ${src} to ${dest} is: ${dist[destIndex]}`,
    );

    // Print the path
    console.log(`Path: `);
    this.printPath(pred, destIndex);
  }

  printPath(pred, destIndex) {
    if (pred[destIndex] === -1) {
      process.stdout.write(this.indexToChar[destIndex]);
      return;
    }
    this.printPath(pred, pred[destIndex]);
    process.stdout.write(` -> ${this.indexToChar[destIndex]}`);
  }
}

// Example usage
const V = 9; // Number of vertices in the graph
const g = new Graph(V);

// Add edges to the graph using characters
g.addEdge("A", "B", 4);
g.addEdge("B", "H", 8);
g.addEdge("A", "C", 8);
g.addEdge("B", "C", 11);
g.addEdge("C", "D", 7);
g.addEdge("C", "I", 2);
g.addEdge("C", "F", 4);
g.addEdge("D", "E", 9);
g.addEdge("D", "F", 14);
g.addEdge("E", "F", 10);
g.addEdge("F", "G", 2);
g.addEdge("G", "H", 1);
g.addEdge("G", "I", 6);
g.addEdge("H", "I", 7);

// Find shortest path from 'A' to 'G'
g.dijkstra("A", "G");
