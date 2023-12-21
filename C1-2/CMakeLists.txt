cmake_minimum_required(VERSION 3.25)
project(C1_2 C)

set(CMAKE_C_STANDARD 90)

add_executable(C1_2 BigNumber.c MillerRobinPrime.c C1Tests.c)
