CXX      = g++-5
CXXFLAGS = -std=c++14 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LDLIBS   = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
VPATH    = ../src:../include
SOURCES  = $(notdir $(wildcard ../src/*.cc))
OBJS     = $(patsubst %.cc, %.o, ${SOURCES})

EXEC = a

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@.out $^ ${LDLIBS}

%.o: %.cc %.h
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

clean:
	rm -rf *.o*

