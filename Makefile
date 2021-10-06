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

all: $(TARGET)
$(TARGET): $(SRCDIR)/$(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCFILES)
clean:
	$(RM) $(TARGET)

# end
