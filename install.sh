#!/bin/bash

fpc -B ./Reenterable.lpr
fpc -B ./mpi2reent.lpr
cd ./Grammar
fpc -B -O3 -Mobjfpc -FcUTF-8 ./Grammar.lpr
cp ./libGrammar.so ../
cp ./libGrammar.dylib ../libGrammar.so
cd ..
cd ./link-grammar-5.3.0
unzip ./link-grammar-5.3.0.zip
sh ./configure CPPFLAGS="-I$PWD" CFLAGS="-I$PWD"
make
sudo make install
sudo ldconfig
cd ..
cp /usr/local/lib/liblink-grammar.so.5.3.0 ./liblink-grammar.so
cd Predicates
g++ -o main.o -c main.cpp -fshort-wchar -fPIC -O3 -I/opt/homebrew/include
g++ -shared -o libPredicates.so main.o
cp libPredicates.so ../
cp libPredicates.dylib ../libPredicates.so
cd ..
cd ANTLR
sudo cmake . -DCMAKE_BUILD_TYPE=Release -DANTLR_JAR_LOCATION=./
sudo make
sudo make install
cd plc_cpp
g++ -o lexer_plc *.cpp ../dist/libantlr4-runtime.a -I../runtime/src -O4 -std=c++14 -I/opt/homebrew/include
cp ./lexer_plc ../../
cd ..
cd plc_preproc
g++ -o lexer_preproc *.cpp ../dist/libantlr4-runtime.a -I../runtime/src -O4 -std=c++14 -I/opt/homebrew/include
cp ./lexer_preproc ../../
cd ..
cd ..
chmod +x *.sh   
cd ./prolog_micro_brain.dir
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Running on a Mac"
   `ls /opt/homebrew/bin/g++*` -o prolog_micro_brain tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -ldl -fopenmp -fpermissive
   `ls /opt/homebrew/bin/g++*` -c tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -ldl -fPIC -fopenmp -fpermissive
else
   g++ -o prolog_micro_brain tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -ldl -fopenmp -fpermissive
   g++ -c tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -ldl -fPIC -fopenmp -fpermissive
fi
cp ./prolog_micro_brain ../
cd ..
cd ./PrologIntrf
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Running on a Mac"
    `ls /opt/homebrew/bin/g++*` -o main.o -c main.cpp -fPIC -O4 -std=c++17 -I/opt/homebrew/include -fpermissive -fopenmp
    `ls /opt/homebrew/bin/g++*` -shared -o libPrologIntrf.so main.o ../prolog_micro_brain.dir/*.o -L/opt/homebrew/lib -lm -ldl
else
    g++ -o main.o -c main.cpp -fPIC -O4 -std=c++17 -fpermissive -fopenmp
    g++ -shared -o libPrologIntrf.so main.o ../prolog_micro_brain.dir/*.o -lm -ldl -Wl,--allow-multiple-definition
fi
cp libPrologIntrf.so ../
cp libPrologIntrf.dylib ../libPrologIntrf.so
cd ..
cd ./xpathInduct.dir
fpc -B -O3 -Mobjfpc -FcUTF-8 -fPIC ./xpathInduct.lpr
cp ./libxpathInduct.so ../
cp ./libxpathInduct.dylib ../libxpathInduct.so
cd ..
sudo make
sudo make -f Makefile.mpi
sudo make -f Makefile.clustered
sudo make -f Makefile.vectorized
sudo make -f Makefile.cilk
sudo make -f Makefile.russian
sudo rm -f ./induct.log
