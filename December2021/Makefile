CC = gcc
CFLAGS = -Wall -Werror -pedantic-errors --std=c99
TARGETS = day1 day2 day3

all: ${TARGETS}

day1: day1.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

day2: day2.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

day3: day3.o utilities.o
	${CC} -o $@ $^ -lm ${CFLAGS}

clean:
	rm -rf ${TARGETS} *.o *~
