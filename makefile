OUT = bin/main
CC = g++
ODIR = build
SDIR = src
INC = -Iinclude
CFLAGS = -c -Wall `pkg-config --cflags glfw3`
LDFLAGS = `pkg-config --libs glfw3` -framework OpenGL -framework Cocoa 


_OBJS = main.o test.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o: $(SDIR)/%.cpp 
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	$(CC) $(OBJS) -o $(OUT) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)
