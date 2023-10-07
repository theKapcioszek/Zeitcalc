#!/bin/sh

cd ./raylib/raylib-4.5.0/src
make 
cd ../../../
clang -I./raylib/raylib-4.5.0/src/ -L./raylib/raylib-4.5.0/src/ -l:libraylib.so -o build/januszex src/main.c -v
