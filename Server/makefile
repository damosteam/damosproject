CC = g++
CFLAGS = -Wall -g -O3
LDFLAGS = -lm

server: file.o linkedList.o Client.o functions.o terminal.o network.o server.o
	${CC} ${CFLAGS} file.o linkedList.o Client.o functions.o terminal.o network.o server.o ${LDFLAGS} -o server

server.o: server.cpp
	${CC} ${CFLAGS} -c server.cpp

terminal.o: terminal.h
	${CC} ${CFLAGS} -c terminal.cpp

network.o: network.h
	${CC} ${CFLAGS} -c network.cpp

functions.o: header.h
	${CC} ${CFLAGS} -c functions.cpp

Client.o: Client.h
	${CC} ${CFLAGS} -c Client.cpp

linkedList.o: linkedList.h
	${CC} ${CFLAGS} -c linkedList.cpp

file.o: file.h
	${CC} ${CFLAGS} -c file.cpp

clean:
	rm -f *.o server
