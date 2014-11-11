OUT = bin/main
CC = g++
ODIR = build
SDIR = src
INC = -Iinclude
CFLAGS = -c -Wall `pkg-config --cflags glfw3`
LDFLAGS = `pkg-config --libs glfw3` -framework OpenGL -framework Cocoa 


_OBJS = main.o test.o ShaderProgram.o Shader.o Renderer.o Window.o


OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o: $(SDIR)/%.cpp 
	@test -d build || mkdir -p build
	@$(CC) -c -Wall $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	@$(CC) $(OBJS) -o $(OUT) $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o $(OUT)
