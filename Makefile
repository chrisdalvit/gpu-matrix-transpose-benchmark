
.PHONY: stats
CC=gcc
SRC_C_DIR := src/c
SRC_CUDA_DIR := src/cuda
TARGET_DIR := bin
STATS_ROOT := stats
STATS_DIR := $(STATS_ROOT)/$(shell date +'%y_%m_%dT%H:%M:%S')
CUSTOM_HEADERS = lib/src/*
OPTIM_FLAGS = 0 1 2 3 

SRC_C := $(shell ls $(SRC_C_DIR))
SRC_CUDA := $(shell ls $(SRC_CUDA_DIR))
BINS_C := $(SRC_C:%.c=%)
BINS_CUDA := $(SRC_CUDA:%.cu=%)

all: dirs compile_c stats report
	
dirs:
	@echo Create directories...
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(STATS_DIR)/cache_runs

stats: dirs $(BINS_C:%=compile_%)
	@echo Run benchmark file...
	@sh benchmark.sh $(TARGET_DIR) $(STATS_DIR)

compile_c: $(BINS_C:%=compile_c_%)

compile_c_%:
	@echo Compile $*...
	@for optim in $(OPTIM_FLAGS) ; do \
		$(CC) $(SRC_C_DIR)/$*.c $(CUSTOM_HEADERS) -g0 -Wall -O$$optim -o $(TARGET_DIR)/$*-$$optim -lm; \
	done

report: report/report.tex
	@echo Compile report...
	@pdflatex -output-directory report report/report.tex
	@biber report/report
	@pdflatex -output-directory report report/report.tex
	@pdflatex -output-directory report report/report.tex

marzola:
	@echo Create directories...
	@mkdir -p $(TARGET_DIR)
	@./cluster/run.sh

clean: 
	@echo Clean up directories...
	@rm -rf $(TARGET_DIR)
	@rm -rf $(STATS_ROOT)