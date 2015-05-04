SRC_FILES = $(wildcard src/*.cpp)
CXX_FLAGS = -Iincludes/ -Wall -g -lfcgi++ -lfcgi
CXX = clang++

all:
	@mkdir -p bin/
	${CXX} ${CXX_FLAGS} ${SRC_FILES} -o bin/llm
