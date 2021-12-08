CC = gcc
CFLAGS = -Wall -Werror -pedantic-errors --std=c99
TARGETS = day1 day2

all: ${TARGETS}

day1: day1.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

day2: day2.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${TARGETS} *.o *~
