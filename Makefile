CFLAGS=-Wall -g

all: 	clean
prog:
	g++ topc.cpp -o topc

clean:
	rm -f topc

