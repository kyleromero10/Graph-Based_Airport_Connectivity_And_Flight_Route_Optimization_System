#pragma once

#include <string>

class Airport {
public:
  std::string airportInitials;
  std::string city;
  std::string state;

  Airport() {
    this->airportInitials = "None";
    this->city = "None";
    this->state = "None";
  }

  Airport(const std::string& initials, const std::string& city, const std::string& state) {
    this->airportInitials = initials;
    this->city = city;
    this->state = state;
  }
};
