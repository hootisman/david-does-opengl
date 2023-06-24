CC=gcc
CXX=g++
CFLAGS=-g -Wall
LDLIBS= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

main: main.o
	$(CXX) main.o glad.o $(CFLAGS) $(LDLIBS) -o out

main.o:
	$(CXX) -c ./main.cpp

glad.o:
	$(CXX) -c ./glad.c

clean:
	rm -rf main.o out
