include ../config

all: test

main: main-grapheur.c
	$(CC) -o ../grapheur$@ $^ $(LIBS)

test: main.c
	$(CC) -o ../test$@ $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


