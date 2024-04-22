/*
 * Used for testing the datastructures 
 */

#include "Airport.h"
#include "Graph.h"
#include "MinHeap.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#define COLUMN_SIZE 20

// Finds the shortest path from origin to destination using the Djikstra's algorithm
std::vector<Edge> shortest_path(Graph graph, Airport origin, Airport destination){
    MinHeap prioQueue;
    
    int size = graph.connections.size();
    int originIndex = origin.index;
    int destIndex = destination.index;
    
    std::vector<double> dist(size, INT_MAX); // holds shortest distance from source to index[i] node
    std::vector<int> prev(size, -1); // holds the index of the previous node

    dist[originIndex] = 0;
    std::vector<Edge> curr = graph.connections[originIndex];
    
    // Insert edge to get algorithm started
    prioQueue.insert(Edge(0, 0, origin, origin));  //added destination

    while(prioQueue.size > 0){
        Edge minEdge = prioQueue.popMin();

        if(destination.airportInitials == minEdge.destination.airportInitials) break;

        int minIndex = minEdge.destination.index;

        std::vector<Edge> neighbor = graph.connections[minIndex];

        for(int i = 0; i < neighbor.size(); i++){
            double distance = neighbor[i].distance;
            int edgeIndex = neighbor[i].destination.index;
            
            if(dist[minIndex] + distance < dist[edgeIndex]){
                dist[edgeIndex] = dist[minIndex] + distance;
                prev[edgeIndex] = minIndex;
                prioQueue.insert(neighbor[i]);
            }
        }
    }

    std::vector<Edge> path;
    int cur = destIndex;

    while (prev[cur] != -1) {
        int parentIndex = prev[cur];
        path.push_back(graph.findConnection(parentIndex, cur));
        cur = parentIndex;
    }

    std::reverse(path.begin(), path.end());

    return path;
}

void printShortestPath(Graph g, Airport origin, Airport destination) {
    std::cout << "Shortest route from " << origin.airportInitials << " to " << destination.airportInitials << ": ";

    std::vector<Edge> shortpath = shortest_path(g, origin, destination);

    double totalDistance = 0.0;
    double totalCost = 0.0;

    if (shortpath.size() == 0) {
        std::cout << "None\n";
        return;
    }

    std::cout << origin.airportInitials;
    for (int i = 0; i < shortpath.size(); i++) {
        std::cout << "->" << shortpath[i].destination.airportInitials;
        totalDistance += shortpath[i].distance;
        totalCost += shortpath[i].cost;
    }
    std::cout << ". The length is " << totalDistance << ". The cost is " << totalCost << ".\n";
}

double distanceFromPath(std::vector<Edge> path) { 
    double ans = 0.0;

    for (int i = 0; i < path.size(); i++) { 
        ans += path[i].distance;
    }

    return ans;
}

std::vector<Edge> dfs(const Graph& graph, const Airport& source, const Airport& dest, std::vector<int> distances,
                      std::vector<Edge> path, int depth) {
    if (depth == 0 && source == dest) {
        return path;
    }
    else if (depth == 0) {
        return {};
    }

    std::vector<Edge> connections = graph.connections[source.index];

    std::vector<Edge> shortestPath;
    double minDist = INT_MAX;

    for (int i = 0; i < connections.size(); i++) {
        int connectionIndex = connections[i].destination.index;

        if (distances[connectionIndex] == -1) {
            std::vector<int> newDistances = distances;
            newDistances[connectionIndex] = depth;
            std::vector<Edge> newPath = path;
            newPath.push_back(connections[i]);

            std::vector<Edge> completePath = dfs(graph, connections[i].destination, dest, newDistances,
                                                 newPath, depth - 1);

            double pathDist = distanceFromPath(completePath);

            if (pathDist != 0.0 && pathDist < minDist) {
                shortestPath = completePath;
                minDist = pathDist;
            }
        }
    }

    return shortestPath;
}

// Uses BFS to find the shortest path with a given number of stopsvector
std::vector<Edge> shortPathWithGivenStops(const Graph& graph, const Airport& source, const Airport& dest, int numStops) {
    int n = graph.airports.size();
    std::vector<int> distances(n, -1);
    std::vector<Edge> path;

    distances[source.index] = numStops;

  return dfs(graph, source, dest, distances, path, numStops);
} 

void printShortestPath(const Graph& graph, const Airport& source, const Airport& dest, int numStops) {
    // We need an extra edge to account for the example program in the project description
  std::vector<Edge> shortestPath = shortPathWithGivenStops(graph, source, dest, numStops + 1);
  
  // initials of source and destination
  std::string si = source.airportInitials;
  std::string di = dest.airportInitials;

  double totalDist = 0.0;
  double totalCost = 0.0;

  std::cout << "Shortest route from " << si << " to " << di << " with " << numStops << " stops: ";

  if (shortestPath.empty()) {
      std::cout << "None\n";
      return;
  }

  std::cout << si;

  for (int i = 0; i < shortestPath.size(); i++) {
    std::cout << "->" << shortestPath[i].destination.airportInitials;
    totalDist += shortestPath[i].distance;
    totalCost += shortestPath[i].cost;
  }
  
  std::cout << ". The length is " << totalDist << ". The cost is " << totalCost << ".\n";
}


void printShortestPathsInState(const Graph& graph, std::string state, Airport origin) {
  std::cout << "Shortest paths from " << origin.airportInitials << " to " << state << " state airports are:\n\n";
  std::cout << std::left << std::setw(COLUMN_SIZE) << "Path" << std::setw(COLUMN_SIZE) << "Length" << "Cost\n";

  for (int i = 0; i < graph.airports.size(); i++) {
    if (graph.airports[i].state != state) continue;
    
    Airport destination = graph.airports[i];
    std::vector<Edge> shortestPath = shortest_path(graph, origin, destination);
    
    if (shortestPath.size() == 0) continue;

    double curDistance = 0.0;
    double curCost = 0.0;
    
    std::string path = "";

    path += origin.airportInitials;
    for (int j = 0; j < shortestPath.size(); j++) {
      path += "->" + shortestPath[j].destination.airportInitials;
      curDistance += shortestPath[j].distance;
      curCost += shortestPath[j].cost;
    }

    std::cout << std::setw(COLUMN_SIZE) << path << std::setw(COLUMN_SIZE) << curDistance << std::setw(COLUMN_SIZE) << curCost << '\n';
  }
}


std::vector<int> findNumConnections(const Graph& graph) {
  std::vector<int> numConnections(graph.connections.size(), 0);

  for (int i = 0; i < graph.connections.size(); i++) {
    // add outbound flights
    numConnections[i] += graph.connections[i].size();

    // add inbound flights
    for (int j = 0; j < graph.connections[i].size(); j++) {
      Airport destination = graph.connections[i][j].destination;

      numConnections[destination.index]++;
    }
  }

  return numConnections;
}

void printAllConnections(const Graph& graph) {
  std::cout << "Airport       Connections\n";

  std::vector<int> numConnections = findNumConnections(graph);

  for (int i = 0; i < numConnections.size(); i++) {
    std::cout << graph.airports[i].airportInitials << "           " << numConnections[i] << '\n';
  }
}

std::vector<Edge> primMST(const Graph& g) {
  std::vector<bool> visited(g.connections.size(), false);
  MinHeap pq;
  pq.useCostToCompare = true;

  visited[0] = true; 
  for (const auto& edge : g.connections[0]) {
    pq.insert(edge);
  }

  std::vector<Edge> mst; // Minimal Spanning Tree
  while (pq.size > 0) {
    Edge minEdge = pq.popMin();

    if (visited[minEdge.destination.index]) continue;
    
    mst.push_back(minEdge);
    visited[minEdge.destination.index] = true;
    for (const auto& edge : g.connections[minEdge.destination.index]) {
      pq.insert(edge);
    }
  }  

  return mst;
}

void printPrimsMST(const Graph& g) {
 // Generate the Minimal Spanning Tree using Prim's algorithm
  std::vector<Edge> mst_prim = primMST(g);

  // Print the MST results
  std::cout << "Prim's Minimal Spanning Tree:\n";
  std::cout << "Edge\t\tWeight\n";

  double totalCost_prim = 0;
  int numEdges = 0;

  for (const auto& edge : mst_prim) {
      numEdges++;
      std::cout << edge.origin.airportInitials << " - " << edge.destination.airportInitials << "\t";
      std::cout << edge.cost << '\n';
      totalCost_prim += edge.cost;
  }
  
  // in a connected mst there will be numVertexes - 1 edges
  if (numEdges != g.airports.size() - 1) {
    std::cout << "MST cannot be formed as graph is disconnected\n";
    return;
  }

  std::cout << "Total Cost of MST: " << totalCost_prim << std::endl;
}

// Function to find the root of the vertex in the disjoint set
int findRoot(std::vector<int>& parent, int vertex) {
  while (parent[vertex] != vertex) {
    parent[vertex] = parent[parent[vertex]]; 
    vertex = parent[vertex];
  }
  return vertex;
}

// Function to generate the Minimal Spanning Tree using Kruskal's algorithm
std::vector<std::vector<Edge>> kruskalMST(const Graph& g) {
  MinHeap heap;
  heap.useCostToCompare = true;

  for (int i = 0; i < g.connections.size(); i++) {
    for (int j = 0; j < g.connections[i].size(); j++) {
      heap.insert(g.connections[i][j]);
    }
  }
  

  std::vector<Edge> mst;
  std::vector<int> parent(g.airports.size());

  // initialize parent
  for (int i = 0; i < g.airports.size(); ++i) {
    parent[i] = i; 
  }

  while (heap.size > 0) {
    Edge minEdge = heap.popMin();

    int root1 = findRoot(parent, minEdge.origin.index);
    int root2 = findRoot(parent, minEdge.destination.index);
    if (root1 != root2) {
      mst.push_back(minEdge);
      parent[root1] = root2;
    }
  }
  
  std::vector<std::vector<Edge>> minSpanForest(g.airports.size());

  for (int i = 0; i < mst.size(); i++) {
    int forestIndex = findRoot(parent, i);

    minSpanForest[forestIndex].push_back(mst[i]);
  }

  return minSpanForest;
}

void printKruskalsMinSpanForest(const Graph& g) {
  std::vector<std::vector<Edge>> forest = kruskalMST(g);
  
  std::cout << "******Kruskal's Minimum Spanning Forest******\n";

  for (int i = 0; i < forest.size(); i++) {
    if (forest[i].size() == 0) continue;

    double totalCost = 0.0;

    std::cout << "Forest with root " << i << '\n';
    std::cout << "Edge\t\tCost\n";

    for (int j = 0; j < forest[i].size(); j++) {
      Airport origin = forest[i][j].origin;
      Airport dest = forest[i][j].destination;

      totalCost += forest[i][j].cost;

      std::cout << origin.airportInitials << " - " << dest.airportInitials << '\t';
      std::cout << forest[i][j].cost << '\n';
    }

    std::cout << "Total Cost of MST: " << totalCost << "\n\n";
  }
}

int main() {
  Graph g;

  std::ifstream readFile;
  readFile.open("airports.txt");
  
  // Row in the format:
  // {Origin_Airport, Destination_Airport, Origin_City, Destination_city, Distance, Cost}
  std::vector<std::string> row;
  std::string line, word, temp;
  
  std::getline(readFile, temp); // get rid of column aliases

  // reads until temp doesn't receive input
  while (std::getline(readFile, line)) {
    row.clear();

    // used for tokenizing the rows
    std::stringstream s(line);
   
    // push each column to row
    while(getline(s, word, ',')) {
      row.push_back(word);
    }

    // Stripping the extra characers created from commas being in the csv
    // big frowny face, Ms. Professor
    row[2] = row[2].substr(1, row[2].size() - 1);
    row[3] = row[3].substr(1, row[3].size() - 2);
    row[4] = row[4].substr(1, row[4].size() - 1);
    row[5] = row[5].substr(1, row[5].size() - 2);
    
    Airport origin;
    Airport destination;

    int originInd = g.findAirport(row[0]);
    int destInd = g.findAirport(row[1]);
    
    // only add airports if they don't exist
    if (originInd == -1) {
      origin = Airport(row[0], row[2], row[3], g.airports.size());
      g.addAirport(origin);
    }
    else {
      origin = g.airports[originInd];
    }

    if (destInd == -1) {
      destination = Airport(row[1], row[4], row[5], g.airports.size());
      g.addAirport(destination);
    }
    else {
      destination = g.airports[destInd];
    }
    
    double dist = std::stod(row[6]);
    double cost = std::stod(row[7]);

    g.addConnection(origin, dist, cost, destination);
  }
  
  // print graph connections (problem 1 kinda)
  // g.print();
 
  // Problem 2
  printShortestPath(g, g.airports[0], g.airports[16]);
  std::cout << '\n';

  // Problem 3
  printShortestPathsInState(g, "GA", g.airports[0]);
  std::cout << '\n';

  // Problem 4
  printShortestPath(g, g.airports[0], g.airports[16], 2);

  // Problem 5
  printAllConnections(g);
  std::cout << '\n';

  // Problem 6
  g.convertToUndirected();

  // For testing problem 6
  // g.print();
  
  // problem 7
  printPrimsMST(g);

   // problem 8
  printKruskalsMinSpanForest(g);

  readFile.close();

  return 0;
}
