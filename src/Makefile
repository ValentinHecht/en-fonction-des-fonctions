include ../config

all: main

main: main.c newsyntaxe.c evaluateur.c lexical.c supportLib.c pbPlots.c testglade.c
	$(CC) -o ../grapheur $^ $(LIBS)
	../grapheur

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o