#include <iostream>
#include <cmath>
#include <windows.h>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>


struct FUNC
{
  FUNC(double (*f)(double), double (*F)(double), std::string name) :
    f(f),
    F(F),
    name(name)
  {}

  double (*f)(double);
  double (*F)(double);
  std::string name;
};

std::vector<FUNC> Func
{
  FUNC
  (
    [](double x) -> double
    {
      return std::exp(0.5 * x);
    }
    ,
    [](double x) -> double
    {
      return 2 * std::exp(0.5 * x);
    }
    ,
    "exp(0.5 * x)"
  )
  ,
  FUNC
  (
    [](double x) -> double
    {
      return 1.5 * std::exp(-2 * x) + std::sin(x) + 3;
    }
    ,
    [](double x) -> double
    {
      return -0.75 * std::exp(-2 * x) - std::cos(x) + 3 * x;
    }
    ,
    "1.5 * exp(-2 * x) + sin(x) + 3"
  )
  ,
  FUNC
  (
    [](double x) -> double
    {
      return 30;
    }
    ,
    [](double x) -> double
    {
      return 30 * x;
    }
    ,
    "30"
  )
  ,
  FUNC
  (
    [](double x) -> double
    {
      return 2 * x + 5;
    }
    ,
    [](double x) -> double
    {
      return x * x + 5 * x;
    }
    ,
    "2 * x + 5"
  )
  ,
  FUNC
  (
    [](double x) -> double
    {
      return 3 * x * x + 1;
    }
    ,
    [](double x) -> double
    {
      return x * x * x + x;
    }
    ,
    "3 * x * x + 1"
  )
  ,
  FUNC
  (
    [](double x) -> double
    {
      return 4 * x * x * x + 3;
    }
    ,
    [](double x) -> double
    {
      return std::pow(x, 4) + 3 * x;
    }
    ,
    "4 * x * x * x + 3"
  )
};


std::vector<std::function<double(double)>> ExpDer
{
  [](double x) -> double
  {
    return std::exp(0.5 * x);
  }
  ,
  [](double x) -> double
  {
    return 0.5 * std::exp(0.5 * x);
  }
  ,
  [](double x) -> double
  {
    return 0.25 * std::exp(0.5 * x);
  }
  ,
  [](double x) -> double
  {
    return 0.125 * std::exp(0.5 * x);
  }
  ,
  [](double x) -> double
  {
    return 0.0625 * std::exp(0.5 * x);
  }
};


struct METHOD
{
  METHOD(std::string name, int AST, double constant) :
    name(name),
    AST(AST),
    constant(constant)
  {}

  std::string name;
  int AST;
  double constant;
};


std::vector<METHOD> Method
{
  METHOD("СКФ левых прямоугольников", 0, 1 / 2.0),
  METHOD("СКФ правых прямоугольников", 0, 1 / 2.0),
  METHOD("СКФ средних прямоугольников", 1, 1 / 24.0),
  METHOD("СКФ трапеций", 1, 1 / 12.0),
  METHOD("СКФ Симпсона", 3, 1 / 2880.0)
};


std::vector<double> ComputeApprox(double A, double B, int m, double f(double))
{
  std::vector<double> Approx(Method.size());
  double h = (B - A) / m;
  double z = 0;
  double w = 0;
  double q = 0;

  z = f(A) + f(B);
  for (int j = 1; j <= m - 1; j++)
    w += f(A + j * h);
  for (int j = 0; j <= m - 1; j++)
    q += f(A + (j + 0.5) * h);

  Approx[0] = h * (f(A) + w);
  Approx[1] = h * (w + f(B));
  Approx[2] = h * q;
  Approx[3] = (h / 2) * (z + 2 * w);
  Approx[4] = (h / 6) * (z + 2 * w + 4 * q);

  return Approx;
}


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


int main()
{
  SetConsoleOutputCP(1251);
  //std::cout << std::fixed << std::setprecision(14);

  std::cout << "Lab 4.2 & 4.3\n";
  std::cout << "ПРИБЛИЖЕННОЕ ВЫЧИСЛЕНИЕ ИНТЕГРАЛА ПО СОСТАВНЫМ КВАДРАТУРНЫМ ФОРМУЛАМ\n";

  char c = 0;
  do
  {
    double A = 0;
    double B = 0;
    int m = 0;
    int l = 0;

    std::cout << "\nВведите A: ";
    std::cin >> A;
    std::cout << "Введите B: ";
    std::cin >> B;
    std::cout << "Введите m: ";
    std::cin >> m;
    std::cout << "Введите l: ";
    std::cin >> l;

    double h = (B - A) / m;

    std::cout << "Выберите функцию:\n";
    for (int i = 0; i < Func.size(); i++)
      std::cout << i + 1 << " - f(x) = " << Func[i].name << "\n";

    int Option = GetVariant(1, Func.size()) - 1;
   
    std::cout << "\n";
    std::vector<double> Approx = ComputeApprox(A, B, m, Func[Option].f);
    std::vector<double> lApprox = ComputeApprox(A, B, m * l, Func[Option].f);

    for (int i = 0; i < Method.size(); i++)
    {
      double Precise = Func[Option].F(B) - Func[Option].F(A);

      std::cout << Method[i].name << "\n";
      std::cout << "J(h) = " << Approx[i] << "\n";
      std::cout << "|J - J(h)| = " << std::abs(Approx[i] - Precise) << "\n";

      if (Option == 0)
      {
        double constant = Method[i].constant;
        int AST = Method[i].AST;
        double Theory = constant * ExpDer[AST + 1](B) * m * std::pow(h, AST + 2);
        std::cout << "Теоретическая погрешность = " << Theory << "\n";
      }

      std::cout << "J(h/l) = " << lApprox[i] << "\n";
      std::cout << "|J - J(h/l)| = " << std::abs(lApprox[i] - Precise) << "\n";

      double lr = std::pow(l, Method[i].AST + 1);
      double RungeApprox = (lr * lApprox[i] - Approx[i]) / (lr - 1);

      std::cout << "Значение по Рунге = " << RungeApprox << "\n";
      std::cout << "Фактическая погрешность по Рунге = ";
      std::cout << std::abs(RungeApprox - Precise) << "\n";

      std::cout << "\n";
    }

    std::cout << "Выйти? (y/n)\n";
    std::cin >> c;
    std::cin.ignore(INT_MAX, '\n');
  } while (c != 'y');

  return 0;
}