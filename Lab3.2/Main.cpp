#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cmath>
#include "Header.h"


int main()
{
  SetConsoleOutputCP(1251);
  std::cout << std::fixed << std::setprecision(14);
  
  double (*f)(double) = [](double x)
  {
    return std::exp(1.5 * 1 * x);
  };

  double (*df)(double) = [](double x)
  {
    return 1.5 * std::exp(1.5 * 1 * x);
  };

  double (*ddf)(double) = [](double x)
  {
    return 1.5 * 1.5 * std::exp(1.5 * 1 * x);
  };


  std::cout << "Lab 3.2\n";
  std::cout << "ÍÀÕÎÆÄÅÍÈÅ ÏÐÎÈÇÂÎÄÍÛÕ ÒÀÁËÈ×ÍÎ ÇÀÄÀÍÍÎÉ ÔÓÍÊÖÈÈ "
               "ÏÎ ÔÎÐÌÓËÀÌ ×ÈÑËÅÍÍÎÃÎ ÄÈÔÔÅÐÅÍÖÈÐÎÂÀÍÈß\n";
  std::cout << "Âàðèàíò 5\n";

  char c = 0;

  do
  {
    int M = 0;
    do
    {
      std::cout << "\nÂâåäèòå m: ";
      std::cin >> M;
      if (M < 3)
        std::cout << "Íåêîððåêòíûé ðàçìåð òàáëèöû\n";
    } while (M < 3);

    double a = 0;
    std::cout << "Ââåäèòå a: ";
    std::cin >> a;

    double h = 0;
    std::cout << "Ââåäèòå øàã h: ";
    std::cin >> h;

    TABLE Table = TableWithFixedStep(f, a, h, M);

    std::cout << "\n";

    for (int i = 0; i <= M; i++)
    {
      std::cout << Table[i].first;
      std::cout << "  " << Table[i].second;

      double FirstDer = 0;
      if (i == 0)
      {
        FirstDer = (-3 * Table[i].second + 4 * Table[i + 1].second - Table[i + 2].second) / (2 * h);
      }
      else if (i == M)
      {
        FirstDer = (3 * Table[i].second - 4 * Table[i - 1].second + Table[i - 2].second) / (2 * h);
      }
      else
      {
        FirstDer = (Table[i + 1].second - Table[i - 1].second) / (2 * h);
      }

      std::cout << "  " << FirstDer;
      std::cout << "  " << std::abs(df(Table[i].first) - FirstDer);

      if (i > 0 && i < M)
      {
        double SecondDer = (Table[i + 1].second - 2 * Table[i].second + Table[i - 1].second) / (h * h);
        std::cout << "  " << SecondDer;
        std::cout << "  " << std::abs(ddf(Table[i].first) - SecondDer);
      }

      std::cout << "\n";
    }

    std::cout << "\nÂâåñòè íîâûå ïàðàìåòðû? (y/n)\n";
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');

  } while (c != 'n');

  return 0;
}