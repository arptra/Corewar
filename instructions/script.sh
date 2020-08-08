#!/bin/bash

dir="*.cor"
for file in $dir
do
echo $file
./corewar -dump 1000 $file | grep "!" -A 1
echo
done
