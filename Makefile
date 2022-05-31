# Copyright 2022 Dumitru Bianca Stefania - 312CA

CFLAGS=-Wall -Wextra -g -std=c99 

build:
	gcc $(CFLAGS) tema2.c linked_list.c hashtable.c functions.c utils.c -o main 

pack:
	zip -FSr 312CA_DumitruBiancaStefania_Tema2.zip README Makefile *.c *.h

clean:
	rm -f tema1

.PHONY: pack clean
