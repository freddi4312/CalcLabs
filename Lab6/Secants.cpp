#include "Header.h"
#include <cmath>


RESULT Secants(double x0, double h, std::function<double(double)> &f, double e)
{
  double prev_prev_x = 0;
  double prev_x = x0;
  double x = x0 + h / 10;
  int steps = 0;

  do
  {
    steps++;
    prev_prev_x = prev_x;
    prev_x = x;
    x = prev_x - f(prev_x) / (f(prev_x) - f(prev_prev_x)) * (prev_x - prev_prev_x);
  } while (std::abs(prev_x - x) >= e);

  return RESULT(x, std::abs(prev_x - x), steps);
}