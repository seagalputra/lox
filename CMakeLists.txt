cmake_minimum_required(VERSION 3.10)

project(Lox C)

add_executable(Lox main.c "parser.h" "parser.c")