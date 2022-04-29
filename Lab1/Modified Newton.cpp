#include "Header.h"
#include <cmath>


RESULT ModNewton(double x, double (*f)(double), double (*df)(double), double e)
{
  double prev_x = 0;
  double x0 = x;
  int steps = 0;

  do
  {
    steps++;
    prev_x = x;
    x = prev_x - f(prev_x) / df(x0);
  } while (std::abs(prev_x - x) >= e);

  return RESULT(x, std::abs(prev_x - x), steps);
}