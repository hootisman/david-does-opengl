CC=gcc
CXX=g++
CFLAGS=-g -Wall
LDLIBS= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

main: main.o glad.o
	$(CXX) $^ $(CFLAGS) $(LDLIBS) -o out

glad.o: glad.c
	$(CC) -c $< -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -rf main.o glad.o out
