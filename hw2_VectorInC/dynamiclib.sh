gcc -fpic -shared vector.c -o libvector.so
gcc -o dynamicvector test.c -L rpath ./libvector.so 