CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LDLIBS   = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
VPATH    = ../src:../include
SOURCES  = $(notdir $(wildcard ../src/*.cc))
OBJS     = $(patsubst %.cc, %.o, ${SOURCES})

EXEC = a

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@.out $^ ${LDLIBS}

main.o: main.cc game.o
game.o: game.cc player.o asset_manager.o
player.o: player.cc player.h constants.h asset_manager.o aabb.o
visible_object.o: visible_object.cc visible_object.h
asset_manager.o: asset_manager.cc asset_manager.h texture.o font.o music.o
texture.o: texture.cc texture.h
font.o: font.cc font.h
music.o: music.cc music.h
enemy.o: enemy.cc enemy.h visible_object.o
asteroid.o: asteroid.cc asteroid.h constants.h enemy.o asset_manager.o
blaster.o: blaster.cc blaster.h constants.h enemy.o asset_manager.o
drone.o: drone.cc drone.h
aabb.o: aabb.cc aabb.h
laser.o: laser.cc laser.h visible_object.o
laser_manager.o: laser_manager.cc laser_manager.h

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

clean:
	rm -rf *.o

