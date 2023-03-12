#!/bin/bash

fpc -B ./Reenterable.lpr
fpc -B ./mpi2reent.lpr
cd Predicates
g++ -o main.o -c main.cpp -fPIC -O3
g++ -shared -o libPredicates.so main.o
cp libPredicates.so ../
cd ..
cd ANTLR
sudo cmake . -DCMAKE_BUILD_TYPE=Release -DANTLR_JAR_LOCATION=./
sudo make
sudo make install
cd plc_cpp
g++ -o lexer_plc *.cpp ../dist/libantlr4-runtime.a -I../runtime/src -O4 -std=c++14
cp ./lexer_plc ../../
cd ..
cd plc_preproc
g++ -o lexer_preproc *.cpp ../dist/libantlr4-runtime.a -I../runtime/src -O4 -std=c++14
cp ./lexer_preproc ../../
cd ..
cd ..
chmod +x *.sh   
make
make -f Makefile.mpi
