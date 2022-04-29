#pragma once

#include <vector>

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


std::vector<std::pair<double, double>> Tabulation(double (*f)(double), double A, double B, int N);
RESULT Bisection(double (*f)(double), double a, double b, double e);
RESULT Newton(double x, double (*f)(double), double (*df)(double), double e);
RESULT ModNewton(double x, double (*f)(double), double (*df)(double), double e);
RESULT Secants(double x0, double (*f)(double), double e);