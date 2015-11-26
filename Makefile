all:
	gcc -g -Wall -pthread files.c -lpthread -o files
clean:
	rm files
