EXEC      = spacecraze

CXX       = g++-5
CXXFLAGS  = -Iinclude -std=c++14 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LDLIBS    = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
BUILD_DIR = build/
INCL_DIR  = include/
SRC_DIR   = src/






VPATH     = ${SRC_DIR}:${INCL_DIR}:${BUILD_DIR}
SOURCES   = $(notdir $(wildcard ${SRC_DIR}*.cc))
OBJS      = $(addprefix ${BUILD_DIR}, $(patsubst %.cc, %.o, ${SOURCES}))

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ $^ ${LDLIBS}

${BUILD_DIR}%.o: %.cc %.h
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

${BUILD_DIR}%.o: %.cc 
	${CXX} ${CXXFLAGS} -c -o $@ $< ${LDLIBS}

clean:
	rm -rf build/*.o ${EXEC}

