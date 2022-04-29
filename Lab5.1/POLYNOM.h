#pragma once

#include <map>
#include <vector>
#include <iostream>


class POLYNOM
{
private:
  std::map<unsigned int, double> A;

public:
  POLYNOM();
  POLYNOM(double a);
  POLYNOM(std::vector<double> a);
  POLYNOM der();
  POLYNOM integr();
  double operator()(double x);
  POLYNOM operator+(POLYNOM const &other);
  POLYNOM operator-(POLYNOM const &other);
  POLYNOM operator*(POLYNOM const &other);
  friend std::ostream &operator<<(std::ostream &out, POLYNOM const &pol);
};