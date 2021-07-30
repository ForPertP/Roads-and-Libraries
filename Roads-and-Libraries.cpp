#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

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

int dfsUtil(std::shared_ptr<Graph>& graph, vector<bool>& visited, int current)
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

long minCost(std::shared_ptr<Graph>& graph, long c_lib, long c_road)
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
    std::shared_ptr<Graph> graph = std::make_shared<Graph>(n, false);

    cout << cities.size() << endl;

    for (size_t i = 0; i < cities.size(); ++i)
    {
        graph->addEdge(cities[i][0]-1, cities[i][1]-1);
    }

    long cost = minCost(graph, c_lib, c_road);

    return cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(cin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
