REPLIB_SDL = /usr/include/SDL2

OBJ_FILE = Image.o Pixel.o
OBJ_FILES = $(addprefix $(OBJDIR), $(OBJ_FILE))

OBJDIR = obj/
SRCDIR = src/
BINDIR = bin/
DOCDIR = doc/

CC = g++
CFLAGS = -ggdb

all: bin/affichage bin/test bin/exemple

bin/affichage: $(OBJDIR)mainAffichage.o $(OBJ_FILES)
	$(CC) $(CCFLAGS) $(OBJDIR)mainAffichage.o $(OBJ_FILES) -L$(REPLIB_SDL) -lSDL2_image -lSDL2  -o $(BINDIR)affichage

bin/test: $(OBJDIR)mainTest.o $(OBJ_FILES)
	$(CC) $(OBJDIR)mainTest.o $(OBJ_FILES) -L$(REPLIB_SDL) -lSDL2_image -lSDL2 -o $(BINDIR)test

bin/exemple: $(OBJDIR)mainExemple.o $(OBJ_FILES)
	$(CC) $(OBJDIR)mainExemple.o $(OBJ_FILES) -L$(REPLIB_SDL) -lSDL2_image -lSDL2 -o $(BINDIR)exemple

$(OBJDIR)mainAffichage.o: $(SRCDIR)mainAffichage.cpp $(SRCDIR)Image.h
	$(CC) $(CFLAGS) -I$(REPLIB_SDL) -c $(SRCDIR)mainAffichage.cpp -o $(OBJDIR)mainAffichage.o

$(OBJDIR)mainExemple.o: $(SRCDIR)mainExemple.cpp $(SRCDIR)Image.h
	$(CC) $(CFLAGS) -c $(SRCDIR)mainExemple.cpp -o $(OBJDIR)mainExemple.o

$(OBJDIR)mainTest.o: $(SRCDIR)mainTest.cpp $(SRCDIR)Image.h
	$(CC) $(CFLAGS) -c $(SRCDIR)mainTest.cpp -o $(OBJDIR)mainTest.o

$(OBJDIR)Image.o: $(SRCDIR)Image.cpp $(SRCDIR)Image.h $(SRCDIR)Pixel.h
	$(CC) $(CFLAGS) -I$(REPLIB_SDL) -c $(SRCDIR)Image.cpp -o $(OBJDIR)Image.o

$(OBJDIR)Pixel.o: $(SRCDIR)Pixel.cpp $(SRCDIR)Pixel.h
	$(CC) $(CFLAGS) -I$(REPLIB_SDL) -c $(SRCDIR)Pixel.cpp -o $(OBJDIR)Pixel.o

clean:
	rm $(OBJDIR)*.o $(BINDIR)*

docu: doc/image.doxy
	doxygen doc/image.doxy
	firefox doc/html/index.html
