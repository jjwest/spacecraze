EXEC      = spacecraze
BUILD_DIR = build/
INCL_DIR  = include/
SRC_DIR   = src/

CXX       = g++-5
CXXFLAGS  = -std=c++14 -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -pedantic -g
LIBS      = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer


# __________________________________________________________________________________________________



VPATH     = ${SRC_DIR}:${INCL_DIR}:${BUILD_DIR}
SOURCES   = $(notdir $(wildcard ${SRC_DIR}*.cc))
OBJS      = $(addprefix ${BUILD_DIR}, $(patsubst %.cc, %.o, ${SOURCES}))

all: ${EXEC}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -I${INCL_DIR} -o $@ $^ ${LIBS}

${BUILD_DIR}%.o: %.cc %.h
	${CXX} ${CXXFLAGS} -I${INCL_DIR} -c -o $@ $< ${LIBS}

${BUILD_DIR}%.o: %.cc 
	${CXX} ${CXXFLAGS} -I${INCL_DIR} -c -o $@ $< ${LIBS}

clean:
	rm -f ${BUILD_DIR}*.o ${EXEC}

