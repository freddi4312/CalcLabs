#include <iostream>
#include <cmath>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <algorithm>
#include <string>
#include "Header.h"


int main()
{
  double (*f)(double) = [](double x) -> double 
  {
    return 1 - std::exp(-2 * x); 
  //  return std::pow(x, 5);
  };

  SetConsoleOutputCP(1251);
  std::cout << std::fixed << std::setprecision(14);

  std::cout << "Lab 2\n";
  std::cout << "���������������� �� ��������� �������\n";
  std::cout << "������� 5\n\n";
  std::cout << "������� ������ ������� (m + 1): ";

  int M = 0;
  std::cin >> M;
  M--;

  std::cout << "������� a: ";
  double a = 0;
  std::cin >> a;

  std::cout << "������� b: ";
  double b = 0;
  std::cin >> b;

  char c = 0;
  TABLE Table;

  std::cout << "�������� �������.\n";
  std::cout << "1 - � ��������������� ������\n";
  std::cout << "2 - � ���������� ������\n";
    
  do
  {
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');
    //std::getline(std::cin, std::string{}, '\n');

    switch (c)
    {
      case '1':
        Table = EqSpacedTable(f, a, b, M);
        break;

      case '2':
        Table = RandomTable(f, a, b, M);
        break;
    }

    if (c != '1' && c != '2')
      std::cout << "������������ ��������\n";

  } while (c != '1' && c != '2');

  std::cout << "\n�������\n";
  for (std::pair<double, double> const &p : Table)
    std::cout << p.first << "   " << p.second << "\n";

  do
  {
    std::cout << "\n������� x: ";
    double x = 0;
    std::cin >> x;
    
    double N = 0;
    do
    {
      std::cout << "������� ������� ���������� n <= " << M << ": ";
      std::cin >> N;
      if (N > M)
        std::cout << "������� ������������ �������� n\n";

    } while (N > M);

    std::sort(Table.begin(), Table.end(), [x](std::pair<double, double> const &a, std::pair<double, double> const &b) -> bool
    {
      return std::abs(a.first - x) < std::abs(b.first - x);
    });

    std::cout << "\n��������� n + 1 ����:\n";
    for (int j = 0; j < N + 1; j++)
      std::cout << Table[j].first << "   " << Table[j].second << "\n";

    double Value = Langrange(Table, N, x);
    std::cout << "\n�������� �� �������� = " << Value << "\n";
    std::cout << "����������� ����������� = " << std::abs(Value - f(x)) << "\n";

    Value = Newton(Table, N, x);
    std::cout << "\n�������� �� ������� = " << Value << "\n";
    std::cout << "����������� ����������� = " << std::abs(Value - f(x)) << "\n";

    std::cout << "\n�������� ��� ���� ������������? (y/n)\n";
    std::cin >> c;
  } while (c != 'n');

  return 0;
}