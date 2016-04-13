EXEC      = spacecraze
BUILD_DIR = build/
INCLUDE   = include/
SRC_DIR   = src/

CXX       = g++-5
CXXFLAGS  = -std=c++14 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LIBS      = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lcppformat


# __________________________________________________________________________________________________



VPATH     = ${SRC_DIR}:${INCLUDES}:${BUILD_DIR}
SOURCES   = $(notdir $(wildcard ${SRC_DIR}*.cc))
OBJS      = $(addprefix ${BUILD_DIR}, $(patsubst %.cc, %.o, ${SOURCES}))
INCLUDES  = $(addprefix -I, ${INCLUDE})

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} ${INCLUDES} -o $@ $^ ${LIBS}

${BUILD_DIR}%.o: %.cc %.h
	${CXX} ${CXXFLAGS} ${INCLUDES} -c -o $@ $< ${LIBS}

${BUILD_DIR}%.o: %.cc 
	${CXX} ${CXXFLAGS} ${INCLUDES} -c -o $@ $< ${LIBS}

clean:
	rm -f ${BUILD_DIR}*.o ${EXEC}
