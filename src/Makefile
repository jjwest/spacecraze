CXX = g++-4.9
INCL = ../inc
CXXFLAGS = -std=c++11 -Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -pedantic -g -I ${INCL}
LDLIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: main

main: unit_test.o player.o
	${CXX} ${CXXFLAGS} unit_test.o player.o visible_object.o -o $@ ${LDLIBS}

player.o: player.cc ../include/player.h visible_object.o
unit_test.o: unit_test.cc
visible_object.o: visible_object.cc ../include/visible_object.h

