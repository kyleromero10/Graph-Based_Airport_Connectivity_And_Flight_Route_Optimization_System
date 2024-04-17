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

//  Graph(Graph &g)
//  {
//      this->connections = g.connections;
//      this->airports = g.airports;
//  }
  
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
    connections.emplace_back(0); // adds new connection list of size 0
  }

  // Inserts a connection at a specified airport
  void addConnection(const Airport& origin, double distance, double cost, const Airport& destination) {
    int airportIndex = findAirport(origin.airportInitials);

    // no airport in list yet
    if (airportIndex == -1) {
      addAirport(origin);
      connections.back().push_back(Edge(distance, cost, destination));

      return;
    }

    connections[airportIndex].push_back(Edge(distance, cost ,destination));
  }

  Edge findConnection(int origin, int destination) {
      for (int i = 0; i < connections[origin].size(); i++) {
          Edge curConnection = connections[origin][i];
          if (curConnection.destination.index == destination) {
              return curConnection;
          }
      }

      return {};
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

  void convertToUndirected(){
      for (int i = 0; i < connections.size(); i++){
        std::vector<Edge> currConn = connections[i];
        Airport currAirport = airports[i];

        for(int j = 0; j < currConn.size(); j++){
            Edge currEdge = currConn[j];
            Airport destAirport = currEdge.destination;
            Edge connection = findConnection(destAirport.index, currAirport.index);

            if(connection.distance == 0 ){
                Edge newEdgeReverse = Edge(currEdge.distance, currEdge.cost, currAirport);
                connections[destAirport.index].push_back(newEdgeReverse);
            }
            else{
                if(currEdge.cost < connection.cost){
                    connection.cost = currEdge.cost;
                }
                else{
                    currEdge.cost = connection.cost;
                }
            }
        }
    }
  }
};


