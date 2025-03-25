CC=gcc
BIN_FLAGS= -o hasm
DEBUG_FLAGS=-o hasm -g
COMP_FLAGS=-c
SOURCES= assembler.c decode.c hashtable.c parser.c
OBJECTS= assembler.o decode.o hashtable.o parser.o


hasm.exe: $(OBJECTS)
	$(CC) $(BIN_FLAGS) $(OBJECTS)
%.o: %.c
	$(CC) $(COMP_FLAGS) $<

debug: $(SOURCES)
	$(CC) $(SOURCES) $(DEBUG_FLAGS)

clean:
	rm *.o


