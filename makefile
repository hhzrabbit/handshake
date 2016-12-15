GCC = gcc -g

all: server.o client.o pipe_networking.o
	$(GCC) -o server.out server.o pipe_networking.o
	$(GCC) -o client.out client.o pipe_networking.o

server.o: server.c
	$(GCC) -c server.c

client.o: client.c
	$(GCC) -c client.c

pipe_networking.o: pipe_networking.c
	$(GCC) -c pipe_networking.c

clean:
	rm -f *~ *.out *.o *.txt
