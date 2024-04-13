/*
 * Used for testing the datastructures 
 */

#include "Airport.h"
#include "Graph.h"
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
  
  // reads until temp doesn't receive input
  while (std::getline(readFile, temp)) {
    row.clear();

    getline(readFile, line);

    // used for tokenizing the rows
    std::stringstream s(line);
   
    // push each column to row
    while(getline(s, word, ',')) {
      row.push_back(word);
    } 
  
    Airport origin(row[0], "Test", "Test");
    Airport destination(row[1], "Test", "Test");
    
    double dist = std::stod(row[6]);
    double cost = std::stod(row[7]);

    g.addAirport(origin);
    g.addAirport(destination);

    g.addConnection(origin, dist, cost, destination);
  }

  g.print();
  readFile.close();

  return 0;
}
