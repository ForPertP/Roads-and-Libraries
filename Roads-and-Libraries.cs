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
