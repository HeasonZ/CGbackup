FILE=skeleton

########
#   Directories
S_DIR=Source
B_DIR=Build

########
SRC_FILES := $(wildcard $(S_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(S_DIR)/%.cpp,$(B_DIR)/%.o,$(SRC_FILES))

########
#   Output
EXEC=$(B_DIR)/$(FILE)

# default build settings
CC_OPTS=-c -pipe -Wall -Wno-switch -ggdb -g3 -O3 
LN_OPTS=
CC=g++

########
#       SDL options
SDL_CFLAGS := $(shell sdl2-config --cflags)
GLM_CFLAGS := -I../glm/
SDL_LDFLAGS := $(shell sdl2-config --libs)

########
#   This is the default action
all:Build


########
#   Object list
#
OBJ = $(B_DIR)/$(OBJ_FILES).o


########
#   Objects
$(B_DIR)/%.o:$(S_DIR)/%.cpp 
	$(CC) $(CC_OPTS) $(SDL_CFLAGS) $(GLM_CFLAGS) -o $@ $<


########
#   Main build rule     
Build : $(OBJ_FILES)
	$(CC) $(LN_OPTS) $^ -o $(EXEC) $(SDL_LDFLAGS) 


clean:
	rm -f $(B_DIR)/* 
