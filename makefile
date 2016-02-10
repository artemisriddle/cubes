# Lauren LaGrone
#
# 09/03/2015
#
# Makefile for paint.cpp

CC = g++

OS = $(shell uname -s)

ifeq ($(OS), Darwin)
     LIBS = -framework GLUT -framework OpenGL -framework Cocoa -w
else
     LIBS = -lGL -lGLU -lglut -w
endif

all: hellocube

hellocube: hellocube.cpp
	$(CC) -o hellocube hellocube.cpp $(LIBS)

clean:
	rm hellocube 
