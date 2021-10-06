##
# Cracking The Coding Interview - C++
# Author: Lam Duong
#
# @file
# @version 0.1

# Compiler setup
CXXFLAGS = -std=c++20 -g -Wall -I $(INCDIR)
CXX = clang++

# Directory setup
INCDIR := include
SRCDIR := src
BINDIR := bin

TARGET = Cracking
SRCFILES = $(SRCDIR)/*.cpp
INCFILES = $(INCDIR)/*.hpp
BIN = $(BINDIR)$(TARGET)

all: $(TARGET)
$(TARGET): $(SRCDIR)/$(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRCFILES)
clean:
	$(RM) $(BIN)

# end
