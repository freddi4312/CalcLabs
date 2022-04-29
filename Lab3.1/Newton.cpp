#include <vector>
#include "Header.h"
#include "POLYNOM.h"


std::vector<std::vector<double>> DiffCompute(TABLE const &Table, int N)
{
  std::vector<std::vector<double>> Diff(N + 1, std::vector<double>(N + 1, 0));

  for (int i = 0; i <= N; i++)
    Diff[i][0] = Table[i].second;

  for (int j = 1; j <= N; j++)
    for (int i = 0; i <= N - j; i++)
      Diff[i][j] = (Diff[i][j - 1] - Diff[i + 1][j - 1]) / (Table[i].first - Table[i + j].first);

  return Diff;
}


double Newton(TABLE const &Table, int N, double x)
{
  std::vector<std::vector<double>> Diff = DiffCompute(Table, N);

  double Result = 0;
  double Product = 1;

  for (int i = 0; i <= N; i++)
  {
    Result += Product * Diff[0][i];
    Product *= (x - Table[i].first);
  }

  return Result;
}


POLYNOM NewtonPolynom(TABLE const &Table, int N)
{
  std::vector<std::vector<double>> Diff = DiffCompute(Table, N);

  POLYNOM Result;
  POLYNOM Product(1);

  for (int i = 0; i <= N; i++)
  {
    Result = Result + Product * Diff[0][i];
    Product = Product * (POLYNOM(std::vector<double>{0, 1}) - Table[i].first);
  }

  return Result;
}