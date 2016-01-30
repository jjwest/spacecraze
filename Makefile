CC = g++
CCFLAGS = -std=c++11 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -Werror -g
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SRCDIR = ./src/
INCLDIR = ./inc/

all: unit_test.o player.o visible_object.o
	${CC} ${CCFLAGS} unit_test.o player.o visible_object.o ${LDFLAGS}

unit_test.o: ./src/unit_test.cc player visible_object
	${CC} ${CCFLAGS} -c $<

player.o: ./src/player.cc ./inc/player.h visible_object
	${CC} ${CCFLAGS} -c $<

visible_object.o: ./src/visible_object.cc ./inc/visible_object.h
	${CC} ${CCFLAGS} -c $<

clean:
	rm -rf *.o
