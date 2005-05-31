OBJS = control.o controlpanel.o eventdispatcher.o eventmanager.o keymanager.o main.o tab.o event.o menu.o buffer.o
CC = gcc
LDFLAGS = -lpthread -lncurses -lstdc++ -lmenu
CFLAGS = -W -Wall

all: $(OBJS)
	$(CC) -o rime $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm rime *.o