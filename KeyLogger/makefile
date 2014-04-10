CC = g++
CFLAGS = -Wall -g -O3
LDFLAGS = -lm

logger: functions.o KeyLogger.o main.o
	${CC} ${CFLAGS} functions.o KeyLogger.o main.o ${LDFLAGS} -o logger

KeyLogger.o: KeyLogger.h
	${CC} ${CFLAGS} -c KeyLogger.cpp

functions.o: header.h
	${CC} ${CFLAGS} -c functions.cpp

main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean:
	rm -f *.o logger
