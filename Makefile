CFLAGS=-Wall -g

all: 	clean
topc:
	g++ topc.cpp -o topc
	
clean:
	rm -f topc

