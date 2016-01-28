CC = g++
CCFLAGS = -std=c++11 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -Werror -g
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SOURCES = $(wildcard **/*.cc)

all:
	$(CC) $(CCFLAGS) $(SOURCES) $(LDFLAGS)

game:
	$(CC) $(CCFLAGS) -c src/game.cc $(LDFLAGS)

gamestate:
	$(CC) $(CCFLAGS) -c src/gamestate_manager.cc $(LDFLAGS)

resource:
	$(CC) $(CCFLAGS) -c src/resourcemanager.cc $(LDFLAGS)

world:
	$(CC) $(CCFLAGS) -c src/world.cc $(LDFLAGS)

sprite:
	$(CC) $(CCFLAGS) -c src/sprite.cc $(LDFLAGS)

player:
	$(CC) $(CCFLAGS) -c src/player.cc $(LDFLAGS)

clean:
	rm *.o
