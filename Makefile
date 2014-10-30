all: mymch

CC=g++
CFLAGS=-std=c++11 -g -Wall

context:
	$(CC) $(CFLAGS) -c context.cpp

functions:
	$(CC) $(CFLAGS) -c functions.cpp

mymch:
	$(CC) $(CFLAGS) -c mymch.cpp

all: context functions mymch
	$(CC) $(CFLAGS) mymch.o functions.o context.o -o mymch

clean:
	rm -rf *.o mymch
