#!/bin/sh

BIN_DIR=$1
STATS_DIR=$2
STATS_FILE=$STATS_DIR/$(date +'%y_%m_%dT%H:%M:%S')
OPTIM=''

echo name,optim,size,time >> $STATS_FILE;

for file in $(ls $BIN_DIR)
do
    OPTIM=${file#*-} # Get optimization flag from suffix
    NAME=${file%-*} # Get file name
    for size in $(seq 5 13) # Loop over sizes
    do
        for i in $(seq 1 5) # Loop over the number of repetitions
        do
            printf "$NAME,$OPTIM," >> $STATS_FILE
            $BIN_DIR/$file $size >> $STATS_FILE
        done
    done
done