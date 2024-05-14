using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;


public class Graph
{
    public bool Directed { get; set; }
    public long NumVertices { get; set; }
    public List<List<long>> AdjacencyList { get; set; }

    public Graph(long numVertices, bool directed)
    {
        NumVertices = numVertices;
        Directed = directed;
        AdjacencyList = new List<List<long>>((int)numVertices);
        for (long i = 0; i < numVertices; i++)
        {
            AdjacencyList.Add(new List<long>());
        }
    }

    public void AddEdge(int vertex1, int vertex2)
    {
        AdjacencyList[vertex1].Add(vertex2);
        if (!Directed)
        {
            AdjacencyList[vertex2].Add(vertex1);
        }
    }
}


class Result
{
    public static long MinimumCost(Graph graph, long costLibrary, long costRoad)
    {
        long totalCost = 0;

         return totalCost;
    }

    private static int DepthFirstSearchUtil(Graph graph, bool[] visited, int currentVertex)
    {
        int count = 1;
 
        return count;
    }

    //public static long roadsAndLibraries(int n, int c_lib, int c_road, List<List<int>> cities)
    public static long roadsAndLibraries(int numCities, int costLibrary, int costRoad, List<List<int>> cities)
    {
        var graph = new Graph(numCities, false);

        foreach (var city in cities)
        {
            graph.AddEdge(city[0] - 1, city[1] - 1);
        }

        long minimumCost = MinimumCost(graph, costLibrary, costRoad);

        return minimumCost;
    }
}


class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);

        int q = Convert.ToInt32(Console.ReadLine().Trim());

        for (int qItr = 0; qItr < q; qItr++)
        {
            string[] firstMultipleInput = Console.ReadLine().TrimEnd().Split(' ');

            int n = Convert.ToInt32(firstMultipleInput[0]);

            int m = Convert.ToInt32(firstMultipleInput[1]);

            int c_lib = Convert.ToInt32(firstMultipleInput[2]);

            int c_road = Convert.ToInt32(firstMultipleInput[3]);

            List<List<int>> cities = new List<List<int>>();

            for (int i = 0; i < m; i++)
            {
                cities.Add(Console.ReadLine().TrimEnd().Split(' ').ToList().Select(citiesTemp => Convert.ToInt32(citiesTemp)).ToList());
            }

            long result = Result.roadsAndLibraries(n, c_lib, c_road, cities);

            textWriter.WriteLine(result);
        }

        textWriter.Flush();
        textWriter.Close();
    }
}
