CXX      = g++-4.9
CXXFLAGS = -std=c++11 -Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -pedantic -g
LDLIBS   = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
VPATH    = ../src:../inc

all: main

main: unit_test.o player.o visible_object.o asset_manager.o texture.o
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDLIBS}

player.o: player.cc player.h
unit_test.o: unit_test.cc
visible_object.o: visible_object.cc visible_object.h
asset_manager.o: asset_manager.cc asset_manager.h
texture.o: texture.cc texture.h

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

clean:
	rm -rf *.o
