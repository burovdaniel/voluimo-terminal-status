all: visual_status

CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -ljpeg
INCLUDES = -I/opt/homebrew/include/
LIBS = -L/opt/homebrew/lib/

visual_status: visual_status.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(LIBS) -o visual_status visual_status.o

visual_status.o: visual_status.c
	$(CC) $(CFLAGS) $(INCLUDES) -c visual_status.c

clean:
	rm -f visual_status visual_status.o
