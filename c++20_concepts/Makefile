CC = g++-9 

INCLUDES = 

CXXFLAGS = -g -Wall $(INCLUDES) -fconcepts -std=c++2a 

LDFLAGS= -g

executables = main

.PHONY: default
default: $(executables)

$(executables): main.o

.PHONY: clean
clean:
	rm -f *.o main
