#pragma once

#include <string>

class Airport {
public:
  std::string airportInitials;
  std::string city;
  std::string state;
  int index;

  Airport() {
    this->airportInitials = "None";
    this->city = "None";
    this->state = "None";
    this->index = -1;
  }

  Airport(const std::string& initials, const std::string& city, const std::string& state, int index) {
    this->airportInitials = initials;
    this->city = city;
    this->state = state;
    this->index = index;
  }
};
