#include "Graph.h"
#include "Edge.h"
#include "Airport.h"

#include <vector>
#include <string>

// Uses BFS to find the shortest path with a given number of stopsvector
std::vector<Edge> shortPathWithGivenStops(const Graph& graph, const Airport& source, const Airport& dest, int numStops) {
  return std::vector<Edge>();
} 

void printShortestPath(const Graph& graph, const Airport& source, const Airport& dest, int numStops) {
  std::vector<Edge> shortestPath = shortPathWithGivenStops(graph, source, dest, numStops);
  
  // initials of source and destination
  std::string si = source.airportInitials;
  std::string di = dest.airportInitials;

  double totalDist = 0.0;
  double totalCost = 0.0;

  std::cout << "Shortest route from " << si << " to " << di << " with " << numStops << " stops: " << si;

  for (int i = 0; i < shortestPath.size(); i++) {
    std::cout << "->" << shortestPath[i].destination.airportInitials;
    totalDist += shortestPath[i].distance;
    totalCost += shortestPath[i].cost;
  }
  
  std::cout << ". The length is " << totalDist << ". The cost is " << totalCost << ".\n";
}
