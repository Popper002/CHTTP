CC= gcc
CFLAGS = 
PORT = 8085 
ACCESS_LOG = access.log
all:
	$(CC) src/server.c -o server
	./server $(PORT) $(ACCESS_LOG) 

