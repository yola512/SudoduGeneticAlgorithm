cmake_minimum_required(VERSION 3.30)
project(SudokuGeneticAlgorithm C)

set(CMAKE_C_STANDARD 23)

add_executable(SudokuGeneticAlgorithm main.c sudoku.c utils.c geneticAlgorithm.c)
