include ../config

all: hello

hello: main-hello.o
	$(CC) -o ../efdf-$@ $^ $(LIBS)


%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


