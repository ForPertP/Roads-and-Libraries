import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;


class Graph {
    boolean directed;
    int numVertices;
    ArrayList<LinkedList<Integer>> adjacencyList;

    public Graph(int numVertices, boolean directed) {
        this.numVertices = numVertices;
        this.directed = directed;
        adjacencyList = new ArrayList<>();
        for (int i = 0; i < numVertices; i++) {
            adjacencyList.add(new LinkedList<>());
        }
    }

    public void addEdge(int vertex1, int vertex2) {
        adjacencyList.get(vertex1).add(vertex2);
        if (!directed) {
            adjacencyList.get(vertex2).add(vertex1);
        }
    }
}


