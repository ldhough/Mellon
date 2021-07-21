CC = gcc
CXX = g++
CPPFLAGS = -Wall -O3 -std=c++11 -pthread
RM = rm -f
BIN = ../bin/

SRCS = main.cc preprocessing.cc levenshtein.cc password_tree.cc password_node.cc
OBJS = $(subst .cc,.o,$(SRCS))

all: mellon_processing

mellon_processing: $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(BIN)mellon_processing $(OBJS)

main.o: main.cc preprocessing.h password_tree.h
	$(CXX) $(CPPFLAGS) -c main.cc

preprocessing.o: preprocessing.cc preprocessing.h levenshtein.h
	$(CXX) $(CPPFLAGS) -c preprocessing.cc

levenshtein.o: levenshtein.cc levenshtein.h
	$(CXX) $(CPPFLAGS) -c levenshtein.cc

password_tree.o: password_tree.cc password_tree.h password_node.h
	$(CXX) $(CPPFLAGS) -c password_tree.cc

password_node.o: password_node.cc password_node.h
	$(CXX) $(CPPFLAGS) -c password_node.cc

clean:
	$(RM) $(OBJS)
