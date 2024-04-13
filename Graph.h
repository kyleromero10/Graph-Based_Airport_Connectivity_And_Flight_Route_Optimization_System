#pragma once

#include "Airport.h"
#include "Edge.h"
#include <iostream>
#include <vector>

class Graph {
public:
  // An airport at airports[i] has a list of connections at connections[i]
  std::vector<std::vector<Edge>> connections;
  std::vector<Airport> airports;

  Graph(){}
  
  // returns index of aiport matching the initials
  // This function gets called a lot and is linear so switching to a better
  // implimentation may be necessary
  int findAirport(std::string intials) {
    for (int i = 0; i < airports.size(); i++) {
      if (airports[i].airportInitials == intials) {
        return i;
      }
    }

    return -1;
  }
  
  // Inserts a new airport
  void addAirport(const Airport& airport) {
    // do not add if airport exists
    if (findAirport(airport.airportInitials) != -1) return; 

    airports.push_back(airport);
    connections.push_back(std::vector<Edge>(0)); // adds new connection list of size 0
  }

  // Inserts a connection at a specified airport
  void addConnection(const Airport& origin, double distance, double cost, const Airport& destination) {
    int airportIndex = findAirport(origin.airportInitials);

    // no airport in list yet
    if (airportIndex == -1) {
      airports.push_back(origin);
      connections.back().push_back(Edge(distance, cost, destination));

      return;
    }

    connections[airportIndex].push_back(Edge(distance, cost ,destination));
  }
  
  // Prints the adjacency list of the graph
  void print() {
    std::cout << "******Printing Graph******\n";

    for (int i = 0; i < connections.size(); i++) {
      std::cout << airports[i].airportInitials << ": ";

      for (int j = 0; j < connections[i].size(); j++) {
        std::cout << connections[i][j].destination.airportInitials << "->";
      }
      
      std::cout << '\n';
    }

    std::cout << "******End of Graph******\n";
  }
};