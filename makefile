CC=gcc
FLAGS= -o hasm
COMP_FLAGS=-c
SOURCES= assembler.c decode.c hashtable.c parser.c
OBJECTS= assembler.o decode.o hashtable.o parser.o


hasm.exe: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS)
%.o: %.c
	$(CC) $(COMP_FLAGS) $<


