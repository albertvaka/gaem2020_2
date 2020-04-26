
EXEC	= bin/gaem2020

SRC	= $(wildcard src/*.cpp)
OBJ	= $(patsubst src/%, obj/%.o, $(SRC))

DEP_SRC = $(wildcard emyl/*.cpp) $(wildcard imgui/*.cpp) $(wildcard SDL2_ext/*.cpp)
DEP_OBJ = $(patsubst SDL2_ext/%, obj/SDL2_ext/%.o, $(patsubst imgui/%, obj/imgui/%.o, $(patsubst emyl/%, obj/emyl/%.o, $(DEP_SRC))))

OPTIM	= 2
DEBUG	= 0
PROFILE	= 0

# Bash so we can use curly braces expansion
SHELL = bash

CFLAGS	= -std=c++17 -pipe $(shell sdl2-config --cflags) $(EMSCRIPTEN_FLAGS) -I emyl -I SDL2_ext -I imgui -std=c++17 -Wall -Wno-unused-parameter -Wno-reorder $(PROFILEFLAGS) $(DEBUGFLAGS) -O$(strip $(OPTIM))
LDFLAGS	= $(CFLAGS) $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lopenal -lvorbis $(LINKER_FLAGS)

ifdef EMSCRIPTEN
	EMSCRIPTEN_FLAGS=-s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s USE_OGG -s USE_VORBIS -s TOTAL_MEMORY=50331648 -s ALLOW_MEMORY_GROWTH=1 --preload-file bin/data@/data --use-preload-plugins -s SDL2_IMAGE_FORMATS='["png"]'
	OUT_FILE=$(EXEC).js
else
	EMSCRIPTEN_FLAGS=
	OUT_FILE=$(EXEC)

	ifeq ($(shell uname),Linux)
		LINKER_FLAGS=-lGL -lvorbisfile
	else
		LINKER_FLAGS=-framework OpenGL -lvorbisfile
	endif
endif

ifeq ($(strip $(PROFILE)),1)
	PROFILEFLAGS=-pg
endif
ifeq ($(strip $(DEBUG)),1)
	#DEBUGFLAGS=-DDEBUG -ggdb3
	DEBUGFLAGS=-D_DEBUG -g
endif

$(EXEC): $(OBJ) $(DEP_OBJ) Makefile
	$(CXX) $(LDFLAGS) $(OBJ) $(DEP_OBJ) -o $(OUT_FILE)

obj/main.cpp.o: src/main.cpp src/*.h #Makefile
	@mkdir -p obj
	$(CXX) $(CFLAGS) -c $< -o $@

obj/%.cpp.o: src/%.cpp src/*.h #Makefile
	@mkdir -p obj/
	$(CXX) $(CFLAGS) -c $< -o $@

obj/emyl/%.cpp.o: emyl/%.cpp emyl/*.h #Makefile
	@mkdir -p obj/emyl
	$(CXX) $(CFLAGS) -c $< -o $@

obj/imgui/%.cpp.o: imgui/%.cpp imgui/*.h #Makefile
	@mkdir -p obj/imgui
	$(CXX) $(CFLAGS) -c $< -o $@

obj/SDL2_ext/%.cpp.o: SDL2_ext/%.cpp SDL2_ext/*.h Makefile 
	@mkdir -p obj/SDL2_ext
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP_OBJ) $(OUT_FILE)

www:
	emmake $(MAKE)
