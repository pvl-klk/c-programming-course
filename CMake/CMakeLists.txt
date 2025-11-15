cmake_minimum_required(VERSION 3.10)
project(StackLibrary C)

set(CMAKE_C_STANDARD 11)

add_library(mylib STATIC
    sorting_station.c
    advanced_braces_balance.c
    Stack/stack.c
)

target_include_directories(mylib PUBLIC . Stack)
