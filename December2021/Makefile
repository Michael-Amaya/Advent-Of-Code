CC = gcc
CFLAGS = -Wall -Werror -pedantic-errors --std=c99
TARGETS = day1

all: ${TARGETS}

day1: day1.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${TARGETS} *.o *~
