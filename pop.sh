#!/bin/bash

nbr_process=$1
team=$((RANDOM % $2))

for i in `seq 0 $nbr_process`; do
  ./lemipc `pwd` $i > /dev/null 2> /dev/null&
done

./lemipc `pwd` 0