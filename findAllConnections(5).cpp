#include <vector>

#include "Graph.h"
#include "Airport.h"


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
