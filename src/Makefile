include ../config

all: hello

hello: testgui.o
	$(CC) -o ../en-fonction-des-fonctions $^ $(LIBS) -g
%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


