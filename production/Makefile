CC=gcc
CCFLAGS=


LD_LIBS= -lwiringPi -lpthread -lwiringPiDev -lm 
LD_FLAGS=-L/usr/local/lib


OUTDIR=./build
TARGET=robot
SRC=robot

all:
	mkdir -p $(OUTDIR)
	$(CC) $(CCFLAGS) $(LD_FLAGS) $(LD_LIBS) -o $(OUTDIR)/$(TARGET) project.c
