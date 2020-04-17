CC = g++-9

INCLUDES =

CXXFLAGS = -g -Wall -O2 $(INCLUDES) -std=c++2a

LDFLAGS = -g

executables = main

objects = main.o 

.PHONY: default
default: $(executables)

.PHONY: clean
clean:
	rm -f *.o main $(objects) $(executables)
