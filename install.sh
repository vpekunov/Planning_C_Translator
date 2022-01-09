#!/bin/bash

fpc -B Reenterable.lpr
fpc -B mpi2reent.lpr
cd Predicates
g++ -o main.o -c main.cpp -fPIC -O3
g++ -shared -o libPredicates.so main.o
cp libPredicates.so ../
cd ..
chmod +x *.sh   
