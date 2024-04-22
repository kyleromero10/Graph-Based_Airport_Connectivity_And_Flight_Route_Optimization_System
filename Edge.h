#pragma once

#include "Airport.h"

class Edge {
public:
  double distance;
  double cost;
  Airport origin;
  Airport destination;
  
  Edge() {
    this->distance = 0;
    this->cost = 0;
    this->origin = Airport();
    this->destination = Airport();
  }

  Edge(double distance, double cost, const Airport& origin, const Airport& destination) {
    this->distance = distance;
    this->cost = cost;
    this->origin = origin;
    this->destination = destination;
  }

  double compareDist(const Edge& other) {
    return this->distance - other.distance;
  }

  double compareCost(const Edge& other) {
    return this->cost - other.cost;
  }
  
  bool operator<(const Edge& other) const { return cost < other.cost; }   
  bool operator>(const Edge& other) const { return cost > other.cost; }
};
