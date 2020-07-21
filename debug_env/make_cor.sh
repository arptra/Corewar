#!/bin/bash

dir="../s-linux-mac/*"
cor_files="../s-linux-mac/*.cor"

cp ../vm-champ-linux/asm ./
for file in $dir
do
echo $file
./asm $file
echo
done

mkdir file_cor
mv $cor_files ./file_cor
rm asm
