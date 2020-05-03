
EXEC	= bin/gaem2020

SRC	= $(wildcard src/*.cpp)
OBJ	= $(patsubst src/%, obj/%.o, $(SRC))

DEP_SRC = $(shell find vendor/ -type f -name '*.cpp' -o -name '*.c')
DEP_OBJ = $(patsubst vendor/%, obj/vendor/%.o, $(DEP_SRC))
DEP_INCLUDE = $(patsubst vendor/%, -I vendor/%, $(shell find vendor -maxdepth 2 -path \*\include) $(shell find vendor -mindepth 1 -maxdepth 1 -type d '!' -exec test -e "{}/include" ';' -print))

OPTIM	= z
DEBUG	= 1
PROFILE	= 0
IMGUI	= 1

# Bash so we can use curly braces expansion
SHELL = bash

#NOTE: Dynamic casts are disabled by fno-rtti
CFLAGS = -pipe $(shell sdl2-config --cflags) $(EMSCRIPTEN_FLAGS) $(DEP_INCLUDE) -Wall -Wno-unused-parameter -Wno-reorder $(PROFILEFLAGS) $(DEBUGFLAGS) $(IMGUIFLAGS) -O$(strip $(OPTIM))
CXXFLAGS = $(CFLAGS) -std=c++17 -fno-rtti -fno-exceptions
LDFLAGS	 = $(CXXFLAGS) $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer $(LINKER_FLAGS)

ifdef EMSCRIPTEN
	EMSCRIPTEN_FLAGS=-s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_OGG -s USE_VORBIS -s ALLOW_MEMORY_GROWTH=1 --preload-file bin/data@/data --use-preload-plugins -s SDL2_IMAGE_FORMATS='["png"]'
	OUT_FILE=$(EXEC).js
	LINKER_FLAGS=
else
	EMSCRIPTEN_FLAGS=
	OUT_FILE=$(EXEC)

	ifeq ($(shell uname),Linux)
		LINKER_FLAGS=-lGL
	else
		LINKER_FLAGS=-framework OpenGL
	endif
endif

ifeq ($(strip $(PROFILE)),1)
	PROFILEFLAGS=-pg
endif
ifeq ($(strip $(DEBUG)),1)
	#DEBUGFLAGS=-DDEBUG -ggdb3
	DEBUGFLAGS=-D_DEBUG -g
endif
ifeq ($(strip $(IMGUI)),1)
	IMGUIFLAGS=-D_IMGUI
endif

$(EXEC): $(OBJ) $(DEP_OBJ) Makefile
	$(CXX) $(LDFLAGS) $(OBJ) $(DEP_OBJ) -o $(OUT_FILE)

obj/main.cpp.o: src/main.cpp src/*.h Makefile
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.cpp.o: src/%.cpp src/*.h Makefile
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/vendor/%.c.o: vendor/%.c $(shell find vendor/ -type f -name '*.h') Makefile
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

obj/vendor/%.cpp.o: vendor/%.cpp $(shell find vendor/ -type f -name '*.h') Makefile
	@mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP_OBJ) $(OUT_FILE)

www:
	emmake $(MAKE)
