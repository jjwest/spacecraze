EXEC      = spacecraze
BUILD_DIR = build/
INCLUDE   = include/
SRC_DIR   = src/

CC       = g++-5
CCFLAGS  = -std=c++14 -O2 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LIBS     = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer


# __________________________________________________________________________________________________



VPATH     = ${SRC_DIR}:${INCLUDES}:${BUILD_DIR}
SOURCES   = $(notdir $(wildcard ${SRC_DIR}*.cc))
OBJECTS   = $(addprefix ${BUILD_DIR}, $(patsubst %.cc, %.o, ${SOURCES}))
INCLUDES  = $(addprefix -I, ${INCLUDE})

all: ${EXEC}

${EXEC}: ${OBJECTS}
	${CC} ${CCFLAGS} ${INCLUDES} -o $@ $^ ${LIBS}

${BUILD_DIR}%.o: %.cc %.h
	${CC} ${CCFLAGS} ${INCLUDES} -c -o $@ $< ${LIBS}

${BUILD_DIR}%.o: %.cc
	${CC} ${CCFLAGS} ${INCLUDES} -c -o $@ $< ${LIBS}

clean:
	rm ${BUILD_DIR}*.o ${EXEC}

run:
	./${EXEC}
