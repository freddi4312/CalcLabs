#include "Header.h"
#include <cmath>


RESULT Bisection(double (*f)(double), double a, double b, double e)
{
  int steps = 0;

  while ((b - a) > 2 * e)
  {
    double c = (a + b) / 2;
    steps++;
    if (f(a) * f(c) <= 0)
      b = c;
    else
      a = c;
  }

  double x = (a + b) / 2;

  return RESULT(x, b - a, steps);
}

//x ≈ ± 9.31724294141481...