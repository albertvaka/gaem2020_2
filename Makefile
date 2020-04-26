
EXEC	= bin/gaem2020

SRC	= $(wildcard src/*.cpp)
OBJ	= $(patsubst src/%, obj/%.o, $(SRC))

DEP_SRC = $(wildcard emyl/*.cpp) $(wildcard imgui/*.cpp) $(wildcard SDL2_ext/*.cpp)
DEP_OBJ = $(patsubst SDL2_ext/%, obj/SDL2_ext/%.o, $(patsubst imgui/%, obj/imgui/%.o, $(patsubst emyl/%, obj/emyl/%.o, $(DEP_SRC))))

OPTIM	= 0
DEBUG	= 0
PROFILE	= 0

# Bash so we can use curly braces expansion
SHELL = bash

CFLAGS	= -pipe $(shell sdl2-config --cflags) -I emyl -I SDL2_ext -I imgui -std=c++17 -Wall -Wno-unused-parameter -Wno-reorder $(PROFILEFLAGS) $(DEBUGFLAGS) -O$(strip $(OPTIM))
LDFLAGS	= -pipe -std=c++17 $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lopenal -lvorbis -lvorbisfile $(OPENGLFLAGS) $(PROFILEFLAGS) $(DEBUGFLAGS) -O$(strip $(OPTIM))

ifeq ($(shell uname),Linux)
	OPENGLFLAGS=-lGL
else
	OPENGLFLAGS=-framework OpenGL
endif

ifeq ($(strip $(PROFILE)),1)
	PROFILEFLAGS=-pg
endif
ifeq ($(strip $(DEBUG)),1)
	#DEBUGFLAGS=-DDEBUG -ggdb3
	DEBUGFLAGS=-D_DEBUG -g
endif

$(EXEC): $(OBJ) $(DEP_OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) $(DEP_OBJ) -o $(EXEC)

obj/main.cpp.o: src/main.cpp src/*.h Makefile
	@mkdir -p obj
	$(CXX) $(CFLAGS) -c $< -o $@

obj/%.cpp.o: src/%.cpp src/*.h Makefile
	@mkdir -p obj/
	$(CXX) $(CFLAGS) -c $< -o $@

obj/emyl/%.cpp.o: emyl/%.cpp emyl/*.h Makefile
	@mkdir -p obj/emyl
	$(CXX) $(CFLAGS) -c $< -o $@

obj/imgui/%.cpp.o: imgui/%.cpp imgui/*.h Makefile
	@mkdir -p obj/imgui
	$(CXX) $(CFLAGS) -c $< -o $@

obj/SDL2_ext/%.cpp.o: SDL2_ext/%.cpp SDL2_ext/*.h Makefile
	@mkdir -p obj/SDL2_ext
	$(CXX) $(CFLAGS) -Wno-unused-but-set-variable -c $< -o $@

clean:
	$(RM) $(OBJ) $(IMGUI_OBJ) $(EXEC)
