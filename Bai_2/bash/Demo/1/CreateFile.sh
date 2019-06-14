#!/bin/sh
echo "Chuong trinh tao/xoa file"
echo "$1"
if [ $1 -eq 1 ]
then
	echo "Chuong trinh tao file"
	echo "Nhap so luong file can tao"
	read num_file
	echo $num_file
	for x in {0..$num_file}
	do
		echo $x
		touch hitech$x.txt
	done
else
	echo "Xoa file"
	rm -f *.txt
fi
