#include "Header.h"
#include <cmath>


RESULT Newton(double x, double (*f)(double), double (*df)(double), double e)
{
  double prev_x = 0;
  int steps = 0;

  do
  {
    steps++;
    prev_x = x;
    x = prev_x - f(prev_x) / df(prev_x);
  } while (std::abs(prev_x - x) >= e);
  
  return RESULT(x, std::abs(prev_x - x), steps);
}