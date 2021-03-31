cmake_minimum_required(VERSION 3.17)

project(BlackBoxUnitTestLib)

add_library(BlackBoxUnitTestLib BlackBoxUnitTest/BlackBoxUnitTest.cpp)

set_target_properties(BlackBoxUnitTestLib PROPERTIES LINKER_LANGUAGE CXX)