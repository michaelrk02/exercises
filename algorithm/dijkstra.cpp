#include <iostream>
#include <vector>

#define DUMP(_X) std::cout << #_X << ": " << (_X) << std::endl

struct Graph {
    int *data;
    int vertices;

    Graph(int vertices);
    ~Graph(void);

    int get(int a, int b);
    void put(int a, int b, int w);
};

Graph::Graph(int vertices) {
    this->data = new int[vertices * vertices];
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            this->data[i * vertices + j] = 0;
        }
    }

    this->vertices = vertices;
}

Graph::~Graph(void) {
    delete this->data;
}

int Graph::get(int a, int b) {
    return this->data[b * this->vertices + a];
}

void Graph::put(int a, int b, int w) {
    this->data[a * this->vertices + b] = w;
    this->data[b * this->vertices + a] = w;
}

int main() {
    // construct a graph
    Graph graph(6);
    graph.put(0, 1, 7);
    graph.put(0, 2, 9);
    graph.put(0, 5, 14);
    graph.put(1, 2, 10);
    graph.put(1, 3, 15);
    graph.put(2, 5, 2);
    graph.put(2, 3, 11);
    graph.put(3, 4, 6);
    graph.put(4, 5, 9);

    int from = 0;
    int to = 4;

    bool *visited = new bool[graph.vertices];
    int *distances = new int[graph.vertices];
    for (int i = 0; i < graph.vertices; i++) {
        visited[i] = false;
        distances[i] = 0x7FFFFFFF;
    }

    int current = from;
    distances[current] = 0;
    visited[current] = true;
    while (!visited[to]) {
        std::vector<int> neighbors;

        // find unvisited neighbors
        for (int i = 0; i < graph.vertices; i++) {
            if ((current != i) && (graph.get(current, i) != 0) && !visited[i]) {
                neighbors.push_back(i);
            }
        }

        int nearestNeighbor = 0;

        // calculate every neighbor distances & determine nearest neighbor
        for (int i = 0; i < neighbors.size(); i++) {
            if (!visited[neighbors[i]]) {
                int dist = graph.get(current, neighbors[i]);
                if (distances[current] + dist < distances[neighbors[i]]) {
                    distances[neighbors[i]] = distances[current] + dist;
                }
                if (dist < graph.get(current, neighbors[nearestNeighbor])) {
                    nearestNeighbor = i;
                }
            }
        }

        current = neighbors[nearestNeighbor];
        visited[current] = true;
    }

    std::cout << "Minimum distance: " << distances[to] << std::endl;

    delete distances;
    delete visited;

    return 0;
}

