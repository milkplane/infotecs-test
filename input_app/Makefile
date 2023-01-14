CC = gcc
CC_OBJECTS_FLAG = -c
CC_OUTPUT_FILE_FLAG = -o

LIBS = -lstdc++

BUILD_FOLDER = build
COMMON_SRCS = $(wildcard src/common/*.cpp)
SRCS = $(wildcard src/*.cpp)
COMMON_OBJS = $(subst src/common/, ${BUILD_FOLDER}/, ${COMMON_SRCS:.cpp=.o})
OBJS = $(subst src/, ${BUILD_FOLDER}/, ${SRCS:.cpp=.o})

app : ${OBJS} ${COMMON_OBJS}
	${CC} ${CC_OUTPUT_FILE_FLAG} $@ ${OBJS} ${COMMON_OBJS} ${LIBS}
${BUILD_FOLDER}/%.o : src/%.cpp ${BUILD_FOLDER}_dir
	${CC} ${CC_OBJECTS_FLAG} ${CC_OUTPUT_FILE_FLAG} $@ $<
${BUILD_FOLDER}/%.o : src/common/%.cpp ${BUILD_FOLDER}_dir
	${CC} ${CC_OBJECTS_FLAG} ${CC_OUTPUT_FILE_FLAG} $@ $<
${BUILD_FOLDER}_dir :
	mkdir -p ${BUILD_FOLDER}
clean :
	rm -rf ${BUILD_FOLDER}
vars :
	echo "compiler = ${CC}"
	echo "srcs = ${SRCS}"
	echo "common_srcs = ${COMMON_SRCS}"
	echo "objs = ${OBJS}"
	echo "common_objs = ${COMMON_OBJS}"
