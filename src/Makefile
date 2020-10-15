include ../config

all: lexical

lexical: main-lexical.o lexical.o
	$(CC) -o ../efdf-$@ $^ $(LIBS)


%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


