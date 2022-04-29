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

  std::cout << "Lab 3.1\n";
  std::cout << "ЗАДАЧА ОБРАТНОГО ИНТЕРПОЛИРОВАНИЯ\n";
  std::cout << "Вариант 5\n\n";

  double a = 0;
  double b = 0;
  TABLE Table = TableCreation(f, a, b);
  
  char c = 0;
  do
  {
    std::cout << "\nВыберете способ решения задачи:\n";
    std::cout << "1 - через обратную функцию (таблично заданная функция должна быть строго монотонна!)\n";
    std::cout << "2 - построение интерполяционного многочлена с последующим методом секущих\n";

    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');

    switch (c)
    {
      case '1':
        ReverseInterpolationMethod1(Table, f);
        break;

      case '2':
        ReverseInterpolationMethod2(Table, f);
        break;

      default:
        std::cout << "Некорректное значение\n";
    }

    std::cout << "Выйти? (y/n)\n"; 
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');

  } while (c != 'y');

  return 0;
}


TABLE TableCreation(double (*f)(double), double &a, double &b)
{
  std::cout << "Введите размер таблицы (m + 1): ";

  int M = 0;
  std::cin >> M;
  M--;

  std::cout << "Введите a: ";
  std::cin >> a;

  std::cout << "Введите b: ";
  std::cin >> b;

  char c = 0;
  TABLE Table;

  std::cout << "Выберите таблицу:\n";
  std::cout << "1 - с равноотстоящими узлами\n";
  std::cout << "2 - с рандомными узлами\n";

  do
  {
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');

    switch (c)
    {
      case '1':
        Table = EqSpacedTable(f, a, b, M);
        break;

      case '2':
        Table = RandomTable(f, a, b, M);
        break;

      default:
        std::cout << "Некорректное значение\n";
    }

  } while (c != '1' && c != '2');

  std::cout << "\nТаблица\n";
  for (std::pair<double, double> const &p : Table)
    std::cout << p.first << "   " << p.second << "\n";

  return Table;
}


void ReverseInterpolationMethod1(TABLE Table, double (*f)(double))
{
  int M = Table.size() - 1;
  char c = 0;

  do
  {
    std::cout << "\nВведите значение F: ";
    double F = 0;
    std::cin >> F;

    int N = 0;
    do
    {
      std::cout << "Введите степень многочлена n <= m: ";
      std::cin >> N;
      if (N > M)
        std::cout << "Введено недопустимое значение n\n";

    } while (N > M);

    for (std::pair<double, double> &p : Table)
      std::swap(p.first, p.second);

    std::sort(Table.begin(), Table.end(), [F](std::pair<double, double> const &a, std::pair<double, double> const &b) -> bool
      {
        return std::abs(a.first - F) < std::abs(b.first - F);
      });

    std::cout << "\nБлижайшие к F n + 1 узлы перевернутой таблицы:\n";
    for (int j = 0; j < N + 1; j++)
      std::cout << Table[j].first << "   " << Table[j].second << "\n";

    double x = Newton(Table, N, F);
    std::cout << "\nЗначение по Ньютону = " << x << "\n";
    std::cout << "Модуль невязки = " << std::abs(f(x) - F) << "\n";

    std::cout << "\nПровести еще одну обратную интерполяцию? (y/n)\n";
    std::cin >> c;
  } while (c != 'n');
}


void ReverseInterpolationMethod2(TABLE Table, double (*f)(double))
{
  int M = Table.size() - 1;
  char c = 0;

  do
  {
    std::cout << "\nВведите значение F: ";
    double F = 0;
    std::cin >> F;
    
    std::cout << "Введите точность e: ";
    double e = 0;
    std::cin >> e;
    
    std::cout << "Введите A: ";
    double A = 0;
    std::cin >> A;
    
    std::cout << "Введите B: ";
    double B = 0;
    std::cin >> B;
    
    int N = 0;
    do
    {
      std::cout << "Введите степень многочлена n <= m: ";
      std::cin >> N;
      if (N > M)
        std::cout << "Введено недопустимое значение n\n";
    
    } while (N > M);
    
    std::sort(Table.begin(), Table.end(), [F](std::pair<double, double> const &a, std::pair<double, double> const &b) -> bool
    {
      return std::abs(a.second - F) < std::abs(b.second - F);
    });

    std::cout << "\nБлижайшие к F n + 1 узлы:\n";
    for (int j = 0; j < N + 1; j++)
      std::cout << Table[j].first << "   " << Table[j].second << "\n";
    
    POLYNOM Pol = NewtonPolynom(Table, N);
    std::function<double (double)> fPol = [&Pol, F](double x) -> double
    {
      return Pol(x) - F; 
    };
    
    std::cout << "\nПолином по n + 1 узлам: " << Pol << "\n";
    
    std::cout << "\nОтделение корней\n";
    std::vector<std::pair<double, double>> Sections = Tabulation(fPol, A, B, std::ceil((B - A) * 100));
    std::cout << "Количество = " << Sections.size() << "\n";
    for (std::pair<double, double> const &p : Sections)
      std::cout << "[" << p.first << ", " << p.second << "]\n";
    
    std::cout << "\n\nМетод секущих\n\n";
    for (std::pair<double, double> const &p : Sections)
    {
      RESULT Result = Secants(p.first, fPol, e);
      std::cout << "Приближенное решение = " << Result.x << "\n";
      std::cout << "|Xm - Xm-1| = " << Result.last << "\n";
      std::cout << "Невязка = " << std::abs(f(Result.x) - F) << "\n";
      std::cout << "\n";
    }
    
    std::cout << "\nПровести еще одну обратную интерполяцию? (y/n)\n";
    std::cin >> c;
  } while (c != 'n');
}