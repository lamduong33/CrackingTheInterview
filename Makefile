##
# Cracking The Coding Interview - C++
# Author: Lam Duong
#
# @file
# @version 0.1

CXXFLAGS = -std=c++20 -g
CC = clang++

TARGET = Cracking
DATASTRUCTURES = DataStructures
all: $ (TARGET)
$ (TARGET): $(TARGET).cpp
	$(CC) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(DATASTRUCTURES).cpp
clean:
	$(RM) $(TARGET)

# end
