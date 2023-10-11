#!/usr/bin/env bash
mkdir -p build
cd build

clang++ -std=c++20 --precompile -o ./lib1.pcm ../lib1/lib1.cppm 
clang++ -std=c++20 --precompile -o ./lib2.pcm ../lib2/lib2.cppm 

clang++ -std=c++20 -o modules -fprebuilt-module-path=. ../main.cpp ./lib1.pcm ./lib2.pcm
