#!/bin/sh

cd ./raylib/raylib-4.5.0/src
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c rcore.c -o  ../build/rcore.o
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c raudio.c -o  ../build/raudio.o
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c rshapes.c -o  ../build/rshapes.o
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c rtextures.c -o  ../build/rtextures.o
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c rmodels.c -o  ../build/rmodels.o
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c utils.c -o  ../build/utils.o
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c rglfw.c -o  ../build/rglfw.o
clang -ggdb -DPLATFORM_DESKTOP -I./external/glfw/include/ -c rtext.c -o  ../build/rtext.o 
cd ../../build/
ar -crs libraylib.a rcore.o raudio.o rshapes.o rtextures.o rmodels.o utils.o rglfw.o rtext.o
cd ../../../
clang -I./raylib/raylib-4.5.0/src/ -L./raylib/raylib-4.5.0/build/ -l:libraylib.a -o build/zeitcalc src/main.c -v
