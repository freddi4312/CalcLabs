#include <vector>
#include <functional>

std::vector<std::pair<double, double>> Tabulation(std::function<double (double)> &f, double A, double B, int N)
{
  std::vector<std::pair<double, double>> Sections;
  double h = (B - A) / N;
  double x1 = A;
  double x2 = x1 + h;
  double y1 = f(A);
  double y2 = 0;

  while (x2 <= B)
  {
    y2 = f(x2);
    if (y1 * y2 <= 0)
      Sections.push_back(std::pair<double, double>(x1, x2));

    x1 = x2;
    x2 = x1 + h;
    y1 = y2;
  }

  return Sections;
}