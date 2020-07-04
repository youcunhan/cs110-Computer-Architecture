gcc vector.c -c -o vector.o
ar rcs libvector.a vector.o
gcc -o staticvector test.c ./libvector.a