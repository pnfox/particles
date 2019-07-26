SHELL = /bin/sh
CXX = g++
CFLAGS = -Wall
SFML = $(shell pkg-config sfml-graphics --libs)

all: particles.o
	$(CXX) $(CFLAGS) $(SFML) -o particles main.cpp particles.o

particles.o:
	$(CXX) $(CFLAGS) $(SFML) -c particles.cpp

clean:
	rm particles *.o
