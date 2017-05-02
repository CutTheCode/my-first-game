VPATH = src:include:lib:/usr/include:usr/lib/gcc/x86_64-redhat-linux/6.2.1/include:/usr/local/include:/usr/include


# Specify the directories for all dependencies
ODIR = obj
LDIR = lib
IDIR = include
SRC = src

# Compiler and its flags
CC = g++
CFLAGS = -I $(IDIR)

OBJS = main.o Sprite.o textureWrapper.o init.o
_DEPS = $(addprefix $(IDIR)/, init.h Sprite.h textureWrapper.h)
LIBS = -lSDL2 -lSDL2_image -lBox2D


tuot: $(OBJS)
	$(CC) $(LIBS) -o tuot $(OBJS) $(CFLAGS)
main.o: 
	$(CC) $(CFLAGS) -c -o main.o $(SRC)/main.cpp
Sprite.o: Sprite.h 
	$(CC) $(CFLAGS) -c -o Sprite.o $(LDIR)/Sprite.cpp
textureWrapper.o: textureWrapper.h 
	$(CC) $(CFLAGS) -c -o textureWrapper.o $(LDIR)/textureWrapper.cpp
init.o: init.h
	$(CC) $(CFLAGS) -c -o init.o $(LDIR)/init.cpp

.PHONY:
clean:
	rm *.o
