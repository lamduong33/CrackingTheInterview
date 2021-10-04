##
# Cracking The Coding Interview - C++
# Author: Lam Duong
#
# @file
# @version 0.1

CXXFLAGS = -std=c++20 -g
CC = clang++

TARGET = Cracking
all: $ (TARGET)
$ (TARGET): $(TARGET).cpp
	$(CC) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp
clean:
	$(RM) $(TARGET)

# end
