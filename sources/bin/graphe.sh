#!/bin/bash
if [ $# = 1 ]
then
    ./DIMACS_conversion $1
    minisat out.DIMACS out.DIMACS
    ./affichage $1 out.DIMACS
    rm out.DIMACS
else
    echo "il faut le nom du fichier en argument"
fi