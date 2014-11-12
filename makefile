OUT = bin/main
CC = g++
ODIR = build
SDIR = src
INC = -Iinclude
CFLAGS = -c -Wall 
LDFLAGS = `pkg-config --libs glfw3` -framework OpenGL -framework Cocoa \
		  `pkg-config --libs assimp` 


_OBJS = main.o ShaderProgram.o Shader.o Renderer.o ModelImporter.o


OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o: $(SDIR)/%.cpp 
	@test -d build || mkdir -p build
	$(CC) -c -Wall $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	$(CC) $(OBJS) -o $(OUT) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)
