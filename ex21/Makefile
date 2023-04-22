CFLAGS= -Wall -g -DNDEBUG

all: ex22_main

ex22_main: ex22.o ex22_main.o
	gcc $(CFLAGS) $^ -o $@

ex22.o: ex22.c ex22.h
	gcc $(CFLAGS) -c $< -o $@

ex22_main.o: ex22_main.c ex22.h dbg.h
	gcc $(CFLAGS) -c $< -o $@

clean: 
	rm -rf ex22_main ex22.o ex22_main.o