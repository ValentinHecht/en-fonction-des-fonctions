include ../config

all: test

main: main-grapheur.o
	$(CC) -o ../grapheur$@ $^ $(LIBS)

test: main.o
	$(CC) -o ../test$@ $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


