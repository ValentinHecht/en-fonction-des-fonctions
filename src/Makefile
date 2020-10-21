include ../config

all: hello

hello: testgui.o
	$(CC) `pkg-config gtk+-2.0 --cflags` -o ../en-fonction-des-fonctions $^ $(LIBS) `pkg-config gtk+-2.0 --libs`

%.o: %.c
	$(CC) `pkg-config gtk+-2.0 --cflags` -c $< $(CFLAGS) `pkg-config gtk+-2.0 --libs` -lm

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


