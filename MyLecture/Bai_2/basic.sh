#!/bin/bash
#xuat ra man hinh
echo "Hello, I am basher"
#dat bien
ten="LTK"
#in ra gia tri cua bien
echo "Hello "${ten}
#doc gia tri nhap vao
echo "Nhap nam sinh: "
read nam_sinh
echo "Nam sinh cua ban la "${nam_sinh}
a=1
b=2
#thuc hien toan tu
let "c=${a}+${b}"
d=$((${a}+${b}))
#in ket qua
echo "Tong c="${c}
echo "Tong d="$d
#so sanh
#-eq: =
#-lt: <
#-le: <=
#-gt: >
#-ge: >=
if [ $a -ge $b ]
then
	echo "A lon hon hoac bang B"
else
	echo "A nho hon B"
fi
#case statement
sw=6
case $sw in
	1)
		echo "SW1="$sw
		;;
	2|3)
		echo "SW2|3="$sw
		;;
	*)
		echo "SW*="$sw
		;;
esac
#vong while va sleep
dem=1
while [ $dem -le 3 ]
do 
	echo "While Dem="$dem
	let "dem=$dem+1"
	sleep 0.5
done
#vong until
dem=1
until [ $dem -gt 3 ]
do
	echo "Until Dem="$dem
	let "dem=$dem+1"
	sleep 0.5
done
#vong for
chuoi="Day la vong lap for cho chuoi"
for c in $chuoi
do
	echo "For="$c
done
#vong lap range
for x in {1..5}
do
	echo "Range="$x
done
#range co buoc nhay duoc thiet lap
for x in {6..0..2}
do
	echo "Range2="$x
	sleep 0.5
done
#vong co break
for x in {10..0..2}
do
	if [ $x -lt 3 ]
	then
		break
	fi
	echo "Range3="$x
	sleep 0.5
done
#vong co continue
for x in {10..0..2}
do
	if [ $x -gt 5 ]
	then
		continue
	fi
	echo "Range4="$x
	sleep 0.5
done
#vong select
chuoi="opt1 opt2 opt3 opt4 Thoat"
select c in $chuoi
do
	if [ $c == "Thoat" ]
	then
		break
	fi
	echo "Ban da chon "$c
done
