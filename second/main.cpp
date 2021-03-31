//
// Created by sergeyampo on 31.03.2021.
//
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
#include <functional>
#include <chrono>
#include <optional>

#include "lib/BlackBoxUnitTest/BlackBoxUnitTest.h"

using namespace std;

std::string solveSystem(double a, double b, double c, double d, double e, double f){
  std::string out;

  if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0))
  {
	out = '5';
  }
  else if ((a * d - c * b != 0) && ((e * d - b * f != 0) || (a * f - c * e != 0)))
  {
	double y = (a * f - c * e) / (a * d - c * b);
	double x = (d * e - b * f) / (d * a - b * c);
	out = "2 " + std::to_string(x) + ' ' + std::to_string(y);
  }
  else if (((a * d - c * b == 0) && ((e * d - b * f != 0) || (a * f - c * e != 0))) ||
	  (a == 0 && c == 0 && e / b != f / d) ||
	  (b == 0 && d == 0 && e / a != f / c) ||
	  (a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0)))
  {
	if (((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
		(c == 0 && d == 0 && f == 0 && b != 0 && a == 0)))
	{
	  double y;
	  if (b == 0)
	  {
		y = f / d;
	  }
	  else if (d == 0)
	  {
		y = e / b;
	  }
	  else if (e == 0 || f == 0){
		y = 0;
	  }
	  out = "4 " + std::to_string(y);
	}
	else if (((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
		(c == 0 && d == 0 && f == 0 && a != 0 && b == 0))){
	  double x;
	  if (a == 0)
	  {
		x = f / c;
	  }
	  else if (c == 0)
	  {
		x = e / a;
	  }
	  else if (e == 0 || f == 0)
	  {
		
		x = 0;
	  }
	  out = "3 " + std::to_string(x);
	}
	else
	  out = '0';
  }
  else if (a == 0 && c == 0)
  {
	double y;
	if (e == 0)
	{
	  y = f / d;
	}
	else if (f == 0)
	{
	  
	  y = e / b;
	}
	else
	{
	  y = e / b;
	}
	out = "4 " + std::to_string(y);
  }
  else if (b == 0 && d == 0)
  {
	double x;
	if (e == 0)
	{
	  x = f / c;
	}
	else if (f == 0)
	{
	  
	  x = e / a;
	}
	else
	{
	  x = e / a;
	}
	out = "3 " + std::to_string(x);
  }
  else if (b == 0 && e == 0)
  {
	double k, n;
	k = -c / d;
	n = f / d;
	out = "1 " + std::to_string(k) + ' ' + std::to_string(n);
  }
  else if (d == 0 && f == 0)
  {
	double k, n;
	k = -a / b;
	n = e / b;
	out = "1 " + std::to_string(k) + ' ' + std::to_string(n);
  }
  else if (a == 0 && e == 0)
  {
	
	double k, n;
	k = -d / c;
	n = f / c;
	out = "1 " + std::to_string(k) + ' ' + std::to_string(n);
  }
  else if (c == 0 && f == 0)
  {
	
	double k, n;
	k = -b / a;
	n = e / a;
	out = "1 " + std::to_string(k) + ' ' + std::to_string(n);
  }
  else if ((a / b == c / d))
  {
	double k, n;
	k = -c / d;
	n = f / d;
	out = "1 " + std::to_string(k) + ' ' + std::to_string(n);
  }
  else
  {
	
	out = "Are you kidding me?";
  }
  return out;
}

void start_tests(auto& solveSystemTest, std::function<std::string(const std::string&)> printStr){
  solveSystemTest.executeTest("zero values", 0, 0, 0, 0, 0, 0, "5", printStr);

  solveSystemTest.executeTest("The only solution", 15, 8,9, 2, 85, 37, "2 3.000000 5.000000", printStr);

  solveSystemTest.executeTest("y = y0, x is aby number. d != 0", 0, 0, 0, 5, 0, 5, "4 1.000000", printStr);
  solveSystemTest.executeTest("y = y0, x is any number. b != 0", 0, 14, 0, 0, 112, 0, "4 8.000000", printStr);

  solveSystemTest.executeTest("x = x0, y is any number. c != 0", 0, 0, 13, 0, 0, 572, "3 44.000000", printStr);
  solveSystemTest.executeTest("x = x0, y is any number. a != 0", 2, 0, 0, 0, 2, 0, "3 1.000000", printStr);

  solveSystemTest.executeTest("No x, y exist", 0, 1, 0, 2, 1, 1, "0", printStr);


  solveSystemTest.executeTest("y = y0, x is any number, a == 0 && c == 0 && e == 0", 0, 3, 0, 5, 0, 0, "4 0.000000", printStr);
  solveSystemTest.executeTest("y = y0, x is any number, a == 0 && c == 0 && e != 0 && f != 0", 0, 9, 0, 5, 27, 15, "4 3.000000", printStr);

  solveSystemTest.executeTest("y = y0, x is any number, b == 0 && d == 0 && e == 0", 3, 0, 5, 0, 0, 0, "3 0.000000", printStr);
  solveSystemTest.executeTest("y = y0, x is any number, b == 0 && d == 0 && e != 0 && f != 0", 9, 0, 5, 0, 27, 15, "3 3.000000", printStr);

  solveSystemTest.executeTest("y = kx + n, b == 0 && e == 0", 0, 0, 18, 2, 0, 66, "1 -9.000000 33.000000", printStr);
  solveSystemTest.executeTest("y = kx + n, d == 0 && f == 0", 3, 9, 0, 0, 54, 0, "1 -0.333333 6.000000", printStr);

  solveSystemTest.executeTest("y = kx + n, a / b = c / d", 3, 6, 6, 12, 9, 18, "1 -0.500000 1.500000", printStr);
}

int main(){
  std::function<std::string(double, double, double, double, double, double)> solveSystemFunc = solveSystem;
  BlackBoxUnitTest<std::string, double, double, double, double, double, double> solveSystemTest(solveSystemFunc);
  auto printStr = [](const std::string& str) -> std::string { return str; };

  start_tests(solveSystemTest, printStr);

  return 0;
}


