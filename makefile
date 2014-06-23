CC := g++
CFLAGS := 

BIN := bin
OBJ := obj
SRC := src

all: $(BIN)/main.exe

$(BIN)/main.exe: $(OBJ)/main.o
	$(CC) $(OBJ)/main.o $(CFLAGS) -o $(BIN)/main.exe

$(OBJ)/main.o: $(SRC)/main.cpp $(SRC)/list.hpp $(SRC)/list.cxx
	$(CC) $< -c -o $*.o
