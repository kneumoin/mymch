all: mymch

CC=g++
CFLAGS=-std=c++11 -g -Wall

all: clean context functions mymch
	$(CC) $(CFLAGS) mymch.o functions.o context.o -o mymch

context:
	$(CC) $(CFLAGS) -c context.cpp

functions:
	$(CC) $(CFLAGS) -c functions.cpp

mymch:
	$(CC) $(CFLAGS) -c mymch.cpp

test:
	python tests/test.py

clean:
	rm -rf *.o mymch
