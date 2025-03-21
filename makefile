CC=gcc
FLAGS= -o hasm
SOURCES= assembler.c decode.c hashtable.c parser.c
build:
	$(CC) $(FLAGS) $(SOURCES)

