EXEC_NAME = module_image
OBJ_FILES = mainTest.o Image.o Pixel.o

CC = g++
CFLAGS = -Wall -ggdbg

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME)

mainTest.o: mainTest.cpp Image.h
	$(CC) $(CFLAGS) -c mainTest.cpp

Image.o: Image.cpp Image.h Pixel.h
	$(CC) $(CFLAGS) -c Image.cpp

Pixel.o: Pixel.cpp Pixel.h
	$(CC) $(CFLAGS) -c Pixel.cpp

clean:
	rm $(OBJ_FILES)
