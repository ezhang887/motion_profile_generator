GTEST_LIB = gtest
GTEST_INCLUDE = /usr/local/include

CC = g++
CFLAGS = -Wall -std=c++11 -I./include/ -I $(GTEST_INCLUDE)
LD_FLAGS = -L /usr/local/lib -l $(GTEST_LIB) -l pthread

TARGET = mp
TARGET_TEST = unit_tests

SRC = $(wildcard src/*.cpp)  
TEST = $(wildcard test/*.cpp)
MAIN = main.cpp
TEST_OBJ = $(patsubst %.cpp, %.o, $(SRC) $(TEST))
MAIN_OBJ = $(patsubst %.cpp, %.o, $(SRC) $(MAIN))
DEPS = $(wildcard include/*.h)

.PHONY: all $(TARGET_TEST) $(TARGET) $(MAIN)

%.o: %.cpp $(SRC) $(TEST) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(MAIN_OBJ)
	$(CC) -o $(TARGET) $(MAIN_OBJ) $(LD_FLAGS) 

$(TARGET_TEST): $(TEST_OBJ)
	$(CC) -o $(TARGET_TEST) $(TEST_OBJ) $(LD_FLAGS) 

all:
	make $(TARGET)
	make $(TARGET_TEST)

clean:
	rm -f $(TARGET) $(TARGET_TEST) $(TEST_OBJ) $(MAIN_OBJ) *.txt

valgrind:
	make all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET_TEST) 

gdb:
	make $(TARGET)
	gdb ./$(TARGET)
