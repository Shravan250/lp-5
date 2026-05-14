#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

// Graph class representing an undirected graph
class Graph
{
private:
    int numVertices;                 // Number of vertices
    vector<vector<int>> adj;         // Adjacency list

public:
    // Constructor
    Graph(int vertices) : numVertices(vertices), adj(vertices) {}

    // Add an edge between two vertices
    void addEdge(int src, int dest)
    {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    // Display the graph
    void viewGraph()
    {
        cout << "Graph:\n";

        for (int i = 0; i < numVertices; i++)
        {
            cout << "Vertex " << i << " -> ";

            for (int neighbor : adj[i])
            {
                cout << neighbor << " ";
            }

            cout << endl;
        }
    }

    // Parallel Breadth First Search (BFS)
    void bfs(int startVertex)
    {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        // Mark starting vertex as visited
        visited[startVertex] = true;

        // Push starting vertex into queue
        q.push(startVertex);

        while (!q.empty())
        {
            // Get front vertex from queue
            int currentVertex = q.front();
            q.pop();

            // Print current vertex
            cout << currentVertex << " ";

            // Parallel loop for all adjacent vertices
            // OpenMP works only with indexed loops
#pragma omp parallel for
            for (int i = 0; i < adj[currentVertex].size(); i++)
            {
                int neighbor = adj[currentVertex][i];

                // If neighbor is not visited
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;

                    // Push neighbor into queue
                    q.push(neighbor);
                }
            }
        }
    }

    // Parallel Depth First Search (DFS)
    void dfs(int startVertex)
    {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        // Mark starting vertex as visited
        visited[startVertex] = true;

        // Push starting vertex into stack
        s.push(startVertex);

        while (!s.empty())
        {
            // Get top vertex from stack
            int currentVertex = s.top();
            s.pop();

            // Print current vertex
            cout << currentVertex << " ";

            // Parallel loop for all adjacent vertices
            // OpenMP works only with indexed loops
#pragma omp parallel for
            for (int i = 0; i < adj[currentVertex].size(); i++)
            {
                int neighbor = adj[currentVertex][i];

                // If neighbor is not visited
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;

                    // Push neighbor into stack
                    s.push(neighbor);
                }
            }
        }
    }
};

int main()
{
    int numVertices;

    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    // Create graph object
    Graph graph(numVertices);

    int numEdges;

    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination):\n";

    // Input edges
    for (int i = 0; i < numEdges; i++)
    {
        int src, dest;

        cin >> src >> dest;

        graph.addEdge(src, dest);
    }

    // Display graph
    graph.viewGraph();

    int startVertex;

    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> startVertex;

    // Perform BFS
    cout << "Breadth First Search (BFS): ";
    graph.bfs(startVertex);

    cout << endl;

    // Perform DFS
    cout << "Depth First Search (DFS): ";
    graph.dfs(startVertex);

    cout << endl;

    return 0;
}