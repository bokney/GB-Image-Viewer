
# GB Image Viewer Makefile #

CC = /opt/gbdk/bin/lcc
CFLAGS = -Wa-l -Wl-m -Wl-j
MFLAGS = -Wl-yt1 -Wl-yo4 -Wl-ya0

all:
	$(CC) $(CFLAGS) -c -o gfx.o gfx.s
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(MFLAGS) -o output.gb main.o gfx.o

clean:
	rm -f *.o *.lst *.map *.gb *.sym
