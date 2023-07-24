CC=gcc
CXX=g++
CFLAGS=-g -Wall
LDLIBS= -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl


SRC_DIR := src
OBJ_DIR := build
SRC := $(wildcard $(SRC_DIR)/*.cpp)
C_SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
C_OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRC))

BIN := out

.PHONY: all clean

all: $(BIN) 

$(BIN): $(OBJ) $(C_OBJ)
	$(CXX) $^ $(CFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/* $(BIN)
