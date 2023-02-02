cmake_minimum_required(VERSION 3.14)
project(ft_containers)

add_subdirectory(UnitTest)

add_executable(ft_containers srcs/main.cpp includes/ft_vector.hpp testfiles/tester.hpp)