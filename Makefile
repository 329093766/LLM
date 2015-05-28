SRC_FILES = $(wildcard src/*.cpp)
CXX_FLAGS = -Iincludes/ -Wall -g -std=c++11 -lfcgi++ -lfcgi
CXX = clang++

all:
	@mkdir -p bin/
	${CXX} ${CXX_FLAGS} ${SRC_FILES} -o bin/llm

spawn:
	spawn-fcgi -p 8000 -n bin/llm
