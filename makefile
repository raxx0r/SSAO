CC = g++
SRCDIR = src/
LFLAGS = -framework OpenGL -framework Cocoa 
INCLUDES = -I include/ 
CFLAGS = -w 
TARGET = main

all : $(TARGET)

$(TARGET) : $(TARGET).cpp
	$(CC) $(TARGET).cpp $(SRCDIR)*.cpp $(LFLAGS) $(CFLAGS) $(INCLUDES) -o bin/$(TARGET)

objects: 
	g++ -c src/*.cpp

clean:
	rm bin/$(TARGET)

