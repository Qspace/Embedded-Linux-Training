#!/bin/bash
echo "Chuong trinh doi prefix cua file name"
echo "Tham so 1: prefix cu"
echo "Tham so 2: prefix moi" 
echo "$1 $2"
for file in $1*
do
newFile=${file#$1}
mv "$file" "${newFile}"
mv "$newFile" "$2$newFile"
done
