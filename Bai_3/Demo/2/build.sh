gcc -c lib.c -o lib.o
gcc -c -DTEST main.c -o main.o
gcc -o test main.o lib.o
