include ../config

all: main

main: main.c
	$(CC) -o ../grapheur $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


