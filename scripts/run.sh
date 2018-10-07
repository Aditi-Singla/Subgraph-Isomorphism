#! /bin/bash

if [ -f solve2 ]; then
    if [ "$#" == 1 ]; then
        ./solve1 "data/$1.graphs" "data/$1.satinput"
        ./minisat "data/$1.satinput" "data/$1.satoutput"
        ./solve2 "data/$1.satoutput" "data/$1.mapping"
    else
        echo "Illegal number of parameters ($#)"
    fi
else
    echo "Executable not found, run compile.sh first"
fi
