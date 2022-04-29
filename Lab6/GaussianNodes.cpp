#include <vector>
#include <functional>
#include "POLYNOM.h"
#include "Header.h"

std::vector<std::vector<std::pair<double, double>>> CalcGaussianNodes(int N, double e)
{
  std::vector<std::vector<std::pair<double, double>>> Nodes(N + 1);

  for (int i = 0; i <= N; i++)
    Nodes[i].resize(i);

  POLYNOM Pn_1(1);
  POLYNOM Pn_2(0);
  POLYNOM Px(std::vector<double>{0, 1});

  for (int n = 1; n <= N; n++)
  {
    POLYNOM Pn = POLYNOM((2 * n - 1.0) / n) * Pn_1 * Px - POLYNOM((n - 1.0) / n) * Pn_2;
    POLYNOM dPn = Pn.der();
    Pn_2 = Pn_1;
    Pn_1 = Pn;

    std::function<double(double)> P([&Pn](double x) {return Pn(x); });
    std::vector<std::pair<double, double>> Ranges = Tabulation(P, -1, 1, 20000);
    if (Ranges.size() != n)
      throw std::exception("Incorrect count of ranges");

    for (int i = 0; i < n; i++)
    {
      double h = Ranges[i].second - Ranges[i].first;
      RESULT Result = Secants(Ranges[i].first, h, P, e);
      double x = Result.x;
      Nodes[n][i].first = x;
      Nodes[n][i].second = 2 / ((1 - x * x) * std::pow(dPn(x), 2));
    }
  }

  return Nodes;
}