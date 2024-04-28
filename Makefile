
.PHONY: stats
CC=gcc
SRC_DIR := src
TARGET_DIR := bin
STATS_ROOT := stats
STATS_DIR := $(STATS_ROOT)/$(shell date +'%y_%m_%dT%H:%M:%S')
CUSTOM_HEADERS = lib/src/*
OPTIM_FLAGS = 0 1 2 3 

SRC := $(shell ls $(SRC_DIR))
BINS := $(SRC:%.c=%)

all: dirs compile stats report
	
dirs:
	@echo Create directories...
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(STATS_DIR)/cache_runs

stats: dirs $(BINS:%=compile_%)
	@echo Run benchmark file...
	@sh benchmark.sh $(TARGET_DIR) $(STATS_DIR)

compile: $(BINS:%=compile_%)

compile_%:
	@echo Compile $*...
	@for optim in $(OPTIM_FLAGS) ; do \
		$(CC) $(SRC_DIR)/$*.c $(CUSTOM_HEADERS) -g0 -Wall -O$$optim -o $(TARGET_DIR)/$*-$$optim -lm; \
	done

report: report/report.tex
	@echo Compile report...
	@pdflatex -output-directory report report/report.tex
	@biber report/report
	@pdflatex -output-directory report report/report.tex
	@pdflatex -output-directory report report/report.tex

clean: 
	@echo Clean up directories...
	@rm -rf $(TARGET_DIR)
	@rm -rf $(STATS_ROOT)