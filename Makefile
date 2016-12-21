# Makefile
#
bmp_to_file: main.o
	gcc -o bmp_to_file main.o

main.o: src/main.c
	gcc -c src/main.c -I./src

clean:
	rm -f *.o bmp_to_file
