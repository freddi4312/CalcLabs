#include <vector>
#include "Header.h"

double Langrange(TABLE const &Table, int N, double x)
{
  double Value = 0;
  
  for (int k = 0; k <= N; k++)
  {
    double Lkn = 1;

    for (int i = 0; i <= N; i++)
      if (i != k)
        Lkn = Lkn * (x - Table[i].first) / (Table[k].first - Table[i].first);

    Value += Lkn * Table[k].second;
  }

  return Value;
}