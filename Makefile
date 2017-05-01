VPATH = /usr/include:./include:/usr/lib/gcc/x86_64-redhat-linux/6.2.1/include:/usr/local/include

CC=g++
CFLAGS=-I$(IDIR)

ODIR := obj
LDIR := lib
IDIR := include

OBJ = main.o sprite.o textureWrapper.o
_DEPS = $(addprefix $(IDIR)/, init.h Sprite.h textureWrapper.h) 
LIBS=-lSDL2 -lSDL2_image -lBox2D

tuot: $(OBJ)
	cc -o tuot $(OBJ)
Sprite.o: Sprite.h textureWrapper.h
textureWrapper.o: SDL.h SDL2_image.h

