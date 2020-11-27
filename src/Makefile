include ../config

all: main

main: main.c newsyntaxe.c
	$(CC) -o ../efdf-$@ $^ $(LIBS)
	../efdf-$@

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o