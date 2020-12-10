include ../config

all: main

main: main.c newsyntaxe.c evaluateur.c lexical.c graphique.c supportLib.c pbPlots.c 
	$(CC) -o ../grapheur $^ $(LIBS) -lm -export-dynamic
	../grapheur

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o