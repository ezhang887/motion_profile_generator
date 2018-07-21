GTEST_LIB = gtest
GTEST_INCLUDE = /usr/local/include

CC = g++
CFLAGS = -Wall -std=c++11 -I./include/ -I $(GTEST_INCLUDE)
LD_FLAGS = -L /usr/local/lib -l $(GTEST_LIB) -l pthread

TARGET = mp_tests

SRC = $(wildcard src/*.cpp) $(wildcard test/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
DEPS = $(wildcard include/*.h)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LD_FLAGS) 

clean:
	rm -f $(TARGET) $(OBJ)

valgrind:
	make
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)
