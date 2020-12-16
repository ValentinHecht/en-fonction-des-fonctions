include ../config

all: lexsyneva graphique

lexsyneva: main.c newsyntaxe.c evaluateur.c lexical.c
	$(CC) -o ../lexsyneva $^ $(LIBS)

graphique:
	gcc -c pbPlots.c -std=c99 -O3 -march=native
	gcc -c supportLib.c -std=c99 -O3 -march=native
	gcc -Wno-format -o ../graphique pbPlots.o supportLib.o testglade.c -Wno-deprecated -Wno-format-security -lm -march=native `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o