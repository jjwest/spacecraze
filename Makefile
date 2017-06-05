EXEC         = spacecraze
BUILD_DIR    = build
SRC_DIR      = src

CC       = g++-5
CCFLAGS  = -std=c++14 -O2 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LIBS     = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
FILE_EXT = cc


# __________________________________________________________________________________________________



VPATH     = ${SRC_DIR}:${INCLUDES}:${BUILD_DIR}
SOURCES   = $(notdir $(wildcard ${SRC_DIR}/*.${FILE_EXT}))
OBJECTS   = $(addprefix ${BUILD_DIR}/, $(patsubst %.${FILE_EXT}, %.o, ${SOURCES}))

all: ${EXEC}

${EXEC}: ${OBJECTS}
	${CC} ${CCFLAGS} ${INCLUDES} -o $@ $^ ${LIBS}

${BUILD_DIR}/%.o: %.cc %.h | ${BUILD_DIR}
	${CC} ${CCFLAGS} ${INCLUDES} -c -o $@ $< ${LIBS}

${BUILD_DIR}/%.o: %.cc | ${BUILD_DIR}
	${CC} ${CCFLAGS} ${INCLUDES} -c -o $@ $< ${LIBS}

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

clean:
	rm ${BUILD_DIR}/*.o ${EXEC}

run:
	./${EXEC}
