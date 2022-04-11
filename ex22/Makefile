CFLAGS=-Wall -g -DNDEBUG

all: ex22 ex22_main

ex22: ex22.c
	gcc -c -o ex22.o ex22.c

ex22_main: ex22_main.c
	gcc ex22_main.c ex22.o -o ex22_main

clean:
	rm -f ex22.o ex22_main