# Mini makefile

CC = gcc
OPTS = -Wall -o
OBJS = main.o parser.o mini_file.o readline.o strip.o

mini_parser: $(OBJS)
	$(CC) $(OPTS) $@ $^

%.o: %.c
	$(CC) -c $^

clean:
	rm -f *.o
