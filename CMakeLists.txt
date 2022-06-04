cmake_minimum_required(VERSION 3.22)
project(Facile)

set(CMAKE_CXX_STANDARD 17)

add_executable(Facile main.cpp CharList.h SyntaxList.h MapList.h Scanner.h Scanner.cpp pujado.go Parser.h SyntaxType.h Compilation.h)
