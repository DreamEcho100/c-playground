CC = gcc
CFLAGS = -Wall -g -Iglad/include
LDFLAGS = -lglfw -lm -lGL

SRC = main.c glad/src/glad.c
TARGET = OpenGL_Project

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

