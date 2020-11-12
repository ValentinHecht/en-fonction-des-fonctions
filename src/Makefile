include ../config

all: graph

graph:
	gcc -c pbPlots.c -std=c99 -O3 -march=native
	gcc -c supportLib.c -std=c99 -O3 -march=native
	gcc -c testgui.c -g -std=c99 -Wall -Wextra `pkg-config gtk+-2.0 --cflags` `pkg-config gtk+-2.0 --libs` -lm -O3 -march=native
	gcc -o ../en-fonction-des-fonctions testgui.o pbPlots.o supportLib.o `pkg-config gtk+-2.0 --cflags` `pkg-config gtk+-2.0 --libs` -g -lm

interface: testgui.o
	$(CC) -o ../en-fonction-des-fonctions $^ pbPlots.o supportLib.o $(LIBS) -g

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


