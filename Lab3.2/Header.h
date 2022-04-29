#pragma once

#include <vector>


typedef std::vector<std::pair<double, double>> TABLE;

TABLE TableWithFixedStep(double (*f)(double), double a, double h, int M);