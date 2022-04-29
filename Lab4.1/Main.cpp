#include <iostream>
#include <cmath>
#include <windows.h>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>



int main()
{
  std::vector<std::function<double (double)>> f
  {
    [](double x) -> double
    {
      return 1.5 * std::exp(-2 * x) + std::sin(x) + 3;
    }
    ,
    [](double x) -> double
    {
      return 30;
    }
    ,
    [](double x) -> double
    {
      return 2 * x + 5;
    }
    ,
    [](double x) -> double
    {
      return 3 * x * x + 1;
    }
    ,
    [](double x) -> double
    {
      return 4 * x * x * x + 3;
    }
  };

  std::vector<std::function<double(double)>> F
  {
    [](double x) -> double
    {
      return -0.75 * std::exp(-2 * x) - std::cos(x) + 3 * x;
    }
    ,
    [](double x) -> double
    {
      return 30 * x;
    }
    ,
    [](double x) -> double
    {
      return x * x + 5 * x;
    }
    ,
    [](double x) -> double
    {
      return x * x * x + x;
    }
    ,
    [](double x) -> double
    {
      return std::pow(x, 4)  + 3 * x;
    }
  };

  std::vector<std::string> fname
  {
    "1.5 * exp(-2 * x) + sin(x) + 3",
    "30",
    "2 * x + 5",
    "3 * x * x + 1",
    "4 * x * x * x + 3"
  };

  SetConsoleOutputCP(1251);
  std::cout << std::fixed << std::setprecision(8);

  std::cout << "Lab 4.1\n";
  std::cout << "ÏÐÈÁËÈÆÅÍÍÎÅ ÂÛ×ÈÑËÅÍÈÅ ÈÍÒÅÃÐÀËÀ ÏÎ ÊÂÀÄÐÀÒÓÐÍÛÌ ÔÎÐÌÓËÀÌ\n";

  char c = 0;
  do
  {
    double a = 0;
    double b = 0;

    std::cout << "Ââåäèòå a: ";
    std::cin >> a;
    std::cout << "Ââåäèòå b: ";
    std::cin >> b;

    std::cout << "Âûáåðèòå ÊÔ:\n";
    std::cout << "1 - ÊÔ ëåâîãî ïðÿìîóãîëüíèêà\n";
    std::cout << "2 - ÊÔ ïðàâîãî ïðÿìîóãîëüíèêà\n";
    std::cout << "3 - ÊÔ ñðåäíåãî ïðÿìîóãîëüíèêà\n";
    std::cout << "4 - ÊÔ òðàïåöèè\n";
    std::cout << "5 - ÊÔ Ñèìïñîíà\n";
    std::cout << "6 - ÊÔ 3/8\n";

    do
    {
      std::cin >> c;
      std::cin.ignore(INT_MAX, '\n');
      if (!(c >= '1' && c <= '6'))
        std::cout << "Íåêîððåêòíûé âàðèàíò\n";
    } while (!(c >= '1' && c <= '6'));

    std::cout << "\n";
    for (int i = 0; i < f.size(); i++)
    {
      double Approx = 0;
      double Precise = F[i](b) - F[i](a);

      switch (c)
      {
        case '1':
          Approx = (b - a) * f[i](a);
          break;

        case '2':
          Approx = (b - a) * f[i](b);
          break;

        case '3':
          Approx = (b - a) * f[i]((a + b) / 2);
          break;

        case '4':
          Approx = (b - a) * (f[i](a) + f[i](b)) / 2;
          break;

        case '5':
          Approx = (f[i](a) + 4 * f[i]((a + b) / 2) + f[i](b)) * (b - a) / 6;
          break;

        case '6':
          double h = (b - a) / 3;
          Approx = (f[i](a) + 3 * f[i](a + h) + 3 * f[i](b - h) + f[i](b)) * (b - a) / 8;
          break;
      }

      std::cout << "f(x) = " << fname[i] << "\n";
      std::cout << "Ïðèáëèæåííîå = " << Approx << "\n";
      std::cout << "Ïîãðåøíîñòü = " << std::abs(Approx - Precise) << "\n\n";
    }

    std::cout << "Âûéòè? (y/n)\n";
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');
  } while (c != 'y');

  return 0;
}