#pragma once

#include "Airport.h"
#include "Graph.h"
#include "Edge.h"
#include "Two_Djikstra.cpp"

#include <iomanip>
#include <string>

#define COLUMN_SIZE 20

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
