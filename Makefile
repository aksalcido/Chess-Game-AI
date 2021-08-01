# the compiler: g++ for C++
CC = g++
TARGET = out
SRC = src

default: main run

main:
	$(CC) -o $(TARGET) $(SRC)/*.cpp 

run:
	.\out.exe