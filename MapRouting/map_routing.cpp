#include "indexPQ.h"
#include "edge_weighted_graph.h"
#include <fstream>
#include <cmath>
#include <stack>
#define INF 100000

class Djikstra_modified
{
private:
    std::vector<double> dist_to;
    std::vector<int> edge_to;
    int src, dest;
    IndexPQ *pq;

public:
    std::vector<int> path;
    Djikstra_modified(EdgeWeightedGraph *graph, int source, int destination)
    {
        const int v_count = graph->getV();
        dist_to = std::vector<double>(v_count);
        edge_to = std::vector<int>(v_count);
        src = source;
        dest = destination;
        pq = new IndexPQ(v_count);
        // Init dist_to
        for (int i=0; i<dist_to.size(); i++)
        {
            dist_to[i] = INF;
        }
        dist_to[source] = 0;
        // Init edge_to
        for (int i=0; i<edge_to.size(); i++)
        {
           edge_to[i] = -1;
        }
        // Init PQ
        pq->insert(source, dist_to[source]);
        while (!pq->empty())
        {
            int v = pq->pop();
            if(v == dest)   return;// Optimization_1: when the destination is discovered, stop relaxing
            for (Edge e : graph->get_edges(v))
            {
                relax(e, v);
            }
        }
    }

    void relax(Edge &e, int v)
    {
        int w = e.to;
        if (dist_to[w] > dist_to[v] + e.weight)
        {
            dist_to[w] = dist_to[v] + e.weight;
            edge_to[w] = e.from;
            if (pq->contain(w))
                pq->update(w, dist_to[w]);
            else
                pq->insert(w, dist_to[w]);
        }
    }

    void get_path()
    {
        int e = edge_to[dest];
        std::stack<int> s;
        std::vector<int> path;
        s.push(dest);
        while (1)
        {
            if (e == -1)
                break;
            s.push(e);
            e = edge_to[e];
        }
        while (!s.empty())
        {
            path.push_back(s.top());
            s.pop();
        }
        std::cout << "path: " << std::endl;
        for (int v : path)
        {
            std::cout << v << " ";
        }
    }
    double total_distance()
    {
        return dist_to[dest];
    }
};
//-------------------------------main-------------------------------
std::vector<std::vector<int>> nodes;
int vertex_count, edge_count;
int v, x, y, w;
int src, dest;
std::vector<std::vector<double>> edges;
std::ifstream infile("usa.txt");
EdgeWeightedGraph *graph;

double distance(int v, int w)
{
    return std::sqrt(std::pow((nodes[v][0]-nodes[w][0]), 2) + std::pow((nodes[v][1]-nodes[w][1]), 2));
}

void init_graph()
{
    // Init nodes
    nodes = std::vector<std::vector<int>>(vertex_count, std::vector<int>(2));
    // Init vertices
    edges = std::vector<std::vector<double>>(edge_count, std::vector<double>(2));
    // Init coordinates
    for (int i = 0; i < vertex_count; i++)
    {
        infile >> v >> x >> y;
        nodes[v] = {x, y};
    }
    // Init edges
    for (int i = 0; i < edge_count; i++)
    {
        infile >> v >> w;
        edges[i][0] = v;
        edges[i][1] = w;
    }
    // Init graph
    graph = new EdgeWeightedGraph(vertex_count);
    for (int i = 0; i < edge_count; i++)
    {
        int v = edges[i][0], w = edges[i][1];
        graph->add_edge(v, w, distance(v, w));
    }
}

int main()
{
    // Read file
    infile >> vertex_count >> edge_count;

    init_graph();

    // Input src && dest
    std::cout << "Please enter the source and the destination(src dest):" << std::endl;
    std::cin >> src >> dest;

    // Calculate the route
    Djikstra_modified route(graph, src, dest);

    // Print path
    route.get_path();
    std::cout << std::endl;

    // Print distance
    double total_dist = route.total_distance();
    std::cout << "distance: " << total_dist;
    return 0;
}
