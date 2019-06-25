#!/bin/sh
echo "Chuong trinh tao/xoa file"
echo "$1"
if [ $1 -eq 1 ]
then
	echo "Chuong trinh tao file"
	echo "Nhap so luong file can tao"
	read num_file
	echo $num_file
#	for x in {0..}
#	do
#		echo "Tao file $x"
#		touch hitech$x.txt
#	done
	dem=0
	while [ $dem -lt $num_file ]
	do
        	echo "While Dem="$dem
		touch hitech$dem.txt
        	let "dem=$dem+1"
	done

else
	echo "Xoa file"
	rm -f *.txt
fi
