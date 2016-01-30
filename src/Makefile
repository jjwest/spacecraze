CC = g++
CCFLAGS = -std=c++11 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -Werror -g
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: ../inc/player.h player.cc unit_test.cc
	${CC} ${CCFLAGS} player.cc unit_test.cc ${LDFLAGS}

