#!/bin/bash

nbr_process=$1

for i in `seq 0 $nbr_process`; do
  team=$((RANDOM % $2))
  echo $team
  ./lemipc `pwd` $team > /dev/null 2> /dev/null&
done
