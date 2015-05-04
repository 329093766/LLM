SRC_FILES = $(wildcard src/*.cpp)
CXX_LINKER = -Wall -g -lfcgi++ -lfcgi
CXX = clang++

all:
	@mkdir -p bin/
	${CXX} ${CXX_LINKER} ${SRC_FILES} -o bin/llm
