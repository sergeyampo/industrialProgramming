//
// Created by sergeyampo on 31.03.2021.
//

#ifndef INDUSTRIALPROGRAMMINGSECOND_SECOND_LIB_BLACKBOXUNITTEST_BLACKBOXUNITTEST_H_
#define INDUSTRIALPROGRAMMINGSECOND_SECOND_LIB_BLACKBOXUNITTEST_BLACKBOXUNITTEST_H_
#include <string>
#include <optional>

template <class RetT, class ...Args>
class BlackBoxUnitTest{
  std::function<RetT(Args...)> function;
  std::tuple<std::string, bool, std::optional<RetT>> isFunctionCorrect(Args... args, RetT expected);
  std::string functionThrowsExceptionCheck(Args... args);
  int counter;
 public:
  BlackBoxUnitTest() = delete;
  BlackBoxUnitTest(BlackBoxUnitTest& a) = delete;
  BlackBoxUnitTest(std::function<RetT(Args...)> function) : function(function), counter(1) {}
  void executeTest(std::string definition, Args... args);
  void executeTest(std::string definition, Args... args, RetT expected, std::function<std::string(RetT)> retToStringParser);
};

#include "BlackBoxUnitTest.cpp"
#endif //INDUSTRIALPROGRAMMINGSECOND_SECOND_LIB_BLACKBOXUNITTEST_BLACKBOXUNITTEST_H_
