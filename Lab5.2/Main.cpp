#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <windows.h>


const double Pi = 3.14159265358979323846264338;


std::vector<int> GetSetOfN()
{
  std::string Str;
  std::istringstream StrIn;
  std::vector<int> N;
  int n;

  std::cout << "\nÂâåäèòå íàáîð N: ";
  std::getline(std::cin, Str, '\n');
  StrIn = std::istringstream(Str);

  while (StrIn >> n)
    N.push_back(n);

  return N;
}


double CalculateQuadratureMeler(std::function<double(double)> const &f, std::vector<double> const &Nodes)
{
  double Result = 0;

  for (double x : Nodes)
    Result += f(x) * Pi / Nodes.size();

  return Result;
}


int main()
{
  SetConsoleOutputCP(1251);
  std::cout << std::setprecision(12) << std::fixed;
  
  std::cout << "Lab 5.2\n";
  std::cout << "ÊÔ ÌÅËÅÐÀ, ÅÅ ÓÇËÛ È ÊÎÝÔÔÈÖÈÅÍÒÛ\n"
    "ÂÛ×ÈÑËÅÍÈÅ ÈÍÒÅÃÐÀËÎÂ ÏÐÈ ÏÎÌÎÙÈ ÊÔ ÌÅËÅÐÀ\n";

  std::function<double(double)> f([](double x)
  {
    return 1 / std::pow(1 + x * x, 0.5);
  });

  char c = 0;

  do {
    std::vector<int> Ns = GetSetOfN();
    
    std::cout << "\nÂû÷èñëåíèå èíòåãðàëà p(x) * f(x), f(x) = 1 / (1 + x^2)^0.5\n\n";

    for (int n : Ns)
    {
      if (n > 0)
      {
        std::vector<double> Nodes(n);
        for (int i = 0; i < n; i++)
          Nodes[i] = std::cos((2 * i + 1) * Pi / (2 * n));

        double Approx = CalculateQuadratureMeler(f, Nodes);

        std::cout << "N = " << n << "\n";
        for (int i = 0; i < n; i++)
          std::cout << Nodes[i] << "\n";

        std::cout << "A = " << Pi / n << "\n";
        std::cout << "Çíà÷åíèå = " << Approx << "\n\n";
      }
    }

    std::cout << "Âûéòè? (y/n)\n";
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');
  } while (c != 'y');

  return 0;
}