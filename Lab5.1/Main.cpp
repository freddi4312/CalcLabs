#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <string>
#include <sstream>
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
      std::cout << "Некорректный вариант\n";
  } while (!(Option >= min && Option <= max));

  return Option;
}


double CalculateQuadrature(std::function<double(double)> const &f, std::vector<std::pair<double, double>> const &Nodes)
{
  double Result = 0;

  for (std::pair<double, double> const &p : Nodes)
    Result += f(p.first) * p.second;

  return Result;
}


std::vector<int> GetSetOfN()
{
  std::string Str;
  std::istringstream StrIn;
  std::vector<int> N;
  int n;

  std::cout << "\nВведите набор N: ";
  std::getline(std::cin, Str, '\n');
  StrIn = std::istringstream(Str);

  while (StrIn >> n)
    N.push_back(n);

  return N;
}


void CheckPrecision(std::vector<std::vector<std::pair<double, double>>> const &Nodes)
{
  std::vector<int> N_check = GetSetOfN();

  for (int n : N_check)
  {
    if (n < Nodes.size() && n > 0)
    {
      POLYNOM X(std::vector<double>{0, 1});
      POLYNOM Pn(1);

      for (int i = 0; i < 2 * n - 1; i++)
        Pn = Pn * X;

      POLYNOM SPn = Pn.integr();

      std::function<double(double)> P([&Pn](double x) {return Pn(x); });

      double Approx = CalculateQuadrature(P, Nodes[n]);
      double Precise = SPn(1) - SPn(-1);
      double Error = std::abs(Approx - Precise);

      std::cout << "\nN = " << n << "\n";
      std::cout << "f(x) = x^" << 2 * n - 1 << "\n";
      std::cout << "Точное значение = " << Precise << "\n";
      std::cout << "Квадратурное значение = " << Approx << "\n";
      std::cout << "Фактическая погрешность = " << Error << "\n";
    }
  }
}


void CalculateGaussianQF(std::function<double(double)> const &f, std::vector<std::vector<std::pair<double, double>>> const &Nodes)
{
  std::vector<int> N_check = GetSetOfN();
  char c = 0;

  do
  {
    double a = 0;
    double b = 0;

    std::cout << "Введите a: ";
    std::cin >> a;
    std::cout << "Введите b: ";
    std::cin >> b;

    for (int n : N_check)
    {
      if (n < Nodes.size() && n > 0)
      {
        std::vector<std::pair<double, double>> NodesAB(n);

        double q = (b - a) / 2;
        for (int i = 0; i < n; i++)
        {
          NodesAB[i].first = a + q * (Nodes[n][i].first + 1);
          NodesAB[i].second = q * Nodes[n][i].second;
        }

        double Approx = CalculateQuadrature(f, NodesAB);

        std::cout << "\nN = " << n << "\n";
        for (int i = 0; i < n; i++)
        {
          std::cout << NodesAB[i].first << "   ";
          std::cout << NodesAB[i].second << "\n";
        }
        std::cout << "Значение = " << Approx << "\n";
      }
    }

    std::cout << "\nВвести новые a, b? (y/n)\n";
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');
  } while (c != 'n');
}


int main()
{
  SetConsoleOutputCP(1251);
  std::cout << std::setprecision(12) << std::fixed;
  
  std::cout << "Lab 5.1\n";
  std::cout << "КФ ГАУССА, ЕЕ УЗЛЫ И КОЭФФИЦИЕНТЫ\n"
               "ВЫЧИСЛЕНИЕ ИНТЕГРАЛОВ ПРИ ПОМОЩИ КФ ГАУССА\n";

  const double e = 1e-12;
  std::function<double(double)> f([] (double x)
  {
    return std::log(1 + x) / (1 + x * x);
  });

  int N;

  std::cout << "\nВведите максимальное количество узлов N: ";
  std::cin >> N;
  N = (std::max)(1, N);

  std::vector<std::vector<std::pair<double, double>>> Nodes = CalcGaussianNodes(N, e);
  for (int n = 1; n <= N; n++)
  {
    std::cout << "\nN = " << n << "\n";
    for (int i = 0; i < n; i++)
      std::cout << Nodes[n][i].first << "   " << Nodes[n][i].second << "\n";

  }

  char c = 0;
  do
  {
    std::cout << "\nВыберите:\n";
    std::cout << "1 - Проверка точности\n";
    std::cout << "2 - Вычисление интеграла ln(1 + x) / (1 + x^2)\n";

    int Option = GetVariant(1, 2);

    switch (Option)
    {
      case 1:
        CheckPrecision(Nodes);
        break;

      case 2:
        CalculateGaussianQF(f, Nodes);
        break;
    }
    


    std::cout << "Выйти? (y/n)\n";
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');
  } while (c != 'y');

  return 0;
}