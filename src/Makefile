include ../config

all: syntaxe

syntaxe: newsyntaxe.o main.o
	$(CC) -o ../efdf-$@ $^ $(LIBS)
	../efdf-$@

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o