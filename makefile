
all: bin
	gcc ./src/simple_server.c -o ./bin/server

bin:
	mkdir bin