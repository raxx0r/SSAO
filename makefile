OUT = bin/main
CC = g++
ODIR = build
SDIR = src
INC = -Iinclude
CFLAGS = -c -Wall -std=c++11 

OS_NAME := $(shell uname -s)

ifeq ($(OS_NAME), Linux)
LDFLAGS = `pkg-config --libs glfw3` -lGL -lGLU -lX11 -lXxf86vm -lpthread\
		  -lXrandr -lXi -lassimp -lIL
else
LDFLAGS = `pkg-config --libs glfw3` -lglfw3 -framework OpenGL -framework Cocoa \
		  `pkg-config --libs assimp` -L/usr/local/Cellar/devil/1.7.8_1/lib/ -lIL
endif

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=build/%.o)

$(ODIR)/%.o: $(SDIR)/%.cpp  
	@test -d build || mkdir -p build
	$(CC) $(CFLAGS) $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	@$(CC) $(OBJS) -o $(OUT) $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o $(OUT)
