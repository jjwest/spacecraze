CC = g++
CCFLAGS = -std=c++11 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -Werror -g
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SOURCES = $(wildcard **/*.cc)

all:
	$(CC) $(CCFLAGS) $(SOURCES) $(LDFLAGS)

test:	player
	$(CC) $(CCFLAGS) src/unit_test.cc $(LDFLAGS)

game:
	$(CC) $(CCFLAGS) -c src/game.cc $(LDFLAGS)

world:	asteroid blaster drone player
	$(CC) $(CCFLAGS) -c src/world.cc $(LDFLAGS)

sprite:
	$(CC) $(CCFLAGS) -c src/sprite.cc $(LDFLAGS)

player:	
	$(CC) $(CCFLAGS) -c src/player.cc $(LDFLAGS)

asteroid:
	$(CC) $(CCFLAGS) -c src/asteroid.cc $(LDFLAGS)

laser:
	$(CC) $(CCFLAGS) -c src/laser.cc $(LDFLAGS)

blaster: world
	$(CC) $(CCFLAGS) -c src/blaster.cc $(LDFLAGS)

drone:
	$(CC) $(CCFLAGS) -c src/drone.cc $(LDFLAGS)

clean:
	rm *.o

check-syntax:
	gcc -o nul -S ${CHK_SOURCES}
