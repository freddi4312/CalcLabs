#pragma once

#include <vector>
#include <map>
#include <functional>
#include "POLYNOM.h"


typedef std::vector<std::pair<double, double>> TABLE;

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

TABLE TableCreation(double (*f)(double), double &a, double &b);
void ReverseInterpolationMethod1(TABLE Table, double (*f)(double));
void ReverseInterpolationMethod2(TABLE Table, double (*f)(double));
TABLE EqSpacedTable(double (*f)(double), double a, double b, int M);
TABLE RandomTable(double (*f)(double), double a, double b, int M);
double Newton(TABLE const &Table, int N, double x);
POLYNOM NewtonPolynom(TABLE const &Table, int N);
std::vector<std::pair<double, double>> Tabulation(std::function<double (double)> &f, double A, double B, int N);
RESULT Secants(double x0, std::function<double(double)> &f, double e);