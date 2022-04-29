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
  std::cout << "������������ ������� ���������� ���������\n\n";
  std::cout << "f(x) = x * sin(x) - 1\n";
  std::cout << "A = " << A << "\n";
  std::cout << "B = " << B << "\n";
  std::cout << "e = " << e << "\n\n";
  std::cout << "������� N: ";

  int N = 0;

  std::cin >> N;


  std::cout << "\n1. ��������� ������\n";
  std::vector<std::pair<double, double>> Sections = Tabulation(f, A, B, N);
  std::cout << "���������� = " << Sections.size() << "\n";
  for (std::pair<double, double> const &p : Sections)
    std::cout << "[" << p.first << ", " << p.second << "]\n";
  

  std::cout << "\n\n2a. ����� ��������\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = Bisection(f, p.first, p.second, e);
    std::cout << "��������� ����������� = " << p.first << "\n";
    std::cout << "���� = " << Result.steps << "\n";
    std::cout << "������������ ������� = " << Result.x << "\n";
    std::cout << "����� ���������� ������� = " << Result.last << "\n";
    std::cout << "������� = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }


  std::cout << "\n\n2b. ����� �������\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = Newton(p.first, f, df, e);
    std::cout << "��������� ����������� = " << p.first << "\n";
    std::cout << "���� = " << Result.steps << "\n";
    std::cout << "������������ ������� = " << Result.x << "\n";
    std::cout << "|Xm - Xm-1| = " << Result.last << "\n";
    std::cout << "������� = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }


  std::cout << "\n\n2c. ���������������� ����� �������\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = ModNewton(p.first, f, df, e);
    std::cout << "��������� ����������� = " << p.first << "\n";
    std::cout << "���� = " << Result.steps << "\n";
    std::cout << "������������ ������� = " << Result.x << "\n";
    std::cout << "|Xm - Xm-1| = " << Result.last << "\n";
    std::cout << "������� = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }


  std::cout << "\n\n2d. ����� �������\n\n";
  for (std::pair<double, double> const &p : Sections)
  {
    RESULT Result = Secants(p.first, f, e);
    std::cout << "��������� ����������� = " << p.first << "\n";
    std::cout << "���� = " << Result.steps << "\n";
    std::cout << "������������ ������� = " << Result.x << "\n";
    std::cout << "|Xm - Xm-1| = " << Result.last << "\n";
    std::cout << "������� = " << std::abs(f(Result.x)) << "\n";
    std::cout << "\n";
  }

  return 0;
}