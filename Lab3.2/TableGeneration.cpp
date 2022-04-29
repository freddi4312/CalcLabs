#include "Header.h"


TABLE TableWithFixedStep(double (*f)(double), double a, double h, int M)
{
  TABLE Table(M + 1);

  for (int i = 0; i <= M; i++)
  {
    Table[i].first = a + i * h;
    Table[i].second = f(Table[i].first);
  }

  return Table;
}