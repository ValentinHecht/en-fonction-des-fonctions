include ../config

all: lexsyneva graphique

lexsyneva: main.c newsyntaxe.c evaluateur.c lexical.c
	$(CC) -o ../lexsyneva $^ $(LIBS)

graphique: main.c newsyntaxe.c evaluateur.c lexical.c
	$(CC) -o ../graphique $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o