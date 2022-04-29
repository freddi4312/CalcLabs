#include <vector>
#include <random>
#include <set>
#include <algorithm>
#include "Header.h"


TABLE EqSpacedTable(double (*f)(double), double a, double b, int M)
{
  TABLE Table(M + 1);

  for (int j = 0; j <= M; j++)
  {
    Table[j].first = a + (b - a) / M * j;
    Table[j].second = f(Table[j].first);
  }

  return Table;
}


TABLE RandomTable(double (*f)(double), double a, double b, int M)
{
  TABLE Table(M + 1);
  std::uniform_real_distribution<double> Unif(a, b);
  std::default_random_engine Engine;
  std::set<double> Numbers;

  for (std::pair<double, double> &p : Table)
  {
    do
    {
      p.first = Unif(Engine);
    } while (Numbers.count(p.first) != 0);
    Numbers.insert(p.first);
    p.second = f(p.first);
  }

  std::sort(Table.begin(), Table.end(), [](std::pair<double, double> const &a, std::pair<double, double> const &b)
    {
      return a.first < b.first;
    });

  return Table;
}