CC = g++
CFLAGS = -Wall -g -O3
LDFLAGS = -lm

client: linkedList.o file.o functions.o network.o terminal.o client.o
	${CC} ${CFLAGS} linkedList.o file.o functions.o network.o terminal.o client.o ${LDFLAGS} -o client

client.o: client.cpp
	${CC} ${CFLAGS} -c client.cpp

terminal.o: terminal.h
	${CC} ${CFLAGS} -c terminal.cpp

functions.o: header.h
	${CC} ${CFLAGS} -c functions.cpp

network.o: network.h
	${CC} ${CFLAGS} -c network.cpp

file.o: file.h
	${CC} ${CFLAGS} -c file.cpp

linkedList.o: linkedList.h
	${CC} ${CFLAGS} -c linkedList.cpp

clean:
	rm -f *.o client
