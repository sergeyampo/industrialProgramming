//
// Created by sergeyampo on 31.03.2021.
//
#include "BlackBoxUnitTest.h"
#include <iostream>
#include <chrono>
#include <tuple>
#include <functional>

using namespace std;
using namespace chrono;

template<class RetT, class ...Args>
string BlackBoxUnitTest<RetT, Args...>::functionThrowsExceptionCheck(Args... args)
{
  try{
	this->function(args...);
  }
  catch (const exception& e)
  {
	return e.what();
  }
  return "";
}

template <class RetT, class ...Args>
tuple<string, bool, optional<RetT>> BlackBoxUnitTest<RetT, Args...>::isFunctionCorrect(Args... args, RetT expected){
  RetT result;
  try
  {
	result = this->function(args...);
  }
  catch (exception e){
	return make_tuple(string(e.what()), 0, nullopt);
  }

  string str = "";
  return make_tuple(str, result == expected, make_optional(result));
}

template <class RetT, class ...Args>
void BlackBoxUnitTest<RetT, Args...>::executeTest(string definition, Args... args)
{
  cout << "Test " + to_string(counter) + ": " + definition;
  chrono::steady_clock::time_point testStart = chrono::steady_clock::now();
  string exceptionStr = functionThrowsExceptionCheck(args...);
  chrono::steady_clock::time_point testEnd = chrono::steady_clock::now();
  chrono::duration<double> elapsedTime = chrono::duration_cast<chrono::duration<double>>(testEnd - testStart);
  cout << " finished in " + to_string(elapsedTime.count()) + " seconds.\n";

  if (exceptionStr == "")
  {
	cout << "Test passed.\n\n";
  }
  else
  {
	cout << "Test failed. Exception thrown: " + exceptionStr + "\n\n\n";
  }

  counter++;
}

template <class RetT, class ...Args>
void BlackBoxUnitTest<RetT, Args...>::executeTest(string definition, Args... args, RetT expected, std::function<string(RetT)> retToStringParser){
  cout << "Test " + to_string(counter) + ": " + definition;
  chrono::steady_clock::time_point testStart = chrono::steady_clock::now();
  tuple<string, bool, optional<RetT>> testPassed = isFunctionCorrect(args..., expected);
  chrono::steady_clock::time_point testEnd = chrono::steady_clock::now();
  chrono::duration<double> elapsedTime = chrono::duration_cast<chrono::duration<double>>(testEnd - testStart);
  cout << " finished in " + to_string(elapsedTime.count()) + " seconds.\n";

  if (get<0>(testPassed) != "")
  {
	cout << "Exception thrown: " << get<0>(testPassed) << "\n\n\n";
	return;
  }

  if (get<1>(testPassed))
  {
	cout << "Test passed!\n\n";
  }
  else
  {
	cout << "Test failed! Function returned:\n";
	cout << retToStringParser(get<2>(testPassed).value()) << "\n\n\n";
  }

  counter++;
}
