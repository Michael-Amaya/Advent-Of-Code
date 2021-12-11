CC = gcc
CFLAGS = -Wall -Werror -pedantic-errors --std=c99
TARGETS = day1 day2 day3 day4 day5

all: ${TARGETS}

day1: day1.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

day2: day2.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

day3: day3.o utilities.o
	${CC} -o $@ $^ -lm ${CFLAGS}

day4: day4.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

day5: day5.o utilities.o
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -rf ${TARGETS} *.o *~
