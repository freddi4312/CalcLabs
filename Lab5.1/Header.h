#pragma once

#include <vector>
#include <functional>


struct RESULT
{
  RESULT(double x, double last, int steps) :
    x(x),
    last(last),
    steps(steps)
  {}

  double x;
  double last;
  int steps;
};


std::vector<std::pair<double, double>> Tabulation(std::function<double(double)> &f, double A, double B, int N);
RESULT Secants(double x0, std::function<double(double)> &f, double e);
std::vector<std::vector<std::pair<double, double>>> CalcGaussianNodes(int N, double e);