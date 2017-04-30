IDIR = ./include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=./obj
LDIR = ./lib

LIBS=-lSDL2 -lSDL2_image -lBox2D

_DEPS = init.h Sprite.h textureWrapper.h 

