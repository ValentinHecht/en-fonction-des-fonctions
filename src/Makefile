include ../config

all: testglade

graph:
	gcc -c pbPlots.c -std=c99 -O3 -march=native
	gcc -c supportLib.c -std=c99 -O3 -march=native
	gcc -c testgui.c -g -std=c99 -Wall -Wextra `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -lm -O3 -march=native
	gcc -o ../en-fonction-des-fonctions testgui.o pbPlots.o supportLib.o `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -g -lm

testglade :
	gcc -c pbPlots.c -std=c99 -O3 -march=native
	gcc -c supportLib.c -std=c99 -O3 -march=native
	gcc -Wno-format -o ../testgladetest pbPlots.o supportLib.o testglade.c -Wno-deprecated -Wno-format-security -lm -march=native `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


