#include <vector>
#include <iostream>
class Edge
{
public:
    int from, to;
    double weight;
    Edge(int from, int to, double weight)
    {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
};


class EdgeWeightedGraph
{
private:
    int V;//the count of vertex
    std::vector<std::vector<Edge>> adj;//adjacent Table
    
public:
    EdgeWeightedGraph(int V)
    {
        this->V = V;
        adj.resize(V);
    }
    void add_edge(int from, int to, double weight)
    {
        adj[from].push_back(Edge(from, to, weight));
        adj[to].push_back(Edge(to, from, weight));
    }
    std::vector<Edge> get_edges(int vertex)// return the ajacent edges of the vertex
    {
        return adj[vertex];
    }
    int getV()
    {
        return V;
    }
};
