
all: config
	@make -C src

config: 
	cp config.default config 

unix:
	@echo "generate Bath config"
	@echo "# Configuration for make" > config
	@echo "CC=gcc" >> config
	@echo "CFLAGS=-std=c99 -Wall -Wextra " >> config
	@echo "OS=`uname`"  >> config

windows: 
	@echo "generate PowerShell config"
	@echo # Configuration for make > config
	@echo OS=Windows >> config
	@echo CC=gcc >> config
	@echo CFLAGS=-std=c99 -Wall -Wextra` >> config

clean:
	@make -C src clean
