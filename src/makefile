CC = gcc
CXX = g++
CPPFLAGS = -Wall -O3 -std=c++11
RM = rm -f

SRCS = main.cc preprocessing.cc levenshtein.cc
OBJS = $(subst .cc,.o,$(SRCS))

all: mellon_processing

mellon_processing: $(OBJS)
	$(CXX) $(CPPFLAGS) -o mellon_processing $(OBJS)

main.o: main.cc preprocessing.h
	$(CXX) $(CPPFLAGS) -c main.cc

preprocessing.o: preprocessing.cc preprocessing.h levenshtein.h
	$(CXX) $(CPPFLAGS) -c preprocessing.cc

levenshtein.o: levenshtein.cc levenshtein.h
	$(CXX) $(CPPFLAGS) -c levenshtein.cc

clean:
	$(RM) $(OBJS)
