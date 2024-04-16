/*
 * Used for testing the datastructures 
 */

#include "Airport.h"
#include "Graph.h"
#include "MinHeap.h"
#include "Two_Djikstra.cpp"

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

    /*
     * removing first char and last char from strings that have space and quotes
     * due to how the orgin and destination columns in the csv have extra commas
     * in them
     */

    row[2] = row[2].substr(1, row[2].size() - 1);
    row[3] = row[3].substr(1, row[3].size() - 2);
    row[4] = row[4].substr(1, row[4].size() - 1);
    row[5] = row[5].substr(1, row[5].size() - 2);

    Airport origin;
    int originIndex = g.findAirport(row[0]);
    if (originIndex == -1) {
        origin = Airport(row[0], row[2], row[3], g.airports.size());
    }
    else {
        origin = g.airports[originIndex];
    }

    g.addAirport(origin);

    Airport destination;
    int destIndex = g.findAirport(row[1]);
    if (destIndex == -1) {
        destination = Airport(row[1], row[4], row[5], g.airports.size());
    }
    else {
        destination = g.airports[destIndex];
    }

    g.addAirport(destination);
    
    double dist = std::stod(row[6]);
    double cost = std::stod(row[7]);

    g.addConnection(origin, dist, cost, destination);
  }

  g.print();
  MinHeap graphHeap(g);
  while (graphHeap.size > 0) {
    std::cout << graphHeap.popMin().distance << " "; 
  }

  std::cout << '\n';

  std::vector<Edge> shortPath = shortest_path(g, g.airports[0], g.airports[5]);

  std::cout << "SHORTEST PATH: ";
  for (int i = 0; i < shortPath.size(); i++) {
      std::cout << shortPath[i].destination.airportInitials << "->";
  }

  std::cout << '\n';

  readFile.close();

  return 0;
}
