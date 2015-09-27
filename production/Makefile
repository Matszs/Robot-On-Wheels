CC=gcc
CCFLAGS=


LD_LIBS=-lwiringPi -lwiringPiDev -lpthread -lm -lrpigpio
LD_FLAGS=-L/usr/local/lib


OUTDIR=./build
TARGET=robot
SRC=robot

all:
	mkdir -p $(OUTDIR)
	$(CC) -o $(OUTDIR)/$(TARGET) project.c $(CCFLAGS) $(LD_FLAGS) $(LD_LIBS)
