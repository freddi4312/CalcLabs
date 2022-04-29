#pragma once
#include <vector>


typedef std::vector<std::pair<double, double>> TABLE;

TABLE EqSpacedTable(double (*f)(double), double a, double b, int M);
TABLE RandomTable(double (*f)(double), double a, double b, int M);
double Langrange(TABLE const &Table, int N, double x);
double Newton(TABLE const &Table, int N, double x);