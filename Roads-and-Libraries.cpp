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
    long num_vertices;
    vector<list<long>> adjacency_list;

public:    
    Graph(long num_vertices, bool directed);
    void addEdge(int vertex1, int vertex2);
};

Graph::Graph(long num_vertices, bool directed)
{
    this->num_vertices = num_vertices;
    this->directed = directed;
    adjacency_list.resize(num_vertices);
}

void Graph::addEdge(int vertex1, int vertex2)
{
    adjacency_list[vertex1].push_back(vertex2);

    if (!directed)
    {
        adjacency_list[vertex2].push_back(vertex1);
    }
}

int depthFirstSearchUtil(Graph& graph, vector<bool>& visited, int current_vertex)
{
    int count = 1;
    visited[current_vertex] = true;

    list<long>::iterator it;
    for (it = graph.adjacency_list[current_vertex].begin(); it != graph.adjacency_list[current_vertex].end(); ++it)
    {
        if (!visited[*it])
        {
            count += depthFirstSearchUtil(graph, visited, *it);
        }
    }

    return count;
}

long minimumCost(Graph& graph, long cost_library, long cost_road)
{
    if (cost_library < cost_road)
    {
        return cost_library * graph.num_vertices;
    }

    vector<bool> visited(graph.num_vertices, false);
    long total_cost = 0;

    for (int i = 0; i < graph.num_vertices; ++i)
    {
        if (!visited[i])
        {
            int num_connected_vertices = depthFirstSearchUtil(graph, visited, i);
            total_cost += (num_connected_vertices - 1) * cost_road;
            total_cost += cost_library;
        }
    }

    return total_cost;
}

//long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities)
long roadsAndLibraries(int num_cities, int cost_library, int cost_road, vector<vector<int>> cities)
{
    Graph graph(num_cities, false);

    for (size_t i = 0; i < cities.size(); ++i)
    {
        graph.addEdge(cities[i][0] - 1, cities[i][1] - 1);
    }

    long minimum_cost = minimumCost(graph, cost_library, cost_road);

    return minimum_cost;
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
