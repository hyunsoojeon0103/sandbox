CC = g++ 

INCLUDES = 

CXXFLAGS = -g -Wall -O2 $(INCLUDES) -std=c++1z

LDFLAGS= -g

executables = main

objects = main.o bigStruct.o

.PHONY: default
default: $(executables)

$(executables): bigStruct.o

$(objects): bigStruct.h

.PHONY: clean
clean:
	rm -f *.o $(objects) $(executables)
