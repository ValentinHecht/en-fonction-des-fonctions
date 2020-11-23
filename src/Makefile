include ../config

all: syntaxe

syntaxe: newsyntaxe.c main.c
	$(CC) -o ../efdf-$@ $^ $(LIBS)
	../efdf-$@

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o