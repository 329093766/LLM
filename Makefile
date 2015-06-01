SRC_FILES = $(wildcard src/*.cpp)
CXX_FLAGS = -Iincludes/ -Wall -g -std=c++14 -lfcgi++ -lfcgi
CXX = ${CXX}

all:
	@mkdir -p bin/
	${CXX} ${CXX_FLAGS} ${SRC_FILES} -o bin/llm

spawn:
	spawn-fcgi -p 8000 -n bin/llm test/echo.llm
