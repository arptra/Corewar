#!/bin/bash

dir="file_cor/*"
for file in $dir
do
echo $file
./vm_ref $file
echo
done

