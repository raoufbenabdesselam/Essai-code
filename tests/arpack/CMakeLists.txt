cmake_minimum_required(VERSION 3.3.0)
include(../setup_testsubproject.cmake)
project(testsuite CXX)
if(DEAL_II_WITH_ARPACK)
  deal_ii_pickup_tests()
endif()
