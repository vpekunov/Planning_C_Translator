#!/bin/bash

MAXSZ=16384; export MAXSZ

./prolog_micro_brain --query-goal "change_directory('"$1"')" --query-goal "consult('"$2"')" --query-goal "tell('"$3"')" --query-goal $4 --query-goal "told" --query-goal "tell('_alive.pl')" --query-goal "saveLF" --query-goal "told" --query-goal "end_of_file" >$5
