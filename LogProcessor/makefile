CC = g++
CFLAGS = -Wall -g -O3
LDFLAGS = -lm

processor: KeyLogProcessor.o main.o
	${CC} ${CFLAGS} KeyLogProcessor.o main.o ${LDFLAGS} -o processor

KeyLogProcessor.o: KeyLogProcessor.h
	${CC} ${CFLAGS} -c KeyLogProcessor.cpp

main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean:
	rm -f *.o processor
