cmake_minimum_required(VERSION 3.23)
project(telefonkonyv C)

set(CMAKE_C_STANDARD 99)

add_executable(telefonkonyv main.c adatok.c adatok.h vcard.c vcard.h kereses.c kereses.h menu.c menu.h)
