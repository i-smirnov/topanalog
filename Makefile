CFLAGS=-Wall -g

all: 
	rm -f topc
	g++ topc.cpp -o topc	
clean:
	rm -f topc
topc:
	g++ topc.cpp -o topc
	

