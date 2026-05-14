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
   g++ -o prolog_micro_brain tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_system -lboost_filesystem -ldl -I/opt/homebrew/include -L/opt/homebrew/lib -fpermissive
   if [ $? -ne 0 ]; then
      g++ -o prolog_micro_brain tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_filesystem -ldl -I/opt/homebrew/include -L/opt/homebrew/lib -fpermissive
   fi
   g++ -c tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_system -lboost_filesystem -ldl -fPIC -I/opt/homebrew/include -L/opt/homebrew/lib -fpermissive
   if [ $? -ne 0 ]; then
      g++ -c tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_filesystem -ldl -fPIC -I/opt/homebrew/include -L/opt/homebrew/lib -fpermissive
   fi
else
   g++ -o prolog_micro_brain tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_system -lboost_filesystem -ldl -fopenmp -fpermissive
   if [ $? -ne 0 ]; then
      g++ -o prolog_micro_brain tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_filesystem -ldl -fopenmp -fpermissive
   fi
   g++ -c tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_system -lboost_filesystem -ldl -fPIC -fopenmp -fpermissive
   if [ $? -ne 0 ]; then
      g++ -c tinyxml2.cpp elements.cpp prolog_micro_brain.cpp -std=c++17 -O4 -lm -lboost_filesystem -ldl -fPIC -fopenmp -fpermissive
   fi
fi
cp ./prolog_micro_brain ../
cd ..
cd ./PrologIntrf
g++ -o main.o -c main.cpp -fPIC -O4 -std=c++17 -I/opt/homebrew/include -fpermissive
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Running on a Mac"
    g++ -shared -o libPrologIntrf.so main.o ../prolog_micro_brain.dir/*.o -L/opt/homebrew/lib -lm -lboost_system -lboost_filesystem -ldl
    if [ $? -ne 0 ]; then
       g++ -shared -o libPrologIntrf.so main.o ../prolog_micro_brain.dir/*.o -L/opt/homebrew/lib -lm -lboost_filesystem -ldl
    fi
else
    g++ -shared -o libPrologIntrf.so main.o ../prolog_micro_brain.dir/*.o -lm -lboost_system -lboost_filesystem -ldl -Wl,--allow-multiple-definition
    if [ $? -ne 0 ]; then
       g++ -shared -o libPrologIntrf.so main.o ../prolog_micro_brain.dir/*.o -lm -lboost_filesystem -ldl -Wl,--allow-multiple-definition
    fi
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
