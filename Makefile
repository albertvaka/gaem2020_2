
EXEC	= bin/gaem2020

SRC	= $(wildcard src/*.cpp)
OBJ	= $(patsubst src/%, obj/%.o, $(SRC))

DEP_SRC = $(shell find vendor/ -type f -name '*.cpp' -o -name '*.c' ! -path 'vendor/glew/*')
DEP_OBJ = $(patsubst vendor/%, obj/vendor/%.o, $(DEP_SRC))
DEP_INCLUDE = $(patsubst vendor/%, -I vendor/%, $(shell find vendor -maxdepth 2 -path \*\include ! -path vendor/SDL2/include) $(shell find vendor -mindepth 1 -maxdepth 1 ! -path vendor/glew -type d '!' -exec test -e "{}/include" ';' -print ))

OPTIM     = z
DEBUG     = 0
PROFILE   = 0
IMGUI     = 0
WEBGL_VER = 2

# Bash so we can use curly braces expansion
SHELL = bash

#NOTE: Dynamic casts are disabled by fno-rtti
CFLAGS = -pipe $(shell sdl2-config --cflags) $(EMSCRIPTEN_FLAGS) $(DEP_INCLUDE) -Wall -Wno-unused-parameter -Wno-reorder $(PROFILEFLAGS) $(DEBUGFLAGS) $(IMGUIFLAGS) -O$(strip $(OPTIM))
CXXFLAGS = $(CFLAGS) -std=c++17 -fno-rtti -fno-exceptions
LDFLAGS	 = $(CXXFLAGS) $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer $(LINKER_FLAGS)

ifdef EMSCRIPTEN
	ifeq ($(strip $(WEBGL_VER)),2)
		WEBGL_FLAGS=-s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -DSDL_GPU_DISABLE_GLES_2 -DIMGUI_IMPL_OPENGL_ES3
	else
		WEBGL_FLAGS=-s MIN_WEBGL_VERSION=1 -s MAX_WEBGL_VERSION=1 -DSDL_GPU_DISABLE_GLES_3 -DIMGUI_IMPL_OPENGL_ES2
	endif
	EMSCRIPTEN_FLAGS=-s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_OGG -s USE_VORBIS -s ALLOW_MEMORY_GROWTH=1 --preload-file bin/data@/data --use-preload-plugins $(WEBGL_FLAGS)
	OUT_FILE=$(EXEC).js
	LINKER_FLAGS=
else
	EMSCRIPTEN_FLAGS=
	OUT_FILE=$(EXEC)

	ifeq ($(shell uname),Linux)
		LINKER_FLAGS=-lGL -lGLEW
	else
		LINKER_FLAGS=-framework OpenGL -lGLEW
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

debug:
	@echo $(DEP_SRC)