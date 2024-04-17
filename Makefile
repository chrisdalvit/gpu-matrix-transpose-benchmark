CC=gcc
SRC_DIR := src
TARGET_DIR := bin
STATS_DIR := stats
CUSTOM_HEADERS = lib/src/*
OPTIM_FLAGS = 0 1 2 3 

SRC := $(shell ls $(SRC_DIR))
BINS := $(SRC:%.c=%)

all: create_dirs $(BINS:%=compile_%)
	sh benchmark.sh $(TARGET_DIR) $(STATS_DIR)
	
create_dirs:
	mkdir -p $(TARGET_DIR)
	mkdir -p $(STATS_DIR)

compile_%:
	@for optim in $(OPTIM_FLAGS) ; do \
		$(CC) $(SRC_DIR)/$*.c $(CUSTOM_HEADERS) -g -Wall -O$$optim -o $(TARGET_DIR)/$*-$$optim -lm; \
	done

clean: 
	rm -rf $(TARGET_DIR)
	rm -rf $(STATS_DIR)