OBJS = control.o controlpanel.o eventdispatcher.o eventmanager.o keymanager.o main.o tab.o event.o menu.o buffer.o xml_parser.o
CC = gcc
LDFLAGS = -lpthread -lncurses -lstdc++ -lmenu -lexpat
CFLAGS = -W -Wall -g -pedantic-errors


all: $(OBJS)
	$(CC) -o rime $(OBJS) $(LDFLAGS)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm rime *.o