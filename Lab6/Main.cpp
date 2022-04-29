#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <string>
#include <sstream>
#include <functional>
#include "Header.h"
#include "POLYNOM.h"


int GetVariant(int min, int max)
{
  int Option;

  do
  {
    std::cin >> Option;
    std::cin.ignore(INT_MAX, '\n');
    if (!(Option >= min && Option <= max))
      std::cout << "Íåêîððåêòíûé âàðèàíò\n";
  } while (!(Option >= min && Option <= max));

  return Option;
}


double CalcQuadrature(std::function<double(double)> const &f, std::vector<std::pair<double, double>> const &Nodes)
{
  double Result = 0;

  for (std::pair<double, double> const &p : Nodes)
    Result += f(p.first) * p.second;

  return Result;
}


double CalcGaussQF(std::function<double(double)> f, std::vector<std::pair<double, double>> Nodes, double a, double b)
{
  int N = Nodes.size();

  std::vector<std::pair<double, double>> NodesAB(N);

  double q = (b - a) / 2;
  for (int i = 0; i < N; i++)
  {
    NodesAB[i].first = a + q * (Nodes[i].first + 1);
    NodesAB[i].second = q * Nodes[i].second;
  }

  return CalcQuadrature(f, NodesAB);
}


void CompoundGaussQF(std::function<double(double)> f, double e)
{
  double a = 0;
  double b = 0;
  int m = 0;
  int N = 0;

  std::cout << "\nÂâåäèòå a: ";
  std::cin >> a;
  std::cout << "Ââåäèòå b: ";
  std::cin >> b;
  std::cout << "Ââåäèòå m: ";
  std::cin >> m;
  std::cout << "Ââåäèòå N: ";
  std::cin >> N;

  std::vector<std::pair<double, double>> Nodes = CalcGaussianNodes(N, e)[N];
  double h = (b - a) / m;
  double Result = 0;
  double SumA = 0;

  for (std::pair<double, double> const &p : Nodes)
    SumA += p.second;

  for (int i = 0; i < m; i++)
  {
    double A = a + h * i;
    double B = A + h;

    Result += CalcGaussQF(f, Nodes, A, B);
  }

  std::cout << "\n";
  for (int i = 0; i < N; i++)
  {
    std::cout << Nodes[i].first << "   ";
    std::cout << Nodes[i].second << "\n";
  }
  std::cout << "Ñóììà Ak = " << SumA << "\n";
  std::cout << "Çíà÷åíèå = " << Result << "\n";
}


double CalcMiddleRects(double A, double B, int m, std::function<double(double)> &f)
{
  double h = (B - A) / m;
  double q = 0;

  for (int j = 0; j <= m - 1; j++)
    q += f(A + (j + 0.5) * h);

  return h * q;
}


std::vector<double> CalcMoments(std::function<double(double)> &p, double a, double b, int N)
{
  std::vector<double> Moments(N + 1);
  POLYNOM Pn(1);
  POLYNOM X(std::vector<double>{0, 1});

  for (int i = 0; i <= N; i++)
  {
    std::function<double(double)> f([&Pn, &p](double x)
    {
      return Pn(x) * p(x);
    });

    Moments[i] = CalcMiddleRects(a, b, 100000, f);
    Pn = Pn * X;
  }

  return Moments;
}


void GaussianTypeQF(std::function<double(double)> &p, std::function<double(double)> &f, std::function<double(double)> &Spx3, double e)
{
  double a = 0;
  double b = 0;
  const int N = 2;

  std::cout << "\nÂâåäèòå a: ";
  std::cin >> a;
  std::cout << "Ââåäèòå b: ";
  std::cin >> b;

  std::vector<double> u = CalcMoments(p, a, b, 2 * N - 1);

  std::cout << "\n";
  for (int i = 0; i <= 2 * N - 1; i++)
    std::cout << "Ìîìåíò " << i << " = " << u[i] << "\n";

  double a1 = (u[0] * u[3] - u[2] * u[1]) / (u[1] * u[1] - u[2] * u[0]);
  double a2 = (u[2] * u[2] - u[3] * u[1]) / (u[1] * u[1] - u[2] * u[0]);

  std::cout << "\nÌíîãî÷ëåí: ";
  std::cout << "x^2 + " << a1 << "*x + " << a2 << "\n";

  std::vector<std::pair<double, double>> Nodes(2);
  double sqrtD = std::sqrt(a1 * a1 - 4 * a2);
  double x1 = Nodes[0].first = (-a1 + sqrtD) / 2;
  double x2 = Nodes[1].first = (-a1 - sqrtD) / 2;
  double A1 = Nodes[0].second = (u[1] - x2 * u[0]) / (x1 - x2);
  double A2 = Nodes[1].second = (u[1] - x1 * u[0]) / (x2 - x1);

  std::cout << "\nÓçëû è êîýôôèöèåíòû\n";
  std::cout << x1 << "   " << A1 << "\n";
  std::cout << x2 << "   " << A2 << "\n";
  std::cout << "A1 + A2 = " << A1 + A2 << "\n";

  std::function<double(double)> P3([](double x)
  {
    return std::pow(x, 3);
  });

  double Approx = CalcQuadrature(P3, Nodes);
  double Precise = Spx3(b) - Spx3(a);

  std::cout << "\nÇíà÷åíèå èíòåãðàëà p(x) * X^3:\n";
  std::cout << "çíà÷åíèå ÊÔ = " << Approx << "\n";
  std::cout << "òî÷íîå = " << Precise << "\n";
  std::cout << "ïîãðåøíîñòü = " << std::abs(Approx - Precise) << "\n";

  Approx = CalcQuadrature(f, Nodes);

  std::cout << "\nÇíà÷åíèå èíòåãðàëà p(x) * f(x):\n";
  std::cout << "çíà÷åíèå ÊÔ = " << Approx << "\n";

  double m_gauss = 0;
  double N_gauss = 0;

  std::cout << "\nÑðàâíåíèå ñ ÑÊÔ Ãàóññà ñ N óçëàìè:\n";
  std::cout << "Ââåäèòå m: ";
  std::cin >> m_gauss;
  std::cout << "Ââåäèòå N: ";
  std::cin >> N_gauss;

  std::function<double(double)> pf([&p, &f](double x)
  {
    return p(x) * f(x);
  });
  std::vector<std::pair<double, double>> Nodes_gauss = CalcGaussianNodes(N_gauss, e)[N_gauss];
  double h = (b - a) / m_gauss;
  double Approx_gauss = 0;

  for (int i = 0; i < m_gauss; i++)
  {
    double A = a + h * i;
    double B = A + h;

    Approx_gauss += CalcGaussQF(pf, Nodes_gauss, A, B);
  }

  std::cout << "\nÇíà÷åíèå ÑÊÔ = " << Approx_gauss << "\n";
  std::cout << "Ìîäóëü ðàçíîñòè = " << std::abs(Approx - Approx_gauss) << "\n";
}


int main()
{
  SetConsoleOutputCP(1251);
  std::cout << std::setprecision(12) << std::fixed;

  std::function<double(double)> p([](double x)
  {
    return -std::log(x);
  });

  std::function<double(double)> f([](double x)
  {
    return std::sin(x);
  });

  std::function<double(double)> Spx3([](double x)
  {
    if (std::abs(x) > 1e-12)
      return std::pow(x, 4) * (1 - 4 * std::log(x)) / 16;
    else
      return 0.0;
  });

  const double e = 1e-12;


  std::cout << "Lab 6\n";
  std::cout << "ÏÐÈÁËÈÆÅÍÍÎÅ ÂÛ×ÈÑËÅÍÈÅ ÈÍÒÅÃÐÀËÎÂ ÏÐÈ ÏÎÌÎÙÈ ÊÂÀÄÐÀÒÓÐÍÛÕ ÔÎÐÌÓË\n"
               "ÍÀÈÂÛÑØÅÉ ÀËÃÅÁÐÀÈ×ÅÑÊÎÉ ÑÒÅÏÅÍÈ ÒÎ×ÍÎÑÒÈ (ÊÔ ÍÀÑÒ)\n";


  char c = 0;

  do
  {
    std::cout << "\nÂûáåðèòå:\n";
    std::cout << "1 - Âû÷èñëåíèå ïðè ïîìîùè ÑÊÔ Ãàóññà\n";
    std::cout << "2 - Âû÷èñëåíèå ïðè ïîìîùè ÊÔ ÍÀÑÒ\n";

    int Option = GetVariant(1, 2);
    std::function<double(double)> pf([&p, &f](double x)
    {
      return p(x) * f(x);
    });

    switch (Option)
    {
      case 1:
        CompoundGaussQF(pf, e);
        break;

      case 2:
        GaussianTypeQF(p, f, Spx3, e);
        break;
    }

    std::cout << "\nÂûéòè? (y/n)\n";
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');
  } while (c != 'y');

  return 0;
}