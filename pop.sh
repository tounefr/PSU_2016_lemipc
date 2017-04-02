#!/bin/bash


for i in `seq 0 400`; do
  team=$((RANDOM % 3))
  ./lemipc `pwd` $team 2> /dev/null > /dev/null&
done

LD_LIBRARY_PATH=`pwd` ./gui_cli `pwd`
