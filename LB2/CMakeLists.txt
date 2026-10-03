cmake_minimum_required(VERSION 3.10)
project(CalculatorProject CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Створення статичної бібліотеки calculator_lib
add_library(calculator_lib STATIC calculator.cpp calculator.h)

# 2. Створення виконуваного файлу
add_executable(calculator_app main.cpp)

# 3. Зв'язування (лінковка) виконуваного файлу з бібліотекою
target_link_libraries(calculator_app PRIVATE calculator_lib)
