cmake_minimum_required(VERSION 3.18)
project(HFB64_TEST)
add_executable(
  base64_test

  src/gtest-all.cc
  base64_test.cc

  test_base64.cc
)
include_directories(. .. include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
target_compile_features(base64_test PUBLIC cxx_std_17)
add_compile_options("-g -Wall -Wextra -fexceptions")
target_link_libraries(base64_test pthread)
