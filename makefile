OUT = bin/main
CC = g++
ODIR = build
SDIR = src
INC = -Iinclude
CFLAGS = -c -Wall 

OS_NAME := $(shell uname -s)

ifeq ($(OS_NAME), Linux)
LDFLAGS = `pkg-config --libs glfw3` -lGL -lGLU -lX11 -lXxf86vm -lpthread\
		  -lXrandr -lXi `pkg-config --libs assimp`
else
LDFLAGS = `pkg-config --libs glfw3` -framework OpenGL -framework Cocoa \
		  `pkg-config --libs assimp` 
endif

_OBJS = main.o ShaderProgram.o Shader.o Renderer.o ModelImporter.o \
		Window.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o: $(SDIR)/%.cpp 
	@test -d build || mkdir -p build
	$(CC) $(CFLAGS) $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	@$(CC) $(OBJS) -o $(OUT) $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o $(OUT)
