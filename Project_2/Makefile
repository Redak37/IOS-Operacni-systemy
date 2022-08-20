#/*
# *  Soubor:      Makefile
# *  Řešení:      IOS - Projekt 2
# *  Autor:       Radek Duchon - xducho07, VUT FIT 1BIT 2017/18
# *  Přeloženo:   gcc 6.4.0
# *  Datum:       30.4.2018
# */

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
LDLIBS = -lpthread
TARGETS = proj2

all: $(TARGETS)

proj2: bus.o rider.o semaphores.o
	$(CC) $(CFLAGS) proj2.c bus.c rider.c semaphores.c $(LDLIBS) -o proj2

clean: 
	@rm -f *.o proj2

zip:
	zip proj2.zip *.c *.h Makefile
