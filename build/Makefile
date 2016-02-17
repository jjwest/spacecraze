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
player.o: player.cc player.h constants.h asset_manager.o aabb.o laser_manager.o
game_object.o: game_object.cc game_object.h
asset_manager.o: asset_manager.cc asset_manager.h texture.o font.o music.o
texture.o: texture.cc texture.h
font.o: font.cc font.h
music.o: music.cc music.h
enemy.o: enemy.cc enemy.h game_object.o
asteroid.o: asteroid.cc asteroid.h constants.h enemy.o asset_manager.o
blaster.o: blaster.cc blaster.h constants.h enemy.o asset_manager.o
drone.o: drone.cc drone.h
aabb.o: aabb.cc aabb.h
laser.o: laser.cc laser.h game_object.o
laser_manager.o: laser_manager.cc laser_manager.h laser.o
enemy_manager.o: enemy_manager.cc enemy_manager.h
play.o: play.cc play.h gamestate.h
world.o: world.cc asset_manager.o laser_manager.o player.o asteroid.o blaster.o drone.o laser.o

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

clean:
	rm -rf *.o*

