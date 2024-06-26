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


class Result {
    public static int depthFirstSearchUtil(Graph graph, boolean[] visited, int currentVertex) {
        int count = 1;
        visited[currentVertex] = true;

        for (long neighbor : graph.adjacencyList.get(currentVertex)) {
            if (!visited[(int) neighbor]) {
                count += depthFirstSearchUtil(graph, visited, (int) neighbor);
            }
        }

        return count;
    }

    public static long minimumCost(Graph graph, long costLibrary, long costRoad) {
        if (costLibrary < costRoad) {
            return costLibrary * graph.numVertices;
        }

        boolean[] visited = new boolean[(int) graph.numVertices];
        long totalCost = 0;

        for (int i = 0; i < graph.numVertices; ++i) {
            if (!visited[i]) {
                int numConnectedVertices = depthFirstSearchUtil(graph, visited, i);
                totalCost += (numConnectedVertices - 1) * costRoad;
                totalCost += costLibrary;
            }
        }

        return totalCost;
    }
    
    // public static long roadsAndLibraries(int n, int c_lib, int c_road, List<List<Integer>> cities) {
    public static long roadsAndLibraries(int numCities, int costLibrary, int costRoad, List<List<Integer>> cities) {
        Graph graph = new Graph(numCities, false);

        for (List<Integer> city : cities) {
            graph.addEdge(city.get(0) - 1, city.get(1) - 1);
        }

        return minimumCost(graph, costLibrary, costRoad);
    }
}


public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int q = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, q).forEach(qItr -> {
            try {
                String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                int n = Integer.parseInt(firstMultipleInput[0]);

                int m = Integer.parseInt(firstMultipleInput[1]);

                int c_lib = Integer.parseInt(firstMultipleInput[2]);

                int c_road = Integer.parseInt(firstMultipleInput[3]);

                List<List<Integer>> cities = new ArrayList<>();

                IntStream.range(0, m).forEach(i -> {
                    try {
                        cities.add(
                            Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                                .map(Integer::parseInt)
                                .collect(toList())
                        );
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                });

                long result = Result.roadsAndLibraries(n, c_lib, c_road, cities);

                bufferedWriter.write(String.valueOf(result));
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}
