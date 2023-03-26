#!/bin/bash

if [[ "$1" != "nocompile" ]] ; then
  cp -f ./$1 ./_.c
  gcc -O2 -o _.exe _.c >_.err
fi;

if [[ "$3" != "" ]] ; then
  ./_.exe >$2 <$3
else
  ./_.exe >$2
fi;

echo $? >_.result
