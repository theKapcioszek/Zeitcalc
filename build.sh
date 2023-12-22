#!/bin/sh

mkdir ./raylib-5.0/build
cd ./raylib-5.0/src
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c rcore.c -o  ../build/rcore.o
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c raudio.c -o ../build/raudio.o
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c rshapes.c -o  ../build/rshapes.o
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c rtextures.c -o ../build/rtextures.o
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c rmodels.c -o ../build/rmodels.o
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c utils.c -o  ../build/utils.o
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c rglfw.c -o ../build/rglfw.o
cc -ggdb -DPLATFORM_DESKTOP -I./ -I./external/glfw/include/ -c rtext.c -o ../build/rtext.o
cd ../build/ 
ar -crs libraylib.a rcore.o raudio.o rshapes.o rtextures.o rmodels.o utils.o rglfw.o rtext.o
cd ../../
cc -o build/zeitcalc src/main.c -I./raylib-5.0/src/ -L./raylib-5.0/build/ -l:libraylib.a -v -lm
