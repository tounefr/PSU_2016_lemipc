#!/bin/bash

for i in `seq 0 200`; do
  team=$((RANDOM % 5))
  ./lemipc `pwd` $team 2> /dev/null > /dev/null&
done

LD_LIBRARY_PATH=`pwd` ./gui_cli `pwd`
