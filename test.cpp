/*
 * Used for testing the datastructures 
 */

#include "Airport.h"
#include "Graph.h"
#include "MinHeap.h"

#include "Two_Djikstra.cpp"
#include "shortestPathInState(3).cpp"
#include "shortPathWithGivenStops(4).cpp"
#include "findAllConnections(5).cpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string getState(std::string location) {
   int i;
  for (i = 0; i < location.size(); i++) {
    if (location[i] == ',') break;
  }
  
  int charactersLeft = location.size() - i;

  // + 1 to account for space after comma in the input
  // hardcoded the state length (the 2) because all states are 2 letters
  return location.substr(i + 1, 1);
}

std::string getCity(std::string location) { 
  int i;
  for (i = 0; i < location.size(); i++) {
    if (location[i] == ',') break;
  }

  return location.substr(0, i);
}

int main() {
  Graph g;

  std::ifstream readFile;
  readFile.open("airports.csv");
  
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
  
  // print graph connections
  g.print();

  // MinHeap test (should output in sorted order)
  // MinHeap graphHeap(g);
  // while (graphHeap.size > 0) {
  //   std::cout << graphHeap.popMin().distance << " "; 
  // }
  //
  // std::cout << '\n';
  
  // Problem 2
  printShortestPath(g, g.airports[0], g.airports[16]);
  std::cout << '\n';

  // Problem 3
  printShortestPathsInState(g, "GA", g.airports[0]);
  std::cout << '\n';

  // Problem 4
  printShortestPath(g, g.airports[0], g.airports[16], 5);

  // Problem 5
//  printAllConnections(g);
//  std::cout << '\n';

  // Problem 6
  g.convertToUndirected();

  // For testing problem 6
  // g.print();

  readFile.close();

  return 0;
}
