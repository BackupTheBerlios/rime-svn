CC = gcc
CFLAGS = -Wall -g
OBJS = main.o keymanager.o eventdispatcher.o
LIBS = -lstdc++

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $<

.o:
	$(CC) $^ -o $@ $(LIBS)

all: $(OBJS)

clean:
	rm *.o