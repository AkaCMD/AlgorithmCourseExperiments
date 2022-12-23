#include "indexPQ.h"
#include "edge_weighted_graph.h"
#include <fstream>
#include <cmath>
#include <stack>
#include <chrono>
#define INF 100000

std::vector<std::vector<int>> nodes;
int vertex_count, edge_count;
int v, x, y, w;
int src, dest;
std::vector<std::vector<double>> edges;
std::ifstream infile("usa.txt");
std::ifstream testfile("usa-100long.txt");
EdgeWeightedGraph *graph;
std::chrono::system_clock::time_point start_time, end_time;

double distance(int v, int w)
{
    return std::sqrt(std::pow((nodes[v][0]-nodes[w][0]), 2) + std::pow((nodes[v][1]-nodes[w][1]), 2));
}
static void start_timer()
{
    start_time = std::chrono::system_clock::now();
}
static void end_timer()
{
    end_time = std::chrono::system_clock::now();
}
static double get_elasped_time()
{
    return double(std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count())/1000.0f;
}

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
            if(v == dest)   return;// Optimization: when the destination is discovered, stop relaxing
            for (Edge e : graph->get_edges(v))
            {
                relax(e, v);
            }
        }
    }

    void relax(Edge &e, int v)
    {
        int w = e.to;
        //------------ A*(Optimization)------------
        double new_dist = dist_to[v] - distance(v, dest) + e.weight + distance(w, dest);// f = g + h
        if(dist_to[w] > new_dist)
        {
            dist_to[w] = new_dist;
            edge_to[w] = e.from;
            if(pq->contain(w))
                pq->update(w, dist_to[w]);
            else
                pq->insert(w, dist_to[w]);
        }
        //------------ djikstra ------------
        // if (dist_to[w] > dist_to[v] + e.weight)
        // {
        //     dist_to[w] = dist_to[v] + e.weight;
        //     edge_to[w] = e.from;
        //     if (pq->contain(w))
        //         pq->update(w, dist_to[w]);
        //     else
        //         pq->insert(w, dist_to[w]);
        // }
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
    double total_time = 0;
    // Read file
    infile >> vertex_count >> edge_count;

    init_graph();
    
    // Test usa-100long
    for(int i=0; i<100; i++)
    {
        testfile >> src >> dest;
        start_timer();
        Djikstra_modified route(graph, src, dest);
        end_timer();
        total_time += get_elasped_time();
        std::cout << "from " << src << " to " << dest << ":" << std::endl;
        route.get_path();
        std::cout << std::endl << "-----------------------------------------------------------------------" << std::endl;
    }

    // Print running time
    std::cout << "running time: " << total_time << "ms" << std::endl;
    return 0;
}
