CC = gcc
CFLAGS = -Wall -g -DDEBUG
OBJS = main.o keymanager.o eventdispatcher.o control.o controlpanel.o eventmanager.o tab.o
LIBS = -lstdc++

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $<

.o:
	$(CC) $^ -o $@ $(LIBS)

all: $(OBJS)

clean:
	rm *.o