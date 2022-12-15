cmake_minimum_required(VERSION 3.23)
project(Speedy_enigma)

set(CMAKE_CXX_STANDARD 14)

add_executable(Speedy_enigma main.cpp Enigma.cpp Enigma.h Graph.cpp Graph.h)
