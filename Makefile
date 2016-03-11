CXX      = g++-5
CXXFLAGS = -I/home/jonve547/projects/spacecraze/include -std=c++14 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LDLIBS   = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
VPATH    = src:include:build
SOURCES  = $(notdir $(wildcard src/*.cc))
OBJS     = $(addprefix build/, $(patsubst %.cc, %.o, ${SOURCES}))
EXEC = a

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDLIBS}

build/%.o: %.cc %.h
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

build/%.o: %.cc 
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

clean:
	rm -rf build/*.o

