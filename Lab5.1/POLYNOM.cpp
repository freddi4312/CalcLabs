#include "POLYNOM.h"
#include <cmath>


POLYNOM::POLYNOM() {}


POLYNOM::POLYNOM(double a)
{
  A[0] = a;
}


POLYNOM::POLYNOM(std::vector<double> a)
{
  for (unsigned int i = 0; i < a.size(); i++)
    A[i] = a[i];
}


double POLYNOM::operator()(double x)
{
  double Result = 0;

  for (std::pair<int, double> const &p : A)
    Result += p.second * std::pow(x, p.first);

  return Result;
}


POLYNOM POLYNOM::operator+(POLYNOM const &other)
{
  POLYNOM Result(*this);

  for (std::pair<int, double> const &p : other.A)
    Result.A[p.first] += p.second;

  return Result;
}


POLYNOM POLYNOM::operator-(POLYNOM const &other)
{
  POLYNOM Result(*this);

  for (std::pair<int, double> const &p : other.A)
    Result.A[p.first] -= p.second;

  return Result;
}

POLYNOM POLYNOM::operator*(POLYNOM const &other)
{
  POLYNOM Result;

  for (std::pair<int, double> const &p1 : A)
    for (std::pair<int, double> const &p2 : other.A)
      Result.A[p1.first + p2.first] += p1.second * p2.second;

  return Result;
}

std::ostream &operator<<(std::ostream &out, POLYNOM const &pol)
{
  if (pol.A.empty())
  {
    out << "0";
  }
  else
  {
    bool isFirst = true;
    for (std::pair<int, double> const &p : pol.A)
    {
      if (!isFirst)
        out << " + ";

      isFirst = false;
      out << p.second << "*X^" << p.first;
    }
  }
  
  return out;
}


POLYNOM POLYNOM::der()
{
  POLYNOM dP;

  for (std::pair<unsigned int, double> const &p : A)
    if (p.first > 0)
      dP.A[p.first - 1] = p.first * p.second;

  return dP;
}


POLYNOM POLYNOM::integr()
{
  POLYNOM SP;

  for (std::pair<unsigned int, double> const &p : A)
      SP.A[p.first + 1] = p.second / (p.first + 1);

  return SP;
}