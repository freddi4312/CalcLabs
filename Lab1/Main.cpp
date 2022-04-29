#include <iostream>
#include <cmath>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <fstream>
#include "Header.h"



int main()
{
  auto f = [](double x) {return x * std::sin(x) - 1; };
  auto df = [](double x) {return std::sin(x) + x * std::cos(x); };
  double A = -10;
  double B = 2;
  double e = 1e-5;

  std::ifstream fin("Params.txt");
  if (!fin.is_open())
  {
    std::cout << "File was not opened\n";
    return 0;
  }

  fin >> A >> B >> e;
  fin.close();

  SetConsoleOutputCP(1251);
  std::cout << std::setprecision(8);

  std::cout << "Lab 1:\n";
  std::cout << "Приближенное решение нелинейных уравнений\n\n";
  std::cout << "f(x) = x * sin(x) - 1\n";
  std::cout << "A = " << A << "\n";
  std::cout << "B = " << B << "\n";
  std::cout << "e = " << e << "\n\n";
  std::cout << "Введите N: ";

  int N = 0;

  std::cin >> N;


  std::cout << "\n1. Отделение корней\n";
  std::vector<std::pair<double, double>> Sections = Tabulation(f, A, B, N);
  std::cout << "Количество = " << Sections.size() << "\n";
  for (std::pair<double, double> const &p : Sections)
    std::cout << "[" << p.first << ", " << p.second << "]\n";
  

  std::cout << "\n\n2a. Метод бисекции\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = Bisection(f, p.first, p.second, e);
    std::cout << "Начальное приближение = " << p.first << "\n";
    std::cout << "Шаги = " << Result.steps << "\n";
    std::cout << "Приближенное решение = " << Result.x << "\n";
    std::cout << "Длина последнего отрезка = " << Result.last << "\n";
    std::cout << "Невязка = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }


  std::cout << "\n\n2b. Метод Ньютона\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = Newton(p.first, f, df, e);
    std::cout << "Начальное приближение = " << p.first << "\n";
    std::cout << "Шаги = " << Result.steps << "\n";
    std::cout << "Приближенное решение = " << Result.x << "\n";
    std::cout << "|Xm - Xm-1| = " << Result.last << "\n";
    std::cout << "Невязка = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }


  std::cout << "\n\n2c. Модифицированный метод Ньютона\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = ModNewton(p.first, f, df, e);
    std::cout << "Начальное приближение = " << p.first << "\n";
    std::cout << "Шаги = " << Result.steps << "\n";
    std::cout << "Приближенное решение = " << Result.x << "\n";
    std::cout << "|Xm - Xm-1| = " << Result.last << "\n";
    std::cout << "Невязка = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }


  std::cout << "\n\n2d. Метод секущих\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = Secants(p.first, f, e);
    std::cout << "Начальное приближение = " << p.first << "\n";
    std::cout << "Шаги = " << Result.steps << "\n";
    std::cout << "Приближенное решение = " << Result.x << "\n";
    std::cout << "|Xm - Xm-1| = " << Result.last << "\n";
    std::cout << "Невязка = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }

  return 0;
}