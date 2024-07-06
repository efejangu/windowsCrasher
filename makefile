CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64

all: bombs

main: bombs.c main.c file_corrupt.c
	$(CC) $(CFLAGS) -o main.exe bombs.c main.c file_corrupt.c

debug: bombs.c main.c file_corrupt.c	
	#$(CC) $(CFLAGS) -g -o main.exe bombs.c main.c file_corrupt.c

clean:
	rm -f main.exeCC = x86_64-w64-mingw32-gcc
