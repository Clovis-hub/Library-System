cmake_minimum_required(VERSION 3.16)
project(Library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library main.cpp Book.cpp Book.h Customer.cpp Customer.h Library.cpp Library.h)