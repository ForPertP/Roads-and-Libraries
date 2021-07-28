class Graph
{
    public:
        bool directed;
        long v;
        std::list<long> *adjList;
        Graph(long v, bool directed);
        ~Graph();
        void addEdge(int v, int e);
};

Graph::Graph(long v, bool directed)
{
    this->v = v;
    this->directed = directed;
    adjList = new list<long>[v];
}

Graph::~Graph()
{
    delete[] adjList;
}

void Graph::addEdge(int v, int e)
{
    adjList[v].push_back(e);

    if (!directed)
    {
        adjList[e].push_back(v);
    }
}

int dfsUtil(Graph *graph, vector<bool> &visited, int current)
{
    int count = 1;
    visited[current] = true;
    
    std::list<long>::iterator it;
    for (it = graph->adjList[current].begin(); it != graph->adjList[current].end(); ++it)
    {
        if (!visited[*it])
        {
            count += dfsUtil(graph, visited, *it);
        }
    }

    return count;
}

long minCost(Graph *graph, long c_lib, long c_road)
{
    if (c_lib < c_road)
    {
        return c_lib * graph->v;
    }

    vector<bool> visited(graph->v, false);
    long cost = 0;
    
    for (int i = 0; i < graph->v; ++i)
    {
        if (!visited[i])
        {
            int x = dfsUtil(graph,visited,i);
            cost += (x-1) * c_road;
            cost += c_lib;
        }
    }

    return cost;
}

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities)
{
    Graph* graph = new Graph(n, false);

    cout << cities.size() << endl;

    for (int i = 0; i < cities.size(); ++i)
    {
        graph->addEdge(cities[i][0]-1, cities[i][1]-1);
    }

    long cost = minCost(graph, c_lib, c_road);
    delete graph;

    return cost;
}
