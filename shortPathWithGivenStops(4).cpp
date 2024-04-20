#include "Graph.h"
#include "Edge.h"
#include "Airport.h"

#include <vector>
#include <string>

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
