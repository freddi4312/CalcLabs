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
  std::cout << "ИНТЕРПОЛИРОВАНИЕ ПО ЗНАЧЕНИЯМ ФУНКЦИИ\n";
  std::cout << "Вариант 5\n\n";
  std::cout << "Введите размер таблицы (m + 1): ";

  int M = 0;
  std::cin >> M;
  M--;

  std::cout << "Введите a: ";
  double a = 0;
  std::cin >> a;

  std::cout << "Введите b: ";
  double b = 0;
  std::cin >> b;

  char c = 0;
  TABLE Table;

  std::cout << "Выберите таблицу.\n";
  std::cout << "1 - с равноотстоящими узлами\n";
  std::cout << "2 - с рандомными узлами\n";
    
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
      std::cout << "Некорректное значение\n";

  } while (c != '1' && c != '2');

  std::cout << "\nТаблица\n";
  for (std::pair<double, double> const &p : Table)
    std::cout << p.first << "   " << p.second << "\n";

  do
  {
    std::cout << "\nВведите x: ";
    double x = 0;
    std::cin >> x;
    
    double N = 0;
    do
    {
      std::cout << "Введите степень многочлена n <= " << M << ": ";
      std::cin >> N;
      if (N > M)
        std::cout << "Введено недопустимое значение n\n";

    } while (N > M);

    std::sort(Table.begin(), Table.end(), [x](std::pair<double, double> const &a, std::pair<double, double> const &b) -> bool
    {
      return std::abs(a.first - x) < std::abs(b.first - x);
    });

    std::cout << "\nБлижайшие n + 1 узлы:\n";
    for (int j = 0; j < N + 1; j++)
      std::cout << Table[j].first << "   " << Table[j].second << "\n";

    double Value = Langrange(Table, N, x);
    std::cout << "\nЗначение по Лагранжу = " << Value << "\n";
    std::cout << "Фактическая погрешность = " << std::abs(Value - f(x)) << "\n";

    Value = Newton(Table, N, x);
    std::cout << "\nЗначение по Ньютону = " << Value << "\n";
    std::cout << "Фактическая погрешность = " << std::abs(Value - f(x)) << "\n";

    std::cout << "\nПровести еще одну интерполяцию? (y/n)\n";
    std::cin >> c;
  } while (c != 'n');

  return 0;
}