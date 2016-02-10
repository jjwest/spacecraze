CXX      = g++-5
CXXFLAGS = -std=c++14 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LDLIBS   = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
VPATH    = ./src:./include:./build

EXEC     = a

all: ${EXEC}

${EXEC}: main.o game.o player.o visible_object.o asset_manager.o texture.o font.o music.o
	${CXX} ${CXXFLAGS} -o a.out $^ ${LDLIBS}

main.o: main.cc game.o
game.o: game.cc player.o asset_manager.o
player.o: player.cc player.h constants.h asset_manager.o
visible_object.o: visible_object.cc visible_object.h
asset_manager.o: asset_manager.cc asset_manager.h texture.o font.o music.o
texture.o: texture.cc texture.h
font.o: font.cc font.h
music.o: music.cc music.h
input_handler.o: input_handler.cc input_handler.h
enemy.o: enemy.cc enemy.h visible_object.o
asteroid.o: asteroid.cc asteroid.h constants.h enemy.o asset_manager.o
blaster.o: blaster.cc blaster.h constants.h enemy.o asset_manager.o

%.o: %.cc
	${CXX} ${CXXFLAGS} -c -o build/$@ $< ${LDLIBS}

clean:
	rm -rf build/*.o

