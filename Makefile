EXEC_NAME = module_image

OBJ_FILE = Image.o Pixel.o
OBJ_FILES = $(addprefix $(OBJDIR), $(OBJ_FILE))

OBJDIR = obj/
SRCDIR = src/
BINDIR = bin/
DOCDIR = doc/

CC = g++
CFLAGS = -Wall -ggdb

all: $(BINDIR)$(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(BINDIR)$(EXEC_NAME)

test: $(OBJDIR)mainTest.o $(OBJ_FILES)
	$(CC) $(OBJDIR)mainTest.o $(OBJ_FILES) -o $(BINDIR)test

exemple: $(OBJDIR)mainExemple.o $(OBJ_FILES)
	$(CC) $(OBJDIR)mainExemple.o $(OBJ_FILES) -o $(BINDIR)exemple

$(OBJDIR)mainExemple.o: $(SRCDIR)mainExemple.cpp $(SRCDIR)Image.h
	$(CC) $(CFLAGS) -c $(SRCDIR)mainExemple.cpp -o $(OBJDIR)mainExemple.o

$(OBJDIR)mainTest.o: $(SRCDIR)mainTest.cpp $(SRCDIR)Image.h
	$(CC) $(CFLAGS) -c $(SRCDIR)mainTest.cpp -o $(OBJDIR)mainTest.o

$(OBJDIR)Image.o: $(SRCDIR)Image.cpp $(SRCDIR)Image.h $(SRCDIR)Pixel.h
	$(CC) $(CFLAGS) -c $(SRCDIR)Image.cpp -o $(OBJDIR)Image.o

$(OBJDIR)Pixel.o: $(SRCDIR)Pixel.cpp $(SRCDIR)Pixel.h
	$(CC) $(CFLAGS) -c $(SRCDIR)Pixel.cpp -o $(OBJDIR)Pixel.o

clean:
	rm $(OBJDIR)*.o
