compile: server client

server: server.c pipe_networking.c
	gcc server.c pipe_networking.c -o server

client: client.c pipe_networking.c
	gcc client.c pipe_networking.c -o client

clean:
	rm -f server client
	rm -f private wkp
	rm -f *.out *.o
	find . -type p -delete