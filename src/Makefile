include ../config

all: main

main: main.o newsyntaxe.o evaluateur.o
	$(CC) -o ../grapheur $^ $(LIBS)
	../grapheur

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o