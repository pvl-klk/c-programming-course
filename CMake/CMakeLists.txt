cmake_minimum_required(VERSION 3.10)
project(StackLibrary C)

set(CMAKE_C_STANDARD 11)

add_library(mylib STATIC
    sorting_station.c
    advanced_braces_balance.c
    Stack/stack.c
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
endif()

target_include_directories(mylib PUBLIC . Stack)
