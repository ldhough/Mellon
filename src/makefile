CC = gcc
CXX = g++
CPPFLAGS = -Wall -O3 -std=c++11 -pthread
RM = rm -f
BIN = ../bin/

SRCS = main.cc preprocessing.cc levenshtein.cc password_tree.cc password_node.cc utils.cc rules.cc
OBJS = $(subst .cc,.o,$(SRCS))

all: mellon_processing

mellon_processing: $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(BIN)mellon_processing $(OBJS)

main.o: main.cc preprocessing.h password_tree.h utils.h rules.h
	$(CXX) $(CPPFLAGS) -c main.cc

preprocessing.o: preprocessing.cc preprocessing.h levenshtein.h
	$(CXX) $(CPPFLAGS) -c preprocessing.cc

levenshtein.o: levenshtein.cc levenshtein.h
	$(CXX) $(CPPFLAGS) -c levenshtein.cc

password_tree.o: password_tree.cc password_tree.h password_node.h
	$(CXX) $(CPPFLAGS) -c password_tree.cc

password_node.o: password_node.cc password_node.h
	$(CXX) $(CPPFLAGS) -c password_node.cc

utils.o: utils.cc utils.h
	$(CXX) $(CPPFLAGS) -c utils.cc

rules.o: rules.cc rules.h
	$(CXX) $(CPPFLAGS) -c rules.cc

clean:
	$(RM) $(OBJS)
