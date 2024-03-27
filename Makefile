CC=gcc
MAIN= main.c
TARGETDIR := bin
CUSTOM_HEADERS = lib/src/*

all: $(MAIN) $(CUSTOM_HEADERS)
	mkdir -p $(TARGETDIR)
	$(CC) $(MAIN) $(CUSTOM_HEADERS) -o $(TARGETDIR)/main

clean: 
	rm -rf $(TARGETDIR)