cmake_minimum_required(VERSION 3.23)
project(telefonkonyv C)

set(CMAKE_C_STANDARD 99)

add_executable(telefonkonyv main.c megjelenites.c megjelenites.h adatok.c adatok.h)
